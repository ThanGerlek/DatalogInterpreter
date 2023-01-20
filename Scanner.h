#ifndef PROJECT1_T2K_SCANNER_H
#define PROJECT1_T2K_SCANNER_H

#include <vector>
#include "Token.h"

class Scanner
{
private:
    std::string input;
    std::vector<Token> tokens;

public:
    Scanner(const std::string &input) : input(input){};

    Token scanToken()
    {
        TokenType type = COMMA;
        std::string value = ",";
        int line = 1;

        // TODO

        return Token(type, value, line);
    }
};

#endif
