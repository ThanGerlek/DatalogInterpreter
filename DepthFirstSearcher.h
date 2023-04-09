#ifndef CS236_PROJECT5_T2K_DATALOG_DEPTH_FIRST_SEARCHER_H
#define CS236_PROJECT5_T2K_DATALOG_DEPTH_FIRST_SEARCHER_H

#include <vector>
#include "Graph.h"

class DepthFirstSearcher
{
public:
    static std::vector<int> run(Graph &graph, int rootId);

private:
    Graph *graphPtr;
    int rootId;
    int leastUnvisitedIndex;
    std::vector<int> sequence;

    DepthFirstSearcher(Graph *graphPtr, int rootId);

    void search();
    int recurseDepthFirstSearch(int rootId);
};

#endif
