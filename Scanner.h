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
    Token scanToken();
};

#endif
