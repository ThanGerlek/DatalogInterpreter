#ifndef CS236_PROJECT5_T2K_DATALOG_DEPTH_FIRST_SEARCHER_H
#define CS236_PROJECT5_T2K_DATALOG_DEPTH_FIRST_SEARCHER_H

#include <vector>
#include "Graph.h"

class DepthFirstSearcher
{
public:
    static std::vector<int> run(Graph &graph, int _rootId);

private:
    Graph *graphPtr;
    int rootId;
    int leastUnvisitedIndex;
    std::vector<int> sequence;

    DepthFirstSearcher(Graph *_graphPtr, int _rootId);

    void search();
    int recurseDepthFirstSearch(int localRootId);
};

#endif
