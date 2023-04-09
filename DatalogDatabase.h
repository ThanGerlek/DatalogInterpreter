#ifndef CS236_PROJECT3_T2K_DATALOG_DATABASE_H
#define CS236_PROJECT3_T2K_DATALOG_DATABASE_H

#include "Database.h"
#include "DatalogProgram.h"

class DatalogDatabase : public Database
{
private:
    DatalogProgram *dlProgram;

    void evaluateRule(Rule rule);
    const Relation evaluateRulePredicates(Rule rule) const;
    const Relation evaluateRulePredicate(Predicate predicate) const;

    void printQueryResult(Predicate query, Relation results) const;
    void printRuleResult(Rule rule, Relation results) const;

public:
    DatalogDatabase(DatalogProgram *_dlProgram) : dlProgram(_dlProgram){};
    void evaluateSchemes();
    void evaluateFacts();
    void evaluateQueries();

    const Relation projectForRule(const Relation &relation, Rule rule) const;

    const Relation selectForPredicate(Relation relation, Predicate predicate) const;
    const Relation projectForPredicate(Relation relation, Predicate predicate) const;
    const Relation renameForPredicate(Relation relation, Predicate predicate) const;
    std::vector<unsigned int> getProjectedIndices(const std::vector<Parameter> *params) const;

    std::string toString() const;
};

#endif
