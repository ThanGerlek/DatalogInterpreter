#ifndef T2K_236PROJECT_DATALOG_PROGRAM_H
#define T2K_236PROJECT_DATALOG_PROGRAM_H

#include <vector>
#include "Rule.h"

class DatalogProgram
{
public:
    DatalogProgram(){};
    ~DatalogProgram(){};
    std::string toString();

    void addScheme(Predicate scheme);
    void addFact(Predicate fact);
    void addQuery(Predicate query);
    void addRule(Rule rule);

    std::vector<Predicate> *getSchemes();
    std::vector<Predicate> *getFacts();
    std::vector<Predicate> *getQueries();
    std::vector<Rule> *getRules();

private:
    std::vector<Predicate> schemes;
    std::vector<Predicate> facts;
    std::vector<Predicate> queries;
    std::vector<Rule> rules;
};

#endif
