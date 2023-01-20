#ifndef PROJECT1_T2K_SCANNER_CPP
#define PROJECT1_T2K_SCANNER_CPP

#include "Scanner.h"

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

bool Scanner::hasNext()
{
    removeWhitespace();
    return input.length() > 0;
}

Token Scanner::scanToken()
{
    removeWhitespace();

    // TODO! Token checking

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

    mToken = scanForSchemesToken(); // SCHEMES token
    if (mToken.hasToken())
    {
        std::cout << "Found schemes token: ";
        Token t = mToken.getToken();
        return t;
    }

    mToken = scanForFactsToken(); // FACTS token
    if (mToken.hasToken())
    {
        std::cout << "Found facts token: ";
        Token t = mToken.getToken();
        return t;
    }

    mToken = scanForRulesToken(); // RULES token
    if (mToken.hasToken())
    {
        std::cout << "Found rules token: ";
        Token t = mToken.getToken();
        return t;
    }

    mToken = scanForQueriesToken(); // QUERIES token
    if (mToken.hasToken())
    {
        std::cout << "Found queries token: ";
        Token t = mToken.getToken();
        return t;
    }

    mToken = scanForIdToken(); // ID token
    if (mToken.hasToken())
    {
        std::cout << "Found id token: ";
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

    // TODO Finish UNDEFINED token (handler function?)
    std::string value = input.substr(0, 1);
    input = input.substr(1);
    Token t = Token(UNDEFINED, value, currentLine);
    return t;
}

MaybeToken Scanner::scanForEOFToken() // END_OF_FILE token
{
    if (input.length() == 0 /*|| input.at(0) == 'EOF'*/)
    {
        return MaybeToken(Token(END_OF_FILE, "", currentLine));
    }
    return MaybeToken();
}

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

// TODO
//     COLON,
//     COLON_DASH,

//     SCHEMES,
//     FACTS,
//     RULES,
//     QUERIES,
//     ID,
//     STRING,
//     COMMENT,
//     UNDEFINED,

//     END_OF_FILE

MaybeToken Scanner::scanForColonTokens() // COLON and COLON_DASH tokens
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

MaybeToken Scanner::scanForSchemesToken() // SCHEMES token
{
    return MaybeToken();
    //
}

MaybeToken Scanner::scanForFactsToken() // FACTS token
{
    return MaybeToken();
    //
}

MaybeToken Scanner::scanForRulesToken() // RULES token
{
    return MaybeToken();
    //
}

MaybeToken Scanner::scanForQueriesToken() // QUERIES token
{
    return MaybeToken();
    //
}

MaybeToken Scanner::scanForIdToken() // ID token
{
    return MaybeToken();
    //
}

MaybeToken Scanner::scanForStringToken() // STRING token
{
    return MaybeToken();
    //
}
MaybeToken Scanner::scanForCommentToken() // COMMENT token
{
    return MaybeToken();
    //
}

MaybeToken Scanner::scanForUndefinedToken() // UNDEFINED token
{
    return MaybeToken();
    //
}

#endif
