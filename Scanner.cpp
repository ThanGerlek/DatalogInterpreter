#ifndef PROJECT1_T2K_SCANNER_CPP
#define PROJECT1_T2K_SCANNER_CPP

#include "Scanner.h"

Token Scanner::scanToken()
{
    // Remove leading whitespace
    while (std::isspace(input.at(0)))
    {
        if (input.at(0) == '\n')
        {
            currentLine++;
        }
        input = input.substr(1);
    }

    // TODO Token checking

    // Check for char token
    MaybeToken mToken = scanForCharToken();
    if (mToken.hasToken())
    {
        Token t = mToken.getToken();
        return t;
    }

    std::string value = input.substr(0, 1);
    Token t = Token(UNDEFINED, value, currentLine);
    return t;
}

MaybeToken Scanner::scanForCharToken()
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

#endif
