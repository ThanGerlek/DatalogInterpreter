#ifndef CS236_LAB4_T2K_RELATION_CPP
#define CS236_LAB4_T2K_RELATION_CPP

#include "Relation.h"

void Relation::addTuple(const Tuple &tuple)
{
    if (tuple.size() != scheme.size())
    {
        std::cerr << "[ERROR] Tried to add tuple to a relation with a scheme of a different size." << std::endl;
        throw;
    }

    tuples.insert(tuple);
}

std::string Relation::toString() const
{
    std::stringstream out;
    for (auto &tuple : tuples)
        out << tuple.toString(scheme) << std::endl;
    return out.str();
}

////
////
////
////

const Relation Relation::selectForConstant(unsigned int u_index, const std::string &value) const
{
    Relation result(name, scheme);
    for (Tuple tuple : tuples)
    {
        if (tuple.at(u_index) == value)
        {
            result.addTuple(tuple);
        }
    }
    return result;
}

const Relation Relation::selectForEqualVariables(unsigned int u_index1, unsigned int u_index2) const
{
    Relation result(name, scheme);
    for (Tuple tuple : tuples)
    {
        std::string v1 = tuple.at(u_index1);
        std::string v2 = tuple.at(u_index2);
        if (v1 == v2)
        {
            result.addTuple(tuple);
        }
    }
    return result;
}

const Relation Relation::project(const std::vector<unsigned int> &u_indices) const
{
    Scheme projectedScheme = scheme.project(u_indices);
    Relation result(name, projectedScheme);
    for (Tuple tuple : tuples)
    {
        Tuple projectedTuple = tuple.project(u_indices);
        result.addTuple(projectedTuple);
    }
    return result;
}

const Relation Relation::rename(const std::string &oldName, const std::string &newName) const
{
    Scheme renamedScheme = scheme.rename(oldName, newName);
    Relation result(name, renamedScheme);
    for (Tuple tuple : tuples)
    {
        result.addTuple(tuple.copy());
    }
    return result;
}

#endif
