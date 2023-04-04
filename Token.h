#ifndef PROJECT1_T2K_TOKEN_H
#define PROJECT1_T2K_TOKEN_H

#include <iostream>
#include <string>
#include <sstream>

// TODO. Polymorphism-ify

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
    TokenType type;
    std::string value;
    int lineNumber;

public:
    Token(TokenType _type, std::string _value, int _lineNumber) : type(_type), value(_value), lineNumber(_lineNumber){};
    Token() : type(UNDEFINED), value(""), lineNumber(-1){};

    /**
     * @brief Get a string representation of a TokenType.
     */
    static std::string typeName(TokenType _type)
    {
        switch (_type)
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
        default:
            std::cerr << "[ERROR] Unrecognized token type: '" << static_cast<int>(_type) << "'" << std::endl;
            throw;
        }
    }

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
        return lineNumber;
    }

    std::string toString() const
    {
        std::stringstream out;
        out << "(" << typeName(type) << ","
            << "\"" << value << "\""
            << "," << lineNumber << ")";
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
    Token token;
    bool isToken;

public:
    MaybeToken() : isToken(false){};
    MaybeToken(Token _token) { setToken(_token); };
    bool hasToken() { return isToken; }

    Token getToken()
    {
        if (!hasToken())
        {
            std::cerr << "[ERROR] Tried to call getToken() on a MaybeToken with no token." << std::endl;
            throw;
        }
        return token;
    }

    void setToken(Token _token)
    {
        token = Token(_token.getType(), _token.getValue(), _token.getLine());
        isToken = true;
    }
};

#endif
