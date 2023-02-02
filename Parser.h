#ifndef T2K_236PROJECT_PARSER_H
#define T2K_236PROJECT_PARSER_H

#include <stack>
#include "Scanner.h"
#include "DatalogProgram.h"

class Parser
{
public:
    Parser(const std::vector<Token> *_tokens, DatalogProgram *_program) : tokens(_tokens), program(_program), location(0){};
    ~Parser(){};
    void parse();

private:
    const std::vector<Token> *tokens;
    DatalogProgram *program;
    int location; // Index of the next token
    std::stack<int> savedLocs;

    TokenType tokenType();
    void advanceToken();
    void throwError();
    void match(TokenType t);

    void saveLoc();
    void restoreLoc();

    // Recursive descent grammar functions
    bool datalogProgram();
    bool schemeList();
    bool factList();
    bool ruleList();
    bool queryList();
    bool scheme();
    bool fact();
    bool rule();
    bool query();
    bool headPredicate();
    bool predicate();
    bool predicateList();
    bool parameterList();
    bool stringList();
    bool idList();
    bool parameter();
};

#endif
