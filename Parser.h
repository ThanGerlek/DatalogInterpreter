#ifndef T2K_236PROJECT_PARSER_H
#define T2K_236PROJECT_PARSER_H

#include <stack>
#include "Scanner.h"
#include "DatalogProgram.h"

class Parser
{
public:
    Parser(const std::vector<Token> *_tokens, DatalogProgram *_program) : tokens(_tokens), program(_program){};
    ~Parser(){};
    void parse();

private:
    const std::vector<Token> *tokens;
    DatalogProgram *program;
    int location; // Index of the next token
    std::stack<int> savedLocs;

    void saveLoc();
    void restoreLoc();

    // Recursive descent grammar functions
    bool datalogProgram() const;
    bool schemeList() const;
    bool factList() const;
    bool ruleList() const;
    bool queryList() const;
    bool scheme() const;
    bool fact() const;
    bool rule() const;
    bool query() const;
    bool headPredicate() const;
    bool predicate() const;
    bool predicateList() const;
    bool parameterList() const;
    bool stringList() const;
    bool idList() const;
    bool parameter() const;
};

#endif
