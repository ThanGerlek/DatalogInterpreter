#ifndef CS236_PROJECT5_T2K_DATALOG_GRAPH_CPP
#define CS236_PROJECT5_T2K_DATALOG_GRAPH_CPP

#include <set>
#include <vector>
#include "Graph.h"
#include "DepthFirstSearcher.h"

// TODO. Convert sets/vectors into stacks

Graph::Graph(int _numNodes)
{
    this->numNodes = _numNodes;
    for (int i = 0; i < _numNodes; i++)
    {
        std::pair<int, Node> pair(i, Node(i));
        nodes.insert(pair);
    }
}

std::vector<std::set<int>> Graph::findAllCliques()
{
    Graph reverseGraph = buildReverseGraph();
    std::vector<int> rootNodeOrder = calculateReversedPostOrderSequence(reverseGraph);
    return calculateCliquesFromDFSOnRootNodes(rootNodeOrder);
}

Graph Graph::buildReverseGraph() const
{
    Graph reverseGraph(numNodes);
    for (int i = 0; i < numNodes; i++)
    {
        Node originalNode = this->nodes.at(i);
        addReversedEdgesFromNode(reverseGraph, originalNode);
    }

    return reverseGraph;
}

void Graph::addReversedEdgesFromNode(Graph &reverseGraph, Node originalNode) const
{
    int fromId = originalNode.nodeId;
    for (int toId : originalNode.adjacentNodeIds)
    {
        reverseGraph.addEdge(toId, fromId);
    }
}

std::vector<int> Graph::calculateReversedPostOrderSequence(Graph &reverseGraph)
{
    std::vector<int> sequence = reverseGraph.depthFirstPostorder();
    std::vector<int> reversedSequence;
    for (int i = static_cast<int>(sequence.size()) - 1; i >= 0; i--)
    {
        reversedSequence.push_back(i);
    }
    return reversedSequence;
}

std::vector<std::set<int>> Graph::calculateCliquesFromDFSOnRootNodes(std::vector<int> &rootOrder)
{
    // TODO calculateCliquesFromDFSOnRootNodes
    std::vector<std::set<int>> forest = DepthFirstSearcher::generateForestWithRootPriorityList(*this, rootOrder);
    return forest;
}

std::vector<int> Graph::depthFirstPostorder()
{
    return DepthFirstSearcher::generatePostorder(*this);
}

void Graph::addEdge(int fromNodeId, int toNodeId)
{
    nodes.at(fromNodeId).addEdge(toNodeId);
}

Node Graph::getNode(int nodeId)
{
    return nodes.at(nodeId);
}

void Graph::resetAllNodes()
{
    for (int i = 0; i < numNodes; i++)
    {
        nodes.at(i).reset();
    }
}

std::string Graph::toString() const
{
    std::stringstream out;
    for (int i = 0; i < numNodes; i++)
    {
        out << "R" << i << ":" << nodes.at(i).toString() << std::endl;
    }
    return out.str();
}

#endif
