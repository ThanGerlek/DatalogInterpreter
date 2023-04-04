#ifndef PROJECT1_T2K_SCANNER_CPP
#define PROJECT1_T2K_SCANNER_CPP

#include "Scanner.h"

/**
 * @brief Scan all tokens into the given vector.
 * Throws an error if the vector is nonempty.
 */
void Scanner::scanTokensInto(std::vector<Token> &tokens)
{
    if (!tokens.empty())
    {
        std::cerr << "[ERROR] Tried to scan into a nonempty vector." << std::endl;
        throw;
    }

    while (hasNextToken())
    {
        scanNextTokenInto(tokens);
    }
}

void Scanner::scanNextTokenInto(std::vector<Token> &tokens)
{
    Token token = scanNextToken();
    if (token.getType() != COMMENT)
    {
        tokens.push_back(token);
    }
}

/**
 * @brief Return true iff there is more text in the input string to scan.
 */
bool Scanner::hasNextToken() const
{
    return !reachedEOF;
}

/**
 * @brief Scan a single token, removing it from the input string.
 */
Token Scanner::scanNextToken()
{
    removeWhitespaceFromInput();

    MaybeToken maybeToken = scanForEOFToken(); // END_OF_FILE token
    if (maybeToken.hasToken())
    {
        Token t = maybeToken.getToken();
        reachedEOF = true;
        return t;
    }

    maybeToken = scanForCharTokens(); // COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, ADD, and MULTIPLY tokens
    if (maybeToken.hasToken())
    {
        Token t = maybeToken.getToken();
        return t;
    }

    maybeToken = scanForColonTokens(); // COLON and COLON_DASH tokens
    if (maybeToken.hasToken())
    {
        Token t = maybeToken.getToken();
        return t;
    }

    maybeToken = scanForWordTokens();
    if (maybeToken.hasToken())
    {
        Token t = maybeToken.getToken();
        return t;
    }

    maybeToken = scanForStringToken(); // STRING token
    if (maybeToken.hasToken())
    {
        Token t = maybeToken.getToken();
        return t;
    }

    maybeToken = scanForCommentToken(); // COMMENT token
    if (maybeToken.hasToken())
    {
        Token t = maybeToken.getToken();
        return t;
    }

    // UNDEFINED token
    std::string value = inputString.substr(0, 1);
    inputString = inputString.substr(1);
    Token t = Token(UNDEFINED, value, currentLine);
    return t;
}

/**
 * @brief Remove any leading whitespace from the input string.
 */
void Scanner::removeWhitespaceFromInput()
{
    while (inputString.length() > 0 && std::isspace(inputString.at(0)))
    {
        if (inputString.at(0) == '\n')
        {
            currentLine++;
        }
        inputString = inputString.substr(1);
    }
}

////
////
////
//                 Individual token scanners
////

/**
 * @brief Scan for END_OF_FILE token.
 */
MaybeToken Scanner::scanForEOFToken() // END_OF_FILE token
{
    if (inputString.length() == 0)
    {
        return MaybeToken(Token(END_OF_FILE, "", currentLine));
    }
    return MaybeToken();
}

/**
 * @brief Scan for COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, MULTIPLY, and ADD tokens.
 */
MaybeToken Scanner::scanForCharTokens()
{
    char character = inputString.at(0);

    TokenType type = UNDEFINED;
    std::string value = "";
    int lineNumber = currentLine;

    switch (character)
    {
    case ',':
        type = COMMA;
        value = ",";
        break;
    case '.':
        type = PERIOD;
        value = ".";
        break;
    case '?':
        type = Q_MARK;
        value = "?";
        break;
    case '(':
        type = LEFT_PAREN;
        value = "(";
        break;
    case ')':
        type = RIGHT_PAREN;
        value = ")";
        break;
    case '*':
        type = MULTIPLY;
        value = "*";
        break;
    case '+':
        type = ADD;
        value = "+";
        break;
    default:
        break;
    }

    if (type == UNDEFINED)
    {
        return MaybeToken();
    }

    inputString = inputString.substr(1);
    Token token = Token(type, value, lineNumber);
    MaybeToken maybeToken = MaybeToken(token);
    return maybeToken;
}

/**
 * @brief Scan for COLON and COLON_DASH tokens.
 */
