#ifndef CS236_PROJECT5_T2K_DATALOG_RULE_EVALUATOR_H
#define CS236_PROJECT5_T2K_DATALOG_RULE_EVALUATOR_H

#include "DatalogDatabase.h"
#include "Graph.h"
#include "StronglyConnectedComponent.h"

class RuleEvaluator
{
public:
    RuleEvaluator(DatalogDatabase &_database,
                  const DatalogProgram &_program,
                  Graph &_dependencyGraph)
        : database(_database),
          program(_program),
          dependencyGraph(_dependencyGraph){};

    void evaluateRules();

private:
    DatalogDatabase &database;
    const DatalogProgram &program;
    Graph &dependencyGraph;

    const std::set<Rule> convertIdSetToRuleSet(std::set<int> clique);
    Rule convertIdToRule(int id) const;
    StronglyConnectedComponent buildSCCFromRuleSet(
        const std::set<Rule> &rules);
    Relation evaluateRule(Rule rule);
    const Relation evaluateRulePredicates(Rule rule) const;
    const Relation evaluateRulePredicate(Predicate predicate) const;
    void printRuleEvaluationResults(
        const std::vector<StronglyConnectedComponent> &components) const;
};

#endif
