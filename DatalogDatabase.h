#ifndef CS236_PROJECT3_T2K_DATALOG_DATABASE_H
#define CS236_PROJECT3_T2K_DATALOG_DATABASE_H

#include "Database.h"
#include "DatalogProgram.h"
#include "QueryResult.h"

class DatalogDatabase : public Database
{
private:
    DatalogProgram *dlProgram;

    bool hasEvaluatedQueries;
    std::vector<QueryResult> queryResults;

    void evaluateSchemes();
    void evaluateFacts();
    void evaluateRules();
    void evaluateQueries();

    void evaluateRule(Rule rule);
    const Relation evaluateRulePredicates(Rule rule) const;
    const Relation DatalogDatabase::evaluateRulePredicate(
        Predicate predicate) const;
    const Relation DatalogDatabase::projectRuleColumns(const Relation &relation, Rule rule) const;

    const Relation selectForPredicate(Relation relation, const std::vector<Parameter> *params) const;
    std::vector<unsigned int> getProjectedIndices(const std::vector<Parameter> *params) const;
    const Relation projectForQuery(Relation relation, std::vector<unsigned int> projectedIndices) const;
    const Relation renameForQuery(Relation relation, const std::vector<Parameter> *params, std::vector<unsigned int> projectedIndices) const;

public:
    DatalogDatabase(DatalogProgram *_dlProgram) : dlProgram(_dlProgram), hasEvaluatedQueries(false){};
    void evaluate();
    void printQueries() const;
    std::string toString() const;
};

#endif