MaybeToken Scanner::scanForColonTokens()
{
    if (inputString.at(0) != ':')
    {
        return MaybeToken();
    }

    if (inputString.at(1) == '-')
    {
        Token token = Token(COLON_DASH, ":-", currentLine);
        inputString = inputString.substr(2);
        return MaybeToken(token);
    }
    else
    {
        Token token = Token(COLON, ":", currentLine);
        inputString = inputString.substr(1);
        return MaybeToken(token);
    }
}

/**
 * @brief Scan for STRING token.
 */
MaybeToken Scanner::scanForStringToken()
{
    if (inputString.at(0) != '\'')
    {
        return MaybeToken();
    }

    std::string stringValue = "'";

    bool finishedScan = false;
    int lineNumber = currentLine;
    unsigned int index = 1;
    MaybeToken maybeToken;

    while (!finishedScan)
    {
        if (index >= inputString.length()) // Fail: Unterminated string
        {
            Token token = Token(UNDEFINED, stringValue, lineNumber);
            maybeToken = MaybeToken(token);
            finishedScan = true;
        }

        else if (inputString.at(index) == '\'') // Found single quote
        {
            if (inputString.length() > index + 1 && inputString.at(index + 1) == '\'')
            {
                // Escaped single quote
                stringValue += "''";
                index += 2;
            }
            else
            {
                // End of string
                stringValue += "'";
                index++;
                Token token = Token(STRING, stringValue, lineNumber);
                maybeToken = MaybeToken(token);
                finishedScan = true;
            }
        }

        // Other character
        else
        {
            if (inputString.at(index) == '\n')
            {
                currentLine++;
            }

            stringValue += inputString.at(index);
            index++;
        }
    }

    inputString = inputString.substr(index);
    return maybeToken;
}

/**
 * @brief Scan for COMMENT token.
 */
MaybeToken Scanner::scanForCommentToken()
{
    if (inputString.at(0) != '#')
    {
        return MaybeToken();
    }

    if (inputString.length() > 1 && inputString.at(1) == '|')
    {
        // Block comment
        return scanBlockComment();
    }
    else
    {
        // Line comment
        std::string valueString = "";

        unsigned int index = 0;
        for (; index < inputString.length() && inputString.at(index) != '\n'; index++)
        {
            valueString += inputString.at(index);
        }

        inputString = inputString.substr(index);
        Token token = Token(COMMENT, valueString, currentLine);
        return MaybeToken(token);
    }
}

/**
 * @brief Scan for a block comment token.
 */
MaybeToken Scanner::scanBlockComment()
{
    std::string valueString = "#|";

    bool finishedScan = false;
    int lineNumber = currentLine;
    unsigned int index = 2;
    MaybeToken maybeToken;

    while (!finishedScan)
    {
        if (index >= inputString.length()) // Fail: Unterminated block comment
        {
            Token token = Token(UNDEFINED, valueString, lineNumber);
            maybeToken = MaybeToken(token);
            finishedScan = true;
        }

        else if (inputString.at(index) == '|') // Found pipe symbol
        {
            if (inputString.length() > index + 1 && inputString.at(index + 1) == '#')
            {
                // End of comment
                valueString += "|#";
                index += 2;
                Token token = Token(COMMENT, valueString, lineNumber);
                maybeToken = MaybeToken(token);
                finishedScan = true;
            }
            else
            {
                // Actual '|' char
                valueString += "|";
                index += 2;
            }
        }

        // Other character
        else
        {
            if (inputString.at(index) == '\n')
            {
                currentLine++;
            }

            valueString += inputString.at(index);
            index++;
        }
    }

    inputString = inputString.substr(index);
    return maybeToken;
}

/**
 * @brief Scan for tokens consisting of a single word: ID, SCHEMES, FACTS, RULES, and QUERIES.
 */
MaybeToken Scanner::scanForWordTokens()
{
    if (!std::isalpha(inputString.at(0)))
    {
        return MaybeToken();
    }

    std::string valueString;

    unsigned index = 0;
    for (; index < inputString.length() && std::isalnum(inputString.at(index)); index++)
    {
        valueString += inputString.at(index);
    }

    inputString = inputString.substr(index);

    TokenType type;
    if (valueString == "Schemes")
    {
        type = SCHEMES;
    }
    else if (valueString == "Facts")
    {
        type = FACTS;
    }
    else if (valueString == "Rules")
    {
        type = RULES;
    }
    else if (valueString == "Queries")
    {
        type = QUERIES;
    }
    else
    {
        type = ID;
    }

    Token token = Token(type, valueString, currentLine);
    return MaybeToken(token);
}

#endif
