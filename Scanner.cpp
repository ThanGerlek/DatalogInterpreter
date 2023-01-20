#ifndef PROJECT1_T2K_SCANNER_CPP
#define PROJECT1_T2K_SCANNER_CPP

#include "Scanner.h"

Token Scanner::scanToken()
{
    TokenType type = UNDEFINED;
    std::string value = "";
    int line = -1;

    // Remove leading whitespace
    while (std::isspace(this->input.at(0)))
    {
        this->input = this->input.substr(1);
    }

    // TODO Token checking

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

#endif
