#ifndef CS236_LAB4_T2K_RELATION_CPP
#define CS236_LAB4_T2K_RELATION_CPP

#include "Relation.h"

/**
 * @brief Add a Tuple to this Relation.
 */
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

/**
 * @brief Return a new Relation, SELECT-ing for Tuples with the given value at the given attribute index.
 *
 * @param u_index The index of the attribute to SELECT for.
 * @param value The value to look for.
 * @return const Relation
 */
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

/**
 * @brief Return a new Relation, SELECT-ing for Tuples where the attributes at the given indices are equal.
 *
 * @param u_index1
 * @param u_index2
 * @return const Relation
 */
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

/**
 * @brief Return a new Relation which includes only the selected attributes in the given order.
 *
 * @param u_indices The (unsigned) indices of the attributes to include.
 * @return const Relation
 */
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

/**
 * @brief Return a new Relation with the given attribute renamed.
 *
 * @param oldName The attribute to rename.
 * @param newName The new name.
 * @return const Relation
 */
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
