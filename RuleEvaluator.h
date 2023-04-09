#ifndef CS236_PROJECT5_T2K_DATALOG_RULE_EVALUATOR_H
#define CS236_PROJECT5_T2K_DATALOG_RULE_EVALUATOR_H

#include "DatalogDatabase.h"
#include "Graph.h"

class RuleEvaluator
{
public:
    RuleEvaluator(DatalogDatabase &_database,
                  const DatalogProgram &_program,
                  const Graph &_dependencyGraph)
        : database(_database),
          program(_program),
          dependencyGraph(_dependencyGraph){};
          
    void evaluate();

private:
    DatalogDatabase &database;
    const DatalogProgram &program;
    const Graph &dependencyGraph;

    const std::set<Rule> convertNodeSetToRuleSet(std::set<Node> clique);
    void evaluateRuleSet(const std::set<Rule> &rules);
    void evaluateRule(Rule rule);
    const Relation evaluateRulePredicates(Rule rule) const;
    const Relation evaluateRulePredicate(Predicate predicate) const;
    void printRuleResult(Rule rule, Relation results) const;
    //
};

#endif
