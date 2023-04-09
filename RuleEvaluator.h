#ifndef CS236_PROJECT5_T2K_DATALOG_RULE_EVALUATOR_H
#define CS236_PROJECT5_T2K_DATALOG_RULE_EVALUATOR_H

#include "DatalogDatabase.h"
#include "Graph.h"

class RuleEvaluator
{
public:
    static void evaluate(const DatalogDatabase &database,
                         const Graph &dependencyGraph);

private:
    DatalogDatabase &database;
    RuleEvaluator(DatalogDatabase &_database) : database(_database){};

    void evaluateRuleSet(const std::vector<Rule> &rules);
    void evaluateRule(Rule rule);
    const Relation evaluateRulePredicates(Rule rule) const;
    const Relation evaluateRulePredicate(Predicate predicate) const;
    void printRuleResult(Rule rule, Relation results) const;
    //
};

#endif
