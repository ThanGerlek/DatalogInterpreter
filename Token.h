#ifndef PROJECT1_T2K_TOKEN_H
#define PROJECT1_T2K_TOKEN_H

#include <iostream>
#include <string>
#include <sstream>

enum TokenType
{
    COMMA,
    PERIOD,
    Q_MARK,
    LEFT_PAREN,
    RIGHT_PAREN,
    COLON,
    COLON_DASH,
    MULTIPLY,
    ADD,
    SCHEMES,
    FACTS,
    RULES,
    QUERIES,
    ID,
    STRING,
    COMMENT,
    UNDEFINED,
    END_OF_FILE

};

class Token
{
private:
    const TokenType type;
    const std::string value;
    const int line;

    std::string typeName(TokenType type) const
    {
        switch (type)
        {
        case COMMA:
            return "COMMA";
        case PERIOD:
            return "PERIOD";
        case Q_MARK:
            return "Q_MARK";
        case LEFT_PAREN:
            return "LEFT_PAREN";
        case RIGHT_PAREN:
            return "RIGHT_PAREN";
        case COLON:
            return "COLON";
        case COLON_DASH:
            return "COLON_DASH";
        case MULTIPLY:
            return "MULTIPLY";
        case ADD:
            return "ADD";
        case SCHEMES:
            return "SCHEMES";
        case FACTS:
            return "FACTS";
        case RULES:
            return "RULES";
        case QUERIES:
            return "QUERIES";
        case ID:
            return "ID";
        case STRING:
            return "STRING";
        case COMMENT:
            return "COMMENT";
        case UNDEFINED:
            return "UNDEFINED";
        case END_OF_FILE:
            return "EOF";
        }

        std::cout << "ERROR: Unrecognized token type." << std::endl;
        throw;
    }

public:
    Token(TokenType type, std::string value, int line) : type(type), value(value), line(line){};
    Token() : type(UNDEFINED), value(""), line(-1){};

    TokenType getType() const
    {
        return type;
    }

    std::string getValue() const
    {
        return value;
    }

    int getLine() const
    {
        return line;
    }

    std::string toString() const
    {
        std::stringstream out;
        out << "(" << typeName(type) << ","
            << "\"" << value << "\""
            << "," << line << ")";
        return out.str();
    }
};

////
////
////
////

// Token wrapper with an additional "hasToken() == false" state
struct MaybeToken
{
private:
    Token *tokenPtr;

public:
    MaybeToken() : tokenPtr(NULL){};
    MaybeToken(Token token)
    {
        setToken(token);
    };

    ~MaybeToken()
    {
        if (tokenPtr)
        {
            delete tokenPtr;
        }
    }

    bool hasToken()
    {
        return tokenPtr != NULL;
    }

    Token getToken()
    {
        if (!hasToken())
        {
            std::cout << "ERROR: Tried to call getToken() on a MaybeToken with no token." << std::endl;
            throw;
        }
        return *tokenPtr;
    }

    void setToken(Token token)
    {
        tokenPtr = new Token(token.getType(), token.getValue(), token.getLine());
    }
};

#endif
