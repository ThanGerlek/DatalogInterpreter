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
 * @brief Test if the given tuples (under the given schemes) should be included in a call to join().
 */
bool Relation::joinable(const Scheme &leftScheme, const Scheme &rightScheme,
                        const Tuple &leftTuple, const Tuple &rightTuple)
{
    // TODO Test for cross product and make it its own function?
    for (unsigned leftIndex = 0; leftIndex < leftScheme.size(); leftIndex++)
    {
        const std::string &leftName = leftScheme.at(leftIndex);
        const std::string &leftValue = leftTuple.at(leftIndex);
        for (unsigned rightIndex = 0; rightIndex < rightScheme.size(); rightIndex++)
        {
            const std::string &rightName = rightScheme.at(rightIndex);
            const std::string &rightValue = rightTuple.at(rightIndex);
            if (leftName == rightName && leftValue != rightValue)
            {
                return false;
            }
        }
    }
    return true;
}

/**
 * @brief Apply the JOIN operation with this Relation on the left and the given Relation on the right.
 *
 * @param right The Relation to join on the right.
 * @return const Relation The resulting joined Relation.
 */
const Relation Relation::join(const Relation &right)
{
    const Relation &left = *this;

    Scheme leftScheme = left.getScheme();
    Scheme rightScheme = right.getScheme();
    Scheme resultScheme = joinSchemes(leftScheme, rightScheme);

    std::string resultName = joinNames(left.getName(), right.getName());
    Relation result(resultName, resultScheme);

    // For each Tuple in left and right Relations, if they're joinable,
    // join them and add the resulting Tuple to the result Relation.
    for (const Tuple &leftTuple : left.tuples)
    {
        for (const Tuple &rightTuple : right.tuples)
        {
            if (joinable(leftScheme, rightScheme, leftTuple, rightTuple))
            {
                Tuple tuple = joinSchemes(leftTuple, rightTuple);
                result.addTuple(tuple);
            }
        }
    }

    return result;
}

std::string Relation::joinNames(std::string left, std::string right)
{
    std::stringstream ss;
    ss << "(" + left + ")" + " JOIN " + "(" + right + ")";
    return ss.str();
}

const Scheme Relation::joinSchemes(const Scheme &left, const Scheme &right)
{
    // TODO
}

const Tuple Relation::joinTuples(const Scheme &leftScheme, const Scheme &rightScheme, const Scheme &resultScheme, const Tuple &left, const Tuple &right)
{
    //? Unneeded parameter?
    // TODO
}

////
////
////
////

// TODO? Add getTuples() function (safety)? Remove unneeded calls to getScheme() (efficiency)?

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
 * @brief Return a new Relation with its attributes renamed.
 *
 * @param newNames The new names of the attributes in the given order.
 * @return const Relation
 */
const Relation Relation::rename(std::vector<std::string> &newNames) const
{
    Scheme renamedScheme = scheme.rename(newNames);
    Relation result(name, renamedScheme);
    for (Tuple tuple : tuples)
    {
        result.addTuple(tuple.copy());
    }
    return result;
}

#endif
