#ifndef T2K_236PROJECT_DATALOG_PROGRAM_H
#define T2K_236PROJECT_DATALOG_PROGRAM_H

#include <vector>
#include "Rule.h"

class DatalogProgram
{
public:
    DatalogProgram(){};
    ~DatalogProgram(){};

    void addScheme(Predicate scheme) { schemes.push_back(scheme); };
    void addFact(Predicate fact) { facts.push_back(fact); };
    void addQuery(Predicate query) { queries.push_back(query); };
    void addRule(Rule rule) { rules.push_back(rule); };

    std::vector<Predicate> *getSchemes() { return &schemes; };
    std::vector<Predicate> *getFacts() { return &facts; };
    std::vector<Predicate> *getQueries() { return &queries; };
    std::vector<Rule> *getRules() { return &rules; };

private:
    std::vector<Predicate> schemes;
    std::vector<Predicate> facts;
    std::vector<Predicate> queries;
    std::vector<Rule> rules;
};

#endif
