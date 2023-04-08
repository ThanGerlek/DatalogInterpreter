#ifndef CS236_PROJECT3_T2K_DATABASE_H
#define CS236_PROJECT3_T2K_DATABASE_H

#include <vector>
#include "Relation.h"

class Database
{
protected:
    std::vector<Relation> relations;

    bool hasRelation(std::string relationName) const
    {
        for (unsigned int i = 0; i < relations.size(); i++)
        {
            if (relations.at(i).getName() == relationName)
            {
                return true;
            }
        }
        return false;
    }

    unsigned int getIndex(std::string relationName) const
    {
        for (unsigned int i = 0; i < relations.size(); i++)
        {
            if (relations.at(i).getName() == relationName)
            {
                return i;
            }
        }
        std::cerr << "[ERROR] Called getIndex() with a Relation name that is not in the Database." << std::endl;
        throw;
    }

    // Update a relation in the database. Does not affect relation names.
    void updateRelation(std::string destinationName, Relation newValue)
    {
        unsigned int index = getIndex(destinationName);
        newValue.setName(destinationName);
        relations.at(index) = newValue;
    }

    ////
    ////
    ////
    ////

public:
    void addRelation(Relation relation)
    {
        if (hasRelation(relation.getName()))
        {
            std::cerr << "[ERROR] Tried to add a relation whose name is already in the database." << std::endl;
            throw;
        }
        relations.push_back(relation);
    }

    void addTuple(Tuple tuple, std::string relationName)
    {
        if (!hasRelation(relationName))
        {
            std::cerr << "[ERROR] Tried to add a tuple to a relation that doesn't exist." << std::endl;
            throw;
        }
        unsigned int index = getIndex(relationName);
        relations.at(index).addTuple(tuple);
    }

    unsigned int size()
    {
        unsigned int total = 0;
        for (Relation relation : relations)
        {
            total += relation.size();
        }
        return total;
    }

    const Relation getRelation(std::string &relationName) const
    {
        if (!hasRelation(relationName))
        {
            std::cerr << "[ERROR] Called getRelation() with a Relation name that is not in the Database." << std::endl;
            throw;
        }

        unsigned int index = getIndex(relationName);
        return relations.at(index);
    }
};

#endif
