#ifndef CS236_PROJECT5_T2K_DATALOG_DEPTH_FIRST_SEARCHER_H
#define CS236_PROJECT5_T2K_DATALOG_DEPTH_FIRST_SEARCHER_H

#include <vector>
#include "Graph.h"

class DepthFirstSearcher
{
public:
    static std::vector<int> generatePostorder(Graph &graph);
    static std::vector<int> generatePostorderWithRootPriorityList(Graph &graph, std::vector<int> rootPriorityList);

protected:
    DepthFirstSearcher(Graph *_graphPtr)
        : graphPtr(_graphPtr), nextRootNode(0){};
    int nextRootNode;

private:
    Graph *graphPtr;
    std::vector<int> visitSequence;
    std::vector<int> postOrderSequence;

private:

    void search();
    void searchTree(Node root);
    void recurseDepthFirstSearch(Node &node);
    void recordVisit(Node &node);
    void visitNeighborsOf(Node &node);
    virtual bool isSearchComplete();
    Node getNextRoot();
    virtual void updateNextRootNode(int nodeId);
};

class PrioritizedDepthFirstSearcher : DepthFirstSearcher
{
private:
    std::vector<int> rootPriorityList;


    PrioritizedDepthFirstSearcher(Graph *_graphPtr,
                                  std::vector<int> _rootPriorityList)
        : DepthFirstSearcher(_graphPtr),
          rootPriorityList(_rootPriorityList){};

    bool isSearchComplete();
    void updateNextRootNode(int nodeId);
};

#endif
