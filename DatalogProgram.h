#ifndef T2K_236PROJECT_DATALOG_PROGRAM_H
#define T2K_236PROJECT_DATALOG_PROGRAM_H

#include <set>
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
    void addToDomain(Parameter param);

private:
    const std::vector<Predicate> *getSchemes() const;
    const std::vector<Predicate> *getFacts() const;
    const std::vector<Predicate> *getQueries() const;
    const std::vector<Rule> *getRules() const;
    const std::set<Parameter> *getDomain() const;

    std::vector<Predicate> schemes;
    std::vector<Predicate> facts;
    std::vector<Predicate> queries;
    std::vector<Rule> rules;
    std::set<Parameter> domain;
};

#endif
