#ifndef CS236_PROJECT5_T2K_DATALOG_GRAPH_CPP
#define CS236_PROJECT5_T2K_DATALOG_GRAPH_CPP

#include <set>
#include <vector>
#include "Graph.h"
#include "DepthFirstSearcher.h"

Graph::Graph(int _numNodes)
{
    this->numNodes = _numNodes;
    for (int i = 0; i < _numNodes; i++)
    {
        std::pair<int, Node> pair(i, Node(i));
        nodes.insert(pair);
    }
}

std::vector<std::set<Node>> Graph::findAllCliques()
{
    Graph reverseGraph = buildReverseGraph();
    std::vector<int> rootNodeOrder = calculateReversedPostOrderSequence(reverseGraph);
    calculateCliquesFromDFSOnRootNodes(rootNodeOrder);
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
    // TODO calculateReversedPostOrderSequence
    std::vector<int> dfsNodes = reverseGraph.depthFirstPostorderFromRoot(0);
}

std::set<std::set<int>> Graph::calculateCliquesFromDFSOnRootNodes(std::vector<int> &rootOrder) const
{
    // TODO calculateCliquesFromDFSOnRootNodes
}

std::vector<int> Graph::depthFirstPostorderFromRoot(int rootId)
{
    // TODO Graph::depthFirstPostorderFromRoot
}

void Graph::addEdge(int fromNodeId, int toNodeId)
{
    nodes.at(fromNodeId).addEdge(toNodeId);
}

Node Graph::getNode(int nodeId)
{
    return nodes.at(nodeId);
}

void Graph::setAllNodesUnvisited()
{
    for (int i = 0; i < numNodes; i++)
    {
        nodes.at(i).hasBeenVisited = false;
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
