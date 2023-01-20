#ifndef PROJECT1_T2K_SCANNER_H
#define PROJECT1_T2K_SCANNER_H

#include <cctype>
#include <vector>
#include "Token.h"

class Scanner
{
private:
    std::string input;
    std::vector<Token> tokens;
    int currentLine;

public:
    Scanner(const std::string &input) : input(input), currentLine(1){};

    Token scanToken()
    {
        TokenType type = UNDEFINED;
        std::string value = "";
        int line = -1;

        // Remove leading whitespace
        while (std::isspace(this->input.at(0)))
        {
            this->input = this->input.substr(1);
        }

        // TODO

        // Check for COMMA token
        if (input.at(0) == ',')
        {
            type = COMMA;
            value = ",";
            line = currentLine;

            // Prep for next token
            currentLine++;
            input = input.substr(1);
        }

        return Token(type, value, line);
    }
};

#endif
