#ifndef CS236_PROJECT5_T2K_DATALOG_GRAPH_CPP
#define CS236_PROJECT5_T2K_DATALOG_GRAPH_CPP

#include <set>
#include <vector>
#include "Graph.h"
#include "DepthFirstSearcher.h"

Graph::Graph(int _numNodes)
{
    this->numNodes = _numNodes;
    for (int i = 0; i < numNodes; i++)
    {
        std::pair<int, Node> pair(i, Node(i));
        nodes.insert(pair);
    }
}

std::vector<std::set<Node>> Graph::findAllCliques()
{
    // TODO
}

Graph Graph::buildReverseGraph() const
{
    // TODO buildReverseGraph
}

void Graph::addReversedEdges(Graph &reverseGraph, Node origNode) const
{
    // TODO addReversedEdges
}

std::vector<int> Graph::calculateReversedPostOrderSequence(Graph &reverseGraph)
{
    // TODO calculateReversedPostOrderSequence
    std::vector<int> dfsNodes = reverseGraph.depthFirstSearchFromRoot(0);
}

std::set<std::set<int>> Graph::calculateCliquesFromDFSOnRootNodes(std::vector<int> &rootOrder) const
{
    // TODO calculateCliquesFromDFSOnRootNodes
}

std::vector<int> Graph::depthFirstSearchFromRoot(int rootId)
{
    return DepthFirstSearcher::run(*this, rootId);
}

void Graph::addEdge(int fromNodeId, int toNodeId)
{
    nodes.at(fromNodeId).addEdge(toNodeId);
}

void Graph::setAllNodesUnvisited()
{
    for (int i = 0; i < nodes.size(); i++)
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
