#ifndef CS236_LAB5_T2K_DATALOG_DEPENDENCY_GRAPH_BUILDER_CPP
#define CS236_LAB5_T2K_DATALOG_DEPENDENCY_GRAPH_BUILDER_CPP

#include "DependencyGraphBuilder.h"

Graph DependencyGraphBuilder::makeGraph(const std::vector<Rule> &rules)
{
    DependencyGraphBuilder builder(rules);
    builder.addEdges();
    return builder.graph;
}

DependencyGraphBuilder::DependencyGraphBuilder(const std::vector<Rule> &_rules)
    : rules(_rules)
{
    numNodes = static_cast<int>(_rules.size());
    graph = Graph(numNodes);
}

void DependencyGraphBuilder::addEdges()
{
    for (unsigned fromRuleID = 0; fromRuleID < rules.size(); fromRuleID++)
    {
        Rule fromRule = rules.at(fromRuleID);
        // std::cout << "from rule R" << fromRuleID << ": " << fromRule.toString() << std::endl;
        addEdgesFromRuleID(fromRuleID);
    }
}

void DependencyGraphBuilder::addEdgesFromRuleID(unsigned fromRuleID)
{
    Rule fromRule = rules.at(fromRuleID);
    for (unsigned predIndex = 0; predIndex < fromRule.size(); predIndex++)
    {
        Predicate bodyPredicate = fromRule.getBodyPredicate(predIndex);
        // std::cout << "from body predicate: " << bodyPredicate.toString() << std::endl;
        addEdgesFromRuleIDWithBodyPredicate(fromRuleID, bodyPredicate);
    }
}

void DependencyGraphBuilder::addEdgesFromRuleIDWithBodyPredicate(unsigned fromRuleID, Predicate bodyPredicate)
{
    for (unsigned toRuleID = 0; toRuleID < rules.size(); toRuleID++)
    {
        Rule toRule = rules.at(toRuleID);
        // std::cout << "to rule R" << toRuleID << ": " << toRule.toString() << std::endl;
        if (hasEdgeFromPredicateToRule(bodyPredicate, toRuleID))
        {
            addEdgeFromRuleToRule(fromRuleID, toRuleID);
        }
    }
}

bool DependencyGraphBuilder::hasEdgeFromPredicateToRule(Predicate bodyPredicate, unsigned toRuleID)
{
    Rule toRule = rules.at(toRuleID);
    return toRule.getHead() == bodyPredicate;
}

void DependencyGraphBuilder::addEdgeFromRuleToRule(unsigned fromRuleID, unsigned toRuleID)
{
    int fromID = static_cast<int>(fromRuleID);
    int toID = static_cast<int>(toRuleID);
    graph.addEdge(fromID, toID);
}

#endif
