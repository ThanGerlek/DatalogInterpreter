#ifndef CS236_LAB5_T2K_DATALOG_DEPENDENCY_GRAPH_BUILDER_H
#define CS236_LAB5_T2K_DATALOG_DEPENDENCY_GRAPH_BUILDER_H

#include <vector>
#include "Rule.h"
#include "Graph.h"

class DependencyGraphBuilder
{
public:
    static Graph makeGraph(const std::vector<Rule> &rules);

private:
    Graph graph;
    int numNodes;
    const std::vector<Rule> &rules;

    DependencyGraphBuilder(const std::vector<Rule> &_rules);

    void addEdges();
    void addEdgesFromRuleID(unsigned fromRuleID);
    void addEdgesFromRuleIDFromBodyPredicate(unsigned fromRuleID, Predicate bodyPredicate);
    bool hasEdgeFromPredicateToRule(Predicate bodyPredicate, unsigned toRuleID);
    void addEdgeFromRuleToRule(unsigned fromRuleID, unsigned toRuleID);
};

#endif
