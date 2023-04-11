#ifndef CS236_PROJECT5_T2K_DATALOG_DEPTH_FIRST_SEARCHER_H
#define CS236_PROJECT5_T2K_DATALOG_DEPTH_FIRST_SEARCHER_H

#include <vector>
#include "Graph.h"

// TODO. Make lists into refs

class DepthFirstSearcher
{
public:
    static std::vector<int> generatePostorder(Graph &graph);
    static std::vector<int> generatePostorderWithRootPriorityList(Graph &graph, std::vector<int> rootPriorityList);
    virtual ~DepthFirstSearcher(){};

protected:
    DepthFirstSearcher(Graph *_graphPtr)
        : graphPtr(_graphPtr), nextRootNodeId(0){};

    Graph *graphPtr;
    int nextRootNodeId;
    std::vector<int> visitSequence;
    std::vector<int> postOrderSequence;

    void search();
    void setAllNodesUnvisited();

private:
    void searchTree(Node &root);
    void recurseDepthFirstSearch(Node &node);
    void recordVisit(Node &node);
    void visitNeighborsOf(Node &node);
    virtual bool isSearchComplete();
    Node &getNextRoot();
    virtual void updateNextRootNode();
};

class PrioritizedDepthFirstSearcher : DepthFirstSearcher
{
public:
    static std::vector<int> generatePostorderWithRootPriorityList(Graph &graph, std::vector<int> rootPriorityList);
    ~PrioritizedDepthFirstSearcher(){};

private:
    PrioritizedDepthFirstSearcher(
        Graph *_graphPtr,
        std::vector<int> _rootPriorityList)
        : DepthFirstSearcher(_graphPtr),
          rootPriorityList(_rootPriorityList){};

    std::vector<int> rootPriorityList;

    bool isSearchComplete();
    void updateNextRootNode();
};

#endif
