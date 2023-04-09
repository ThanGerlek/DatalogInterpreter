#ifndef CS236_PROJECT5_T2K_DATALOG_GRAPH_CPP
#define CS236_PROJECT5_T2K_DATALOG_GRAPH_CPP

#include "Graph.h"

// TODO std::vector<std::set<Node>> findAllCliques();

Graph::Graph(int _numNodes)
{
    this->numNodes = _numNodes;
    for (int i = 0; i < numNodes; i++)
    {
        std::pair<int, Node> pair(i, Node());
        nodes.insert(pair);
    }
}

void Graph::addEdge(int fromNodeId, int toNodeId)
{
    nodes.at(fromNodeId).addEdge(toNodeId);
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
