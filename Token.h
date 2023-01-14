#ifndef PROJECT1_T2K_TOKEN_H
#define PROJECT1_T2K_TOKEN_H

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
    TokenType type;
    std::string value;
    int line;

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

        throw "Unrecognized token type.";
    }

public:
    Token(TokenType type, std::string value, int line) : type(type), value(value), line(line){};

    std::string toString() const
    {
        std::stringstream out;
        out << "(" << typeName(type) << ","
            << "\"" << value << "\""
            << "," << line << ")";
        return out.str();
    }
};

#endif
