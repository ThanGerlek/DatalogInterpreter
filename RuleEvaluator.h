#ifndef CS236_PROJECT5_T2K_DATALOG_RULE_EVALUATOR_H
#define CS236_PROJECT5_T2K_DATALOG_RULE_EVALUATOR_H

#include "DatalogDatabase.h"
#include "Graph.h"

class RuleEvaluator
{
public:
    RuleEvaluator(DatalogDatabase &_database, const Graph &_dependencyGraph) : database(_database), dependencyGraph(_dependencyGraph){};
    void evaluate();

private:
    DatalogDatabase &database;
    const Graph &dependencyGraph;

    static const std::set<Rule> convertNodeSetToRuleSet(std::set<Node> clique,
                                                 DatalogDatabase database);
    void evaluateRuleSet(const std::set<Rule> &rules);
    void evaluateRule(Rule rule);
    const Relation evaluateRulePredicates(Rule rule) const;
    const Relation evaluateRulePredicate(Predicate predicate) const;
    void printRuleResult(Rule rule, Relation results) const;
    //
};

#endif
