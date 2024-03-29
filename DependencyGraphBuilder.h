#ifndef CS236_LAB5_T2K_DATALOG_DEPENDENCY_GRAPH_BUILDER_H
#define CS236_LAB5_T2K_DATALOG_DEPENDENCY_GRAPH_BUILDER_H

#include <vector>
#include "DatalogProgram.h"
#include "Rule.h"
#include "Graph.h"

// TODO. Eliminate pointers

class DependencyGraphBuilder
{
public:
    static Graph buildGraphFromProgram(const DatalogProgram &program);

private:
    Graph graph;
    int numNodes;
    const std::vector<Rule> &rules;

    DependencyGraphBuilder(const std::vector<Rule> &_rules);

    void build();
    void addEdges();
    void addEdgesFromRuleID(unsigned fromRuleID);
    void addEdgesFromRuleIDWithBodyPredicate(unsigned fromRuleID, Predicate bodyPredicate);
    bool hasEdgeFromPredicateToRule(Predicate bodyPredicate, unsigned toRuleID);
    void addEdgeFromRuleToRule(unsigned fromRuleID, unsigned toRuleID);
};

#endif
