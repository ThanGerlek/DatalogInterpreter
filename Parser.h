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
    // TODO set to private
    // private:
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
    void datalogProgram();
    void schemeList();
    void factList();
    void ruleList();
    void queryList();
    void scheme();
    void fact();
    void rule();
    void query();
    void headPredicate();
    void predicate();
    void predicateList();
    void parameterList();
    void stringList();
    void idList();
    void parameter();
};

#endif
