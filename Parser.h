#ifndef T2K_236PROJECT_PARSER_H
#define T2K_236PROJECT_PARSER_H

#include <stack>
#include "Scanner.h"
#include "DatalogProgram.h"

class Parser
{
public:
    Parser(const std::vector<Token> *_tokens, DatalogProgram *_program) : tokens(_tokens), program(_program), nextTokenIndex(0), max_nextTokenIndex(0){};
    ~Parser(){};
    void parse();

private:
    const std::vector<Token> *tokens;
    DatalogProgram *program;
    unsigned int nextTokenIndex;     // Index of the next token
    unsigned int max_nextTokenIndex; // Index of the farthest token reached (used for failure reporting)
    std::stack<unsigned int> savedLocations;

    TokenType tokenType();
    std::string tokenStr();
    void advanceToken();
    void throwError();
    void match(TokenType t);

    void saveLocation();
    void restoreLocation();

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
