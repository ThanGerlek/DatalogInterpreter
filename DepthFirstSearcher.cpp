#ifndef CS236_PROJECT5_T2K_DATALOG_DEPTH_FIRST_SEARCHER_CPP
#define CS236_PROJECT5_T2K_DATALOG_DEPTH_FIRST_SEARCHER_CPP

#include <iostream>
#include "DepthFirstSearcher.h"

std::vector<int> DepthFirstSearcher::generatePostorder(Graph &graph)
{
    DepthFirstSearcher searcher(&graph);
    graph.setAllNodesUnvisited();
    searcher.search();
    return searcher.postOrderSequence;
}

std::vector<int> DepthFirstSearcher::generatePostorderWithRootPriorityList(
    Graph &graph, std::vector<int> rootPriorityList)
{
    // TODO generatePostorderWithRootPriorityList
}

void DepthFirstSearcher::search()
{
    while (!isSearchComplete())
    {
        Node &root = getNextRoot();
        searchTree(root);
    }
}

void DepthFirstSearcher::searchTree(Node &root)
{
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

Node &DepthFirstSearcher::getNextRoot()
{
    updateNextRootNode();
    return graphPtr->nodes.at(nextRootNodeId);
}

bool DepthFirstSearcher::isSearchComplete()
{
    for (int i = 0; i < graphPtr->numNodes; i++)
    {
        Node &node = graphPtr->nodes.at(i);
        if (!node.hasBeenVisited)
        {
            return false;
        }
    }
    return true;
}

void DepthFirstSearcher::updateNextRootNode()
{
    for (int i = 0; i < graphPtr->numNodes; i++)
    {
        Node &root = graphPtr->nodes.at(i);
        if (!root.hasBeenVisited)
        {
            this->nextRootNodeId = i;
            return;
        }
    }
    std::cerr << "[ERROR] Could not find root node." << std::endl;
    throw;
}

#endif
