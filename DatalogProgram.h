#ifndef T2K_236PROJECT_DATALOG_PROGRAM_H
#define T2K_236PROJECT_DATALOG_PROGRAM_H

#include <vector>
#include "Rule.h"

class DatalogProgram
{
public:
    DatalogProgram(){};
    ~DatalogProgram(){};

    void addScheme(Predicate scheme);
    void addFact(Predicate fact);
    void addQuery(Predicate query);
    void addRule(Rule rule);

    const std::vector<Predicate> *getSchemes() { return &schemes; };
    const std::vector<Predicate> *getFacts() { return &facts; };
    const std::vector<Predicate> *getQueries() { return &queries; };
    const std::vector<Rule> *getRules() { return &rules; };

private:
    std::vector<Predicate> schemes;
    std::vector<Predicate> facts;
    std::vector<Predicate> queries;
    std::vector<Rule> rules;
};

#endif
