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
    DFSForest(){};

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

    int numTrees()
    {
        return static_cast<int>(forest.size());
    }

private:
    std::set<int> &getCurrentDfsTree()
    {
        initializeDfsTree();
        unsigned index = static_cast<unsigned>(getCurrentDfsTreeIndex());
        return forest.at(index);
    }

    void initializeDfsTree()
    {
        if (getCurrentDfsTreeIndex() >= numTrees())
        {
            std::set<int> dfsTree;
            forest.push_back(dfsTree);
        }
    }

    int getCurrentDfsTreeIndex()
    {
        if (numTrees() == 0)
        {
            return 0;
        }
        return numTrees() - 1;
    }
};

#endif
