#ifndef CS236_PROJECT3_T2K_DATALOG_DATABASE_H
#define CS236_PROJECT3_T2K_DATALOG_DATABASE_H

#include "Database.h"
#include "DatalogProgram.h"

class DatalogDatabase : public Database
{
private:
    DatalogProgram *dlProgram;

    bool hasEvaluatedQueries;

    void evaluateSchemes();
    void evaluateFacts();
    void evaluateRules();
    void evaluateQueries();

    void evaluateRule(Rule rule);
    const Relation evaluateRulePredicates(Rule rule) const;
    const Relation evaluateRulePredicate(Predicate predicate) const;
    const Relation projectRuleColumns(const Relation &relation, Rule rule) const;

    const Relation selectForPredicate(Relation relation, const std::vector<Parameter> *params) const;
    std::vector<unsigned int> getProjectedIndices(const std::vector<Parameter> *params) const;
    const Relation projectForPredicate(Relation relation, std::vector<unsigned int> projectedIndices) const;
    const Relation renameForPredicate(Relation relation, const std::vector<Parameter> *params, std::vector<unsigned int> projectedIndices) const;

    void printQueryResult(Predicate query, Relation results);
    void printRuleResult(Rule rule, Relation results);

public:
    DatalogDatabase(DatalogProgram *_dlProgram) : dlProgram(_dlProgram), hasEvaluatedQueries(false){};
    void evaluate();
    std::string toString() const;
};

#endif
