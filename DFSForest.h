#ifndef CS236_PROJECT5_T2K_DATALOG_DFS_FOREST_H
#define CS236_PROJECT5_T2K_DATALOG_DFS_FOREST_H

#include <set>
#include <vector>
#include "Node.h"

class DFSForest
{
private:
    std::vector<std::set<int>> forest;

public:
    DFSForest()
    {
        initializeDfsTree();
    }

    void addNode(Node &node)
    {
        getCurrentDfsTree().insert(node.nodeId);
    }

    void beginNewTree()
    {
        if (getCurrentDfsTree().size() != 0)
        {
            std::set<int> dfsTree;
            forest.push_back(dfsTree);
            initializeDfsTree();
        }
    }

    std::vector<std::set<int>> getFlattenedTrees()
    {
        return forest;
    }

    int size()
    {
        return static_cast<int>(forest.size());
    }

private:
    std::set<int> &getCurrentDfsTree()
    {
        initializeDfsTree();
        return forest.at(getCurrentDfsTreeIndex());
    }

    void initializeDfsTree()
    {
        if (getCurrentDfsTreeIndex() >= forest.size())
        {
            std::set<int> dfsTree;
            forest.push_back(dfsTree);
        }
    }

    unsigned getCurrentDfsTreeIndex()
    {
        if (forest.size() == 0)
        {
            return 0;
        }
        return forest.size() - 1;
    }
};

#endif
