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
    std::vector<int> visitSequence;
    std::vector<int> postOrderSequence;

    DepthFirstSearcher(Graph *_graphPtr) : graphPtr(_graphPtr){};

    void searchFrom(int rootId);
    void recurseDepthFirstSearch(Node &node);
    void recordVisit(Node &node);
    void visitNeighborsOf(Node &node);
};

#endif
