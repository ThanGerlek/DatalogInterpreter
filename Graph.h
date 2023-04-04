#ifndef CS236_LAB5_T2K_DATALOG_GRAPH_H
#define CS236_LAB5_T2K_DATALOG_GRAPH_H

#include <map>
#include "Node.h"

class Graph
{
private:
    std::map<int, Node> nodes;
    int numNodes;

public:
    Graph() : numNodes(0){};
    Graph(int _numNodes) : numNodes(_numNodes)
    {
        for (int i = 0; i < numNodes; i++)
        {
            std::pair<int, Node> pair(i, Node());
            nodes.insert(pair);
        }
    };

    void addEdge(int fromNodeId, int toNodeId)
    {
        nodes.at(fromNodeId).addEdge(toNodeId);
    }

    std::string toString() const
    {
        std::stringstream out;
        for (int i = 0; i < numNodes; i++)
        {
            out << "R" << i << ":" << nodes.at(i).toString() << std::endl;
        }
        return out.str();
    }
};

#endif
