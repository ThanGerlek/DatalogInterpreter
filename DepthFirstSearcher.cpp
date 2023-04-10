#ifndef CS236_PROJECT5_T2K_DATALOG_DEPTH_FIRST_SEARCHER_CPP
#define CS236_PROJECT5_T2K_DATALOG_DEPTH_FIRST_SEARCHER_CPP

#include "DepthFirstSearcher.h"

std::vector<int> DepthFirstSearcher::run(Graph &graph, int _rootId)
{
    graph.setAllNodesUnvisited();
    DepthFirstSearcher searcher(&graph, _rootId);
    searcher.search();
    return searcher.sequence;
}

DepthFirstSearcher::DepthFirstSearcher(Graph *_graphPtr, int _rootId)
{
    // TODO DepthFirstSearcher
}

void DepthFirstSearcher::search()
{
    // TODO search()
}

int DepthFirstSearcher::recurseDepthFirstSearch(int localRootId)
{
    // TODO recurseDepthFirstSearch
}

#endif
