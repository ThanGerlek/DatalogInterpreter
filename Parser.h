#ifndef T2K_236PROJECT_PARSER_H
#define T2K_236PROJECT_PARSER_H

#include "Scanner.h"
#include "DatalogProgram.h"

class Parser
{
public:
    Parser(const std::vector<Token> &tokens, DatalogProgram &program){};
    ~Parser(){};
    void parse();

private:
    // Recursive descent grammar functions
};

#endif
