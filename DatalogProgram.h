#ifndef T2K_236PROJECT_DATALOG_PROGRAM_H
#define T2K_236PROJECT_DATALOG_PROGRAM_H

#include <vector>
#include "Rule.h"

// TODO domain list

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

    const std::vector<Predicate> *getSchemes() const;
    const std::vector<Predicate> *getFacts() const;
    const std::vector<Predicate> *getQueries() const;
    const std::vector<Rule> *getRules() const;

private:
    std::vector<Predicate> schemes;
    std::vector<Predicate> facts;
    std::vector<Predicate> queries;
    std::vector<Rule> rules;
    std::vector<std::string> domain;
};

#endif
