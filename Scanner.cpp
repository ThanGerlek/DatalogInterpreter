#ifndef PROJECT1_T2K_SCANNER_CPP
#define PROJECT1_T2K_SCANNER_CPP

#include "Scanner.h"

Scanner::Scanner(std::ifstream &ifs)
{
    reachedEOF = false;
    currentLine = 1;

    // Convert ifstream to string
    ifs.seekg(0, std::ios_base::end);                         // offset 0 from end
    input.resize(static_cast<long unsigned>(ifs.tellg()));    // resize string
    ifs.seekg(0, std::ios_base::beg);                         // offset 0 from beginning
    ifs.read(&input[0], static_cast<long int>(input.size())); // read data
}

/**
 * @brief Scan all tokens into the given vector.
 * Throws an error if the vector is nonempty.
 */
void Scanner::scan(std::vector<Token> &tokens)
{
    if (!tokens.empty())
    {
        std::cerr << "[ERROR] Tried to scan into a nonempty vector." << std::endl;
        throw;
    }

    while (hasNext())
    {
        Token token = scanToken();
        if (token.getType() != COMMENT)
        {
            tokens.push_back(token);
        }
    }
}

/**
 * @brief Remove any leading whitespace from the input string.
 */
void Scanner::removeWhitespace()
{
    while (input.length() > 0 && std::isspace(input.at(0)))
    {
        if (input.at(0) == '\n')
        {
            currentLine++;
        }
        input = input.substr(1);
    }
}

/**
 * @brief Return true iff there is more text in the input string to scan.
 */
bool Scanner::hasNext() const
{
    return !reachedEOF;
}

/**
 * @brief Scan a single token, removing it from the input string.
 */
Token Scanner::scanToken()
{
    removeWhitespace();

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
    std::string value = input.substr(0, 1);
    input = input.substr(1);
    Token t = Token(UNDEFINED, value, currentLine);
    return t;
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
    if (input.length() == 0)
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
    char character = input.at(0);

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

    input = input.substr(1);
    Token token = Token(type, value, lineNumber);
    MaybeToken maybeToken = MaybeToken(token);
    return maybeToken;
}

/**
 * @brief Scan for COLON and COLON_DASH tokens.
 */
MaybeToken Scanner::scanForColonTokens()
{
    if (input.at(0) != ':')
    {
        return MaybeToken();
    }

    if (input.at(1) == '-')
    {
        Token token = Token(COLON_DASH, ":-", currentLine);
        input = input.substr(2);
        return MaybeToken(token);
    }
    else
    {
        Token token = Token(COLON, ":", currentLine);
        input = input.substr(1);
        return MaybeToken(token);
    }
}

/**
 * @brief Scan for STRING token.
 */
MaybeToken Scanner::scanForStringToken()
{
    if (input.at(0) != '\'')
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
        if (index >= input.length()) // Fail: Unterminated string
        {
            Token token = Token(UNDEFINED, stringValue, lineNumber);
            maybeToken = MaybeToken(token);
            finishedScan = true;
        }

        else if (input.at(index) == '\'') // Found single quote
        {
            if (input.length() > index + 1 && input.at(index + 1) == '\'')
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
            if (input.at(index) == '\n')
            {
                currentLine++;
            }

            stringValue += input.at(index);
            index++;
        }
    }

    input = input.substr(index);
    return maybeToken;
}

/**
 * @brief Scan for COMMENT token.
 */
MaybeToken Scanner::scanForCommentToken()
{
    if (input.at(0) != '#')
    {
        return MaybeToken();
    }

    if (input.length() > 1 && input.at(1) == '|')
    {
        // Block comment
        return scanBlockComment();
    }
    else
    {
        // Line comment
        std::string valueString = "";

        unsigned int index = 0;
        for (; index < input.length() && input.at(index) != '\n'; index++)
        {
            valueString += input.at(index);
        }

        input = input.substr(index);
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
        if (index >= input.length()) // Fail: Unterminated block comment
        {
            Token token = Token(UNDEFINED, valueString, lineNumber);
            maybeToken = MaybeToken(token);
            finishedScan = true;
        }

        else if (input.at(index) == '|') // Found pipe symbol
        {
            if (input.length() > index + 1 && input.at(index + 1) == '#')
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
            if (input.at(index) == '\n')
            {
                currentLine++;
            }

            valueString += input.at(index);
            index++;
        }
    }

    input = input.substr(index);
    return maybeToken;
}

/**
 * @brief Scan for tokens consisting of a single word: ID, SCHEMES, FACTS, RULES, and QUERIES.
 */
MaybeToken Scanner::scanForWordTokens()
{
    if (!std::isalpha(input.at(0)))
    {
        return MaybeToken();
    }

    std::string valueString;

    unsigned index = 0;
    for (; index < input.length() && std::isalnum(input.at(index)); index++)
    {
        valueString += input.at(index);
    }

    input = input.substr(index);

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
