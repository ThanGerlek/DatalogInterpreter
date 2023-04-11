#ifndef CS236_LAB5_T2K_DATALOG_GRAPH_H
#define CS236_LAB5_T2K_DATALOG_GRAPH_H

#include <map>
#include "Node.h"

class Graph
{
private:
    std::map<int, Node> nodes;
    int numNodes;

    std::vector<int> calculateReversedPostOrderSequence(Graph &reverseGraph);
    std::vector<std::set<int>> calculateCliquesFromDFSOnRootNodes(std::vector<int> &rootOrder);
    void addReversedEdgesFromNode(Graph &reverseGraph, Node originalNode) const;
    void resetAllNodes();
    std::vector<int> depthFirstPostorder();

    friend class DepthFirstSearcher;

public:
    Graph() : numNodes(0){};
    Graph(int _numNodes);

    std::vector<std::set<int>> findAllCliques();
    Graph buildReverseGraph() const;
    void addEdge(int fromNodeId, int toNodeId);
    Node getNode(int nodeId);
    std::string toString() const;
};

#endif
