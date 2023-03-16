#ifndef CS236_LAB4_T2K_RELATION_CPP
#define CS236_LAB4_T2K_RELATION_CPP

#include "Relation.h"

void Relation::addTuple(const Tuple &tuple)
{
    if (tuple.size() != scheme.size())
    {
        std::cerr << "Tried to add tuple to a relation with a scheme of a different size" << std::endl;
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

Relation Relation::selectForConstant(int index, const std::string &value) const
{
    Relation result(name, scheme);
    for (std::set<Tuple>::iterator iter = tuples.begin(); iter != tuples.end(); iter++)
    {
        if (iter->at(static_cast<unsigned int>(index)) == value)
        {
            result.addTuple(*iter);
        }
    }
    return result;
}

Relation Relation::selectForEqualVariables(int index1, int index2) const
{
    Relation result(name, scheme);
    for (std::set<Tuple>::iterator iter = tuples.begin(); iter != tuples.end(); iter++)
    {
        std::string v1 = iter->at(static_cast<unsigned int>(index1));
        std::string v2 = iter->at(static_cast<unsigned int>(index2));
        if (v1 == v2)
        {
            result.addTuple(*iter);
        }
    }
    return result;
}

Relation Relation::project(std::vector<int> &indices) const
{
    Scheme projectedScheme = scheme.project(indices);
    Relation result(name, projectedScheme);
    for (Tuple tuple : tuples)
    {
        Tuple projectedTuple = tuple.project(indices);
        result.addTuple(projectedTuple);
    }
    return result;
}

Relation Relation::rename(int index, const std::string &newName) const
{
    Scheme renamedScheme = scheme.rename(index, newName);
    Relation result(name, renamedScheme);
    for (Tuple tuple : tuples)
    {
        result.addTuple(tuple.copy());
    }
    return result;
}

#endif
