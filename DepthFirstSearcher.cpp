#ifndef CS236_PROJECT5_T2K_DATALOG_DEPTH_FIRST_SEARCHER_CPP
#define CS236_PROJECT5_T2K_DATALOG_DEPTH_FIRST_SEARCHER_CPP

#include <iostream>
#include "DepthFirstSearcher.h"

std::vector<int> DepthFirstSearcher::run(Graph &graph, int rootId)
{
    DepthFirstSearcher searcher(&graph);
    graph.setAllNodesUnvisited();
    searcher.searchFrom(rootId);
    return searcher.postOrderSequence;
}

void DepthFirstSearcher::searchFrom(int rootId)
{
    Node root = graphPtr->nodes.at(rootId);
    recurseDepthFirstSearch(root);
}

void DepthFirstSearcher::recurseDepthFirstSearch(Node &node)
{
    if (!node.hasBeenVisited)
    {
        recordVisit(node);
        visitNeighborsOf(node);
        postOrderSequence.push_back(node.nodeId);
    }
}

void DepthFirstSearcher::recordVisit(Node &node)
{
    node.hasBeenVisited = true;
    visitSequence.push_back(node.nodeId);
}

void DepthFirstSearcher::visitNeighborsOf(Node &node)
{
    for (int neighborId : node.adjacentNodeIds)
    {
        Node &neighbor = graphPtr->nodes.at(neighborId);
        recurseDepthFirstSearch(neighbor);
    }
}

#endif
