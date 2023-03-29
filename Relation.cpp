#ifndef CS236_LAB4_T2K_RELATION_CPP
#define CS236_LAB4_T2K_RELATION_CPP

#include "Relation.h"

// TODO Reorder functions (Clean Code practice)

/**
 * @brief Add a Tuple to this Relation.
 */
void Relation::addTuple(const Tuple &tuple)
{
    if (tuple.size() != this->scheme.size())
    {
        std::cerr << "[ERROR] Tried to add tuple to a relation with a scheme of a different size." << std::endl;
        throw;
    }

    this->tuples.insert(tuple);
}

void Relation::setName(std::string &newName)
{
    this->name = newName;
}

std::string Relation::toString() const
{
    std::stringstream out;
    for (auto &tuple : this->tuples)
        out << tuple.toString(this->scheme) << std::endl;
    return out.str();
}

////
////
////
////

/**
 * @brief Test if the given tuples should be included in a call to join().
 */
bool Relation::joinable(const Scheme &leftScheme, const Scheme &rightScheme,
                        const Tuple &leftTuple, const Tuple &rightTuple)
{
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
 * @brief JOIN this Relation with another Relation.
 *
 * Applies the natural join operation with this Relation on the left and
 * the given Relation on the right.
 *
 * @param right The Relation to join on the right.
 * @return const Relation
 */
const Relation Relation::join(const Relation &right)
{
    const Relation &left = *this;

    Scheme leftScheme = left.scheme;
    Scheme rightScheme = right.scheme;
    Scheme resultScheme = joinSchemes(leftScheme, rightScheme);

    std::string resultName = joinNames(left.name, right.name);
    Relation result(resultName, resultScheme);

    // For each Tuple in left and right Relations, if they're joinable,
    // join them and add the resulting Tuple to the result Relation.
    for (const Tuple &leftTuple : left.tuples)
    {
        for (const Tuple &rightTuple : right.tuples)
        {
            if (joinable(leftScheme, rightScheme, leftTuple, rightTuple))
            {
                Tuple tuple = joinTuples(leftScheme, rightScheme, leftTuple, rightTuple);
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
    std::vector<std::string> attributes;
    for (std::string attribute : left)
    {
        attributes.push_back(attribute);
    }
    for (std::string attribute : right)
    {
        if (!contains(attributes, attribute))
        {
            attributes.push_back(attribute);
        }
    }
    Scheme result = Scheme(attributes);
    return result;
}

// Returns true if strs contains str.
bool Relation::contains(std::vector<std::string> strs, std::string str)
{
    for (std::string current : strs)
    {
        if (current == str)
        {
            return true;
        }
    }
    return false;
}

const Tuple Relation::joinTuples(const Scheme &leftScheme, const Scheme &rightScheme, const Tuple &leftTuple, const Tuple &rightTuple)
{
    // Add attributes from left to result
    std::vector<std::string> values = static_cast<std::vector<std::string>>(leftTuple);

    // Add attributes from right to result, skipping duplicates
    std::vector<std::string> attributes = rightScheme;
    for (unsigned int i = 0; i < rightScheme.size(); i++)
    {
        std::string attribute = rightScheme.at(i);
        if (!contains(leftScheme, attribute))
        {
            std::string value = rightTuple.at(i);
            values.push_back(value);
        }
    }
    Tuple result = Tuple(values);
    return result;
}

////
////
////
////

/**
 * @brief Apply the cross product to this Relation.
 *
 * Applies the cross product operation with this Relation on the left and
 * the given Relation on the right.
 *
 * @param right The Relation to cross on the right.
 * @return const Relation
 */
const Relation Relation::cross(const Relation &right)
{
    const Relation &left = *this;

    Scheme resultScheme = crossSchemes(left.scheme, right.scheme);
    std::string resultName = crossNames(left.name, right.name);
    Relation result = Relation(resultName, resultScheme);

    for (Tuple leftTuple : left.tuples)
    {
        for (Tuple rightTuple : right.tuples)
        {
            Tuple tuple = crossTuples(leftTuple, rightTuple);
            result.addTuple(tuple);
        }
    }

    return result;
}

std::string Relation::crossNames(std::string left, std::string right)
{
    std::stringstream ss;
    ss << "(" + left + ")" + " CROSS " + "(" + right + ")";
    return ss.str();
}

const Scheme Relation::crossSchemes(const Scheme &left, const Scheme &right)
{
    std::vector<std::string> resultNames;
    for (std::string attributeName : left)
    {
        resultNames.push_back(attributeName);
    }
    for (std::string attributeName : right)
    {
        resultNames.push_back(attributeName);
    }
    Scheme result = Scheme(resultNames);
    return result;
}

const Tuple Relation::crossTuples(const Tuple &left, const Tuple &right)
{
    std::vector<std::string> values;
    for (std::string value : left)
    {
        values.push_back(value);
    }
    for (std::string value : right)
    {
        values.push_back(value);
    }
    Tuple result = Tuple(values);
    return result;
}

////
////
////
////

/**
 * @brief SELECT on this Relation for an attribute with a specific value.
 *
 * Returns a new Relation containing only Tuples where the attribute at the given
 * index has the specified value.
 *
 * @param index The index of the attribute to SELECT for.
 * @param value The value to look for.
 * @return const Relation
 */
const Relation Relation::selectForConstant(unsigned int index, const std::string &value) const
{
    Relation result(this->name, this->scheme);
    for (Tuple tuple : this->tuples)
    {
        if (tuple.at(index) == value)
        {
            result.addTuple(tuple);
        }
    }
    return result;
}

/**
 * @brief SELECT on this Relation for attributes with the same value.
 * Returns a new Relation containing only Tuples where the values
 * at the given indices are equal.
 *
 * @param index1
 * @param index2
 * @return const Relation
 */
const Relation Relation::selectForEqualVariables(unsigned int index1,
                                                 unsigned int index2) const
{
    Relation result(this->name, this->scheme);
    for (Tuple tuple : this->tuples)
    {
        std::string v1 = tuple.at(index1);
        std::string v2 = tuple.at(index2);
        if (v1 == v2)
        {
            result.addTuple(tuple);
        }
    }
    return result;
}

/**
 * @brief Apply the PROJECT operator on this Relation.
 *
 * Returns a new Relation which includes only the attributes at the given
 * indices, in the given order.
 *
 * @param indices The indices of the attributes to include.
 * @return const Relation
 */
const Relation Relation::project(const std::vector<unsigned int> &indices) const
{
    Scheme projectedScheme = this->scheme.project(indices);
    Relation result(this->name, projectedScheme);
    for (Tuple tuple : this->tuples)
    {
        Tuple projectedTuple = tuple.project(indices);
        result.addTuple(projectedTuple);
    }
    return result;
}

/**
 * @brief Return a new Relation with its attributes renamed.
 *
 * @param newNames The new names of the attributes.
 * @return const Relation
 */
const Relation Relation::rename(std::vector<std::string> &newNames) const
{
    Scheme renamedScheme = scheme.rename(newNames);
    Relation result(this->name, renamedScheme);
    for (Tuple tuple : this->tuples)
    {
        result.addTuple(tuple.copy());
    }
    return result;
}

////
////
////

const Relation Relation::makeUnionCompatibleWith(const Relation &other)
{
    // TODO
}

const Relation Relation::unionWith(const Relation &other)
{
    // TODO
}

#endif
