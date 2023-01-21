#ifndef PROJECT1_T2K_SCANNER_CPP
#define PROJECT1_T2K_SCANNER_CPP

#include "Scanner.h"

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
    removeWhitespace();
    return input.length() > 0;
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
        std::cout << "Found EOF token: ";
        Token t = mToken.getToken();
        return t;
    }

    mToken = scanForCharTokens(); // COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, ADD, and MULTIPLY tokens
    if (mToken.hasToken())
    {
        std::cout << "Found char token: ";
        Token t = mToken.getToken();
        return t;
    }

    mToken = scanForColonTokens(); // COLON and COLON_DASH tokens
    if (mToken.hasToken())
    {
        std::cout << "Found colon or colon_dash token: ";
        Token t = mToken.getToken();
        return t;
    }

    // mToken = scanForSchemesToken(); // SCHEMES token
    // if (mToken.hasToken())
    // {
    //     std::cout << "Found schemes token: ";
    //     Token t = mToken.getToken();
    //     return t;
    // }

    // mToken = scanForFactsToken(); // FACTS token
    // if (mToken.hasToken())
    // {
    //     std::cout << "Found facts token: ";
    //     Token t = mToken.getToken();
    //     return t;
    // }

    // mToken = scanForRulesToken(); // RULES token
    // if (mToken.hasToken())
    // {
    //     std::cout << "Found rules token: ";
    //     Token t = mToken.getToken();
    //     return t;
    // }

    // mToken = scanForQueriesToken(); // QUERIES token
    // if (mToken.hasToken())
    // {
    //     std::cout << "Found queries token: ";
    //     Token t = mToken.getToken();
    //     return t;
    // }

    mToken = scanForWordTokens();
    if (mToken.hasToken())
    {
        std::cout << "Found word token: ";
        Token t = mToken.getToken();
        return t;
    }

    mToken = scanForStringToken(); // STRING token
    if (mToken.hasToken())
    {
        std::cout << "Found string token: ";
        Token t = mToken.getToken();
        return t;
    }

    mToken = scanForCommentToken(); // COMMENT token
    if (mToken.hasToken())
    {
        std::cout << "Found comment token: ";
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

// /**
//  * Scan for a token whose value is the given string.
//  * Called by SCHEMES, FACTS, RULES, and QUERIES token scanners.
//  */
// MaybeToken Scanner::scanForKeywordTokens(TokenType type, std::string &value)
// {
//     // Fail if input doesn't begin with value
//     if (input.length() < value.length() || input.substr(0, value.length()) != value)
//     {
//         return MaybeToken();
//     }

//     // Fail if the first character following value is not a whitespace
//     if (input.length() > value.length() && !std::isspace(input.at(value.length())))
//     {
//         return MaybeToken();
//     }

//     input = input.substr(value.length());
//     Token token = Token(type, value, currentLine);
//     return MaybeToken(token);
// }

// /**
//  * Scan for SCHEMES token.
//  */
// MaybeToken Scanner::scanForSchemesToken()
// {
//     std::string value = "Schemes";
//     return scanForKeywordTokens(SCHEMES, value);
// }

// /**
//  * Scan for FACTS token.
//  */
// MaybeToken Scanner::scanForFactsToken()
// {
//     std::string value = "Facts";
//     return scanForKeywordTokens(FACTS, value);
// }

// /**
//  * Scan for RULES token.
//  */
// MaybeToken Scanner::scanForRulesToken()
// {
//     std::string value = "Rules";
//     return scanForKeywordTokens(RULES, value);
// }

// /**
//  * Scan for QUERIES token.
//  */
// MaybeToken Scanner::scanForQueriesToken()
// {
//     std::string value = "Queries";
//     return scanForKeywordTokens(QUERIES, value);
// }

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
    int index = 1;
    MaybeToken mt;

    while (!finishedScan)
    {
        if (index >= static_cast<int>(input.length())) // Fail: Unterminated string
        {
            Token token = Token(UNDEFINED, ss.str(), line);
            mt = MaybeToken(token);
            finishedScan = true;
        }

        else if (input.at(index) == '\'') // Found single quote
        {
            if (static_cast<int>(input.length()) > index + 1 && input.at(index + 1) == '\'')
            {
                // Escaped single quote
                ss << "''";
                index += 2;
            }
            else
            {
                // End of string
                ss << "'";
                index++;
                Token token = Token(STRING, ss.str(), line);
                mt = MaybeToken(token);
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

            ss << input.at(index);
            index++;
        }
    }

    input = input.substr(index);
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

        int index = 0;
        for (; index < static_cast<int>(input.length()) && input.at(index) != '\n'; index++)
        {
            ss << input.at(index);
        }

        input = input.substr(index);
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
    int index = 2;
    MaybeToken mt;

    while (!finishedScan)
    {
        if (index >= static_cast<int>(input.length())) // Fail: Unterminated block comment
        {
            Token token = Token(UNDEFINED, ss.str(), line);
            mt = MaybeToken(token);
            finishedScan = true;
        }

        else if (input.at(index) == '|') // Found pipe symbol
        {
            if (static_cast<int>(input.length()) > index + 1 && input.at(index + 1) == '#')
            {
                // End of comment
                ss << "|#";
                index += 2;
                Token token = Token(STRING, ss.str(), line);
                mt = MaybeToken(token);
                finishedScan = true;
            }
            else
            {
                // Actual '|' char
                ss << "|";
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

            ss << input.at(index);
            index++;
        }
    }

    input = input.substr(index);
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

    int index = 0;
    for (; index < static_cast<int>(input.length()) && std::isalnum(input.at(index)); index++)
    {
        ss << input.at(index);
    }

    input = input.substr(index);
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
