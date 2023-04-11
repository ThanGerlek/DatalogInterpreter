#ifndef CS236_PROJECT5_T2K_DATALOG_DEPTH_FIRST_SEARCHER_CPP
#define CS236_PROJECT5_T2K_DATALOG_DEPTH_FIRST_SEARCHER_CPP

#include <iostream>
#include "DepthFirstSearcher.h"

std::vector<int> DepthFirstSearcher::generatePostorder(Graph &graph)
{
    DepthFirstSearcher searcher(&graph);
    searcher.resetAllNodes();
    searcher.search();
    return searcher.postOrderSequence;
}

std::vector<std::set<int>> DepthFirstSearcher::generateForestWithRootPriorityList(
    Graph &graph, std::vector<int> rootPriorityList)
{
    return PrioritizedDepthFirstSearcher::generateForestWithRootPriorityList(graph, rootPriorityList);
}

std::vector<std::set<int>> PrioritizedDepthFirstSearcher::generateForestWithRootPriorityList(Graph &graph, std::vector<int> rootPriorityList)
{
    PrioritizedDepthFirstSearcher searcher(&graph, rootPriorityList);
    searcher.resetAllNodes();
    searcher.search();
    return searcher.dfsForest;
}

void DepthFirstSearcher::search()
{
    while (!isSearchComplete())
    {
        Node &root = getNextRoot();
        searchTree(root);
        currentDfsTreeIndex++;
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
    node.dfsTreeId = currentDfsTreeIndex;
    visitSequence.push_back(node.nodeId);
    std::set<int> &dfsTree = dfsForest.at(currentDfsTreeIndex);
    dfsTree.insert(node.nodeId);
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

void DepthFirstSearcher::resetAllNodes()
{
    graphPtr->resetAllNodes();
}

// Subclasses

bool PrioritizedDepthFirstSearcher::isSearchComplete()
{
    for (unsigned i = 0; i < priorityListSize(); i++)
    {
        int nodeId = rootPriorityList.at(i);
        Node node = graphPtr->getNode(nodeId);
        if (!node.hasBeenVisited)
        {
            return false;
        }
    }
    return true;
}

void PrioritizedDepthFirstSearcher::updateNextRootNode()
{
    for (unsigned i = 0; i < priorityListSize(); i++)
    {
        int nodeId = rootPriorityList.at(i);
        Node node = graphPtr->getNode(nodeId);
        if (!node.hasBeenVisited)
        {
            this->nextRootNodeId = nodeId;
            return;
        }
    }
    std::cerr << "[ERROR] Could not find root node." << std::endl;
    throw;
}

unsigned PrioritizedDepthFirstSearcher::priorityListSize()
{
    return static_cast<unsigned>(rootPriorityList.size());
}

#endif
