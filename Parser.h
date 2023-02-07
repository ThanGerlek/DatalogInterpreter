#ifndef T2K_236PROJECT_PARSER_H
#define T2K_236PROJECT_PARSER_H

#include <stack>
#include "Scanner.h"
#include "DatalogProgram.h"

class Parser
{
public:
    Parser(const std::vector<Token> *_tokens, DatalogProgram *_program) : tokens(_tokens), program(_program), u_location(0), u_max_location(0){};
    ~Parser(){};
    void parse();

private:
    const std::vector<Token> *tokens;
    DatalogProgram *program;
    unsigned u_location;     // Index of the next token
    unsigned u_max_location; // Index of the farthest token reached (used for failure reporting)
    std::stack<unsigned> savedLocs;

    TokenType tokenType();
    std::string tokenStr();
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
    Predicate headPredicate();
    Predicate predicate();
    void predicateList(Rule &currentRule);
    void parameterList(Predicate &currentPredicate);
    void stringList(Predicate &currentPredicate);
    void idList(Predicate &currentPredicate);
    Parameter parameter();
};

#endif
