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
    Graph(int _numNodes);

    std::vector<std::set<Node>> Graph::findAllCliques();
    void addEdge(int fromNodeId, int toNodeId);
    std::string toString() const;
};

#endif
