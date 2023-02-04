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
 * Scan all tokens into the given vector.
 * Throws an error if the vector is nonempty.
 */
void Scanner::scan(std::vector<Token> &tokens)
{
    if (!tokens.empty())
    {
        std::string msg = "Error: tried to scan into a nonempty vector.";
        std::cout << msg << std::endl;
        throw std::invalid_argument(msg);
    }

    while (hasNext())
    {
        tokens.push_back(scanToken());
    }
}

/**
 * Remove any leading whitespace from the input string.
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
 * Return true iff there is more text in the input string to scan.
 */
bool Scanner::hasNext()
{
    return !reachedEOF;
}

/**
 * Scan a single token, removing it from the input string.
 */
Token Scanner::scanToken()
{
    removeWhitespace();

    // TODO Order calls according to frequency

    MaybeToken mToken = scanForEOFToken(); // END_OF_FILE token
    if (mToken.hasToken())
    {
        Token t = mToken.getToken();
        reachedEOF = true;
        return t;
    }

    mToken = scanForCharTokens(); // COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, ADD, and MULTIPLY tokens
    if (mToken.hasToken())
    {
        Token t = mToken.getToken();
        return t;
    }

    mToken = scanForColonTokens(); // COLON and COLON_DASH tokens
    if (mToken.hasToken())
    {
        Token t = mToken.getToken();
        return t;
    }

    mToken = scanForWordTokens();
    if (mToken.hasToken())
    {
        Token t = mToken.getToken();
        return t;
    }

    mToken = scanForStringToken(); // STRING token
    if (mToken.hasToken())
    {
        Token t = mToken.getToken();
        return t;
    }

    mToken = scanForCommentToken(); // COMMENT token
    if (mToken.hasToken())
    {
        Token t = mToken.getToken();
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
 * Scan for END_OF_FILE token.
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
 * Scan for COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, MULTIPLY, and ADD tokens.
 */
MaybeToken Scanner::scanForCharTokens()
{
    char c = input.at(0);

    TokenType type = UNDEFINED;
    std::string value = "";
    int line = currentLine;

    switch (c)
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
    Token token = Token(type, value, line);
    MaybeToken mToken = MaybeToken(token);
    return mToken;
}

/**
 * Scan for COLON and COLON_DASH tokens.
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
 * Scan for STRING token.
 */
MaybeToken Scanner::scanForStringToken()
{
    if (input.at(0) != '\'')
    {
        return MaybeToken();
    }

    std::stringstream ss;
    ss << "'";

    bool finishedScan = false;
    int line = currentLine;
    unsigned uindex = 1;
    MaybeToken mt;

    while (!finishedScan)
    {
        if (uindex >= input.length()) // Fail: Unterminated string
        {
            Token token = Token(UNDEFINED, ss.str(), line);
            mt = MaybeToken(token);
            finishedScan = true;
        }

        else if (input.at(uindex) == '\'') // Found single quote
        {
            if (input.length() > uindex + 1 && input.at(uindex + 1) == '\'')
            {
                // Escaped single quote
                ss << "''";
                uindex += 2;
            }
            else
            {
                // End of string
                ss << "'";
                uindex++;
                Token token = Token(STRING, ss.str(), line);
                mt = MaybeToken(token);
                finishedScan = true;
            }
        }

        // Other character
        else
        {
            if (input.at(uindex) == '\n')
            {
                currentLine++;
            }

            ss << input.at(uindex);
            uindex++;
        }
    }

    input = input.substr(uindex);
    return mt;
}

/**
 * Scan for COMMENT token.
 */
MaybeToken Scanner::scanForCommentToken()
{
    if (input.at(0) != '#')
    {
        return MaybeToken();
    }

    if (static_cast<int>(input.length()) > 1 && input.at(1) == '|')
    {
        // Block comment
        return scanBlockComment();
    }
    else
    {
        // Line comment
        std::stringstream ss;

        unsigned uindex = 0;
        for (; uindex < input.length() && input.at(uindex) != '\n'; uindex++)
        {
            ss << input.at(uindex);
        }

        input = input.substr(uindex);
        Token token = Token(COMMENT, ss.str(), currentLine);
        return MaybeToken(token);
    }
}

/**
 * Scan for a block comment token.
 */
MaybeToken Scanner::scanBlockComment()
{
    std::stringstream ss;
    ss << "#|";

    bool finishedScan = false;
    int line = currentLine;
    unsigned uindex = 2;
    MaybeToken mt;

    while (!finishedScan)
    {
        if (uindex >= input.length()) // Fail: Unterminated block comment
        {
            Token token = Token(UNDEFINED, ss.str(), line);
            mt = MaybeToken(token);
            finishedScan = true;
        }

        else if (input.at(uindex) == '|') // Found pipe symbol
        {
            if (input.length() > uindex + 1 && input.at(uindex + 1) == '#')
            {
                // End of comment
                ss << "|#";
                uindex += 2;
                Token token = Token(COMMENT, ss.str(), line);
                mt = MaybeToken(token);
                finishedScan = true;
            }
            else
            {
                // Actual '|' char
                ss << "|";
                uindex += 2;
            }
        }

        // Other character
        else
        {
            if (input.at(uindex) == '\n')
            {
                currentLine++;
            }

            ss << input.at(uindex);
            uindex++;
        }
    }

    input = input.substr(uindex);
    return mt;
}

/**
 * Scan for tokens consisting of a single word: ID, SCHEMES, FACTS, RULES, and QUERIES.
 */
MaybeToken Scanner::scanForWordTokens()
{
    if (!std::isalpha(input.at(0)))
    {
        return MaybeToken();
    }

    std::stringstream ss;

    unsigned uindex = 0;
    for (; uindex < input.length() && std::isalnum(input.at(uindex)); uindex++)
    {
        ss << input.at(uindex);
    }

    input = input.substr(uindex);
    std::string value = ss.str();

    TokenType type;
    if (value == "Schemes")
    {
        type = SCHEMES;
    }
    else if (value == "Facts")
    {
        type = FACTS;
    }
    else if (value == "Rules")
    {
        type = RULES;
    }
    else if (value == "Queries")
    {
        type = QUERIES;
    }
    else
    {
        type = ID;
    }

    Token token = Token(type, value, currentLine);
    return MaybeToken(token);
}

#endif
