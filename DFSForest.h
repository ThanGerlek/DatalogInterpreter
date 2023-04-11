#ifndef CS236_PROJECT5_T2K_DATALOG_DFS_FOREST_H
#define CS236_PROJECT5_T2K_DATALOG_DFS_FOREST_H

#include <set>
#include <vector>
#include "Node.h"

class DFSForest
{
private:
    unsigned currentDfsTreeIndex;
    std::vector<std::set<int>> forest;

public:
    DFSForest() : currentDfsTreeIndex(0)
    {
        initializeDfsTree();
    }

    void addNode(Node &node)
    {
        initializeDfsTree();
        std::set<int> &dfsTree = forest.at(currentDfsTreeIndex);
        dfsTree.insert(node.nodeId);
    }

    void beginNewTree()
    {
        if (forest.at(currentDfsTreeIndex).size() != 0)
        {
            initializeDfsTree();
            currentDfsTreeIndex++;
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
    void initializeDfsTree()
    {
        if (forest.size() >= currentDfsTreeIndex)
        {
            std::set<int> dfsTree;
            forest.at(currentDfsTreeIndex) = dfsTree;
        }
    }
};

#endif
