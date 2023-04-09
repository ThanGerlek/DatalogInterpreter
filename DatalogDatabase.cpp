#ifndef CS236_PROJECT3_T2K_DATALOG_DATABASE_CPP
#define CS236_PROJECT3_T2K_DATALOG_DATABASE_CPP

#include "DatalogDatabase.h"
#include "RuleEvaluator.h"

// TODO. Refactor

/**
 * @brief Update the internal Database with the data from the Scheme list of the DatalogProgram.
 */
void DatalogDatabase::evaluateSchemes()
{
    for (Predicate predicate : *(dlProgram->getSchemes()))
    {
        std::vector<std::string> attributeNames = predicate.getParamStrings();
        std::string relationName = predicate.getName();
        Scheme scheme(attributeNames);
        Relation relation(relationName, scheme);
        addRelation(relation);
    }
}

/**
 * @brief Update the internal Database with the data from the Fact list of the DatalogProgram.
 */
void DatalogDatabase::evaluateFacts()
{
    for (Predicate predicate : *(dlProgram->getFacts()))
    {
        std::vector<std::string> values = predicate.getParamStrings();
        std::string relationName = predicate.getName();
        Tuple tuple(values);
        addTuple(tuple, relationName);
    }
}

/**
 * @brief Update the internal Database with the data from the Query list of the DatalogProgram.
 */
void DatalogDatabase::evaluateQueries()
{
    std::cout << "Query Evaluation" << std::endl;

    // For each query in the Datalog program:
    for (Predicate queryPredicate : *(dlProgram->getQueries()))
    {
        // Get the Relation from the Database with the same name as the predicate name in the query.

        std::string relationName = queryPredicate.getName();

        if (!hasRelation(relationName)) // TODO. Extract error handling
        {
            std::cerr << "[ERROR] Invalid query: no such relation." << std::endl;
            throw;
        }

        unsigned int index = getIndex(relationName);
        Relation relation = relations.at(index);

        // Use a sequence of select, project, and rename operations on the Database to evaluate the query.
        relation = selectForPredicate(relation, queryPredicate);
        relation = projectForPredicate(relation, queryPredicate); // TODO? Reuse projectedIndices? Both project and rename use it.
        relation = renameForPredicate(relation, queryPredicate);

        printQueryResult(queryPredicate, relation);
    }
}

void DatalogDatabase::printQueryResult(Predicate query, Relation results) const
{
    std::cout << query.toString() << "? ";

    if (results.size() == 0)
    {
        std::cout << "No" << std::endl;
    }
    else
    {
        std::cout << "Yes(" << results.size() << ")" << std::endl;

        // Print Tuples
        for (Tuple tuple : results.getTuples())
        {
            if (tuple.size() > 0)
            {
                std::cout << "  " << tuple.toString(results.getScheme()) << std::endl;
            }
        }
    }
}

////
////
////
////

const Relation DatalogDatabase::projectForRule(const Relation &relation, Rule rule) const
{
    std::vector<std::string> attributes = rule.getHead().getParamStrings();
    Relation result = relation.project(attributes);
    return result;
}

////
////
////
////
////
////

/**
 * @brief Apply SELECT operations to select the tuples from the given Relation that match the predicate.
 *
 * @param relation The relation to apply SELECT to.
 * @param params The Parameter list of the current predicate.
 * @return const Relation
 */
const Relation DatalogDatabase::selectForPredicate(Relation relation, Predicate predicate) const
{
    std::vector<Parameter> *params = predicate.getParams();
    // Iterate over the parameters of the predicate: If the parameter is a constant, select the tuples from the Relation that have the same value as the constant in the same position as the constant. If the parameter is a variable and the same variable name appears later in the predicate, select the tuples from the Relation that have the same value in both positions where the variable name appears.

    if (params->size() != relation.getScheme().size())
    {
        std::cerr << "[ERROR] Tried to selectForPredicate() with mismatched sizes." << std::endl;
        throw;
    }

    for (unsigned int i = 0; i < params->size(); i++)
    {
        Parameter param = params->at(i);
        if (param.isVariable())
        {
            // Check if this variable is also used in another Parameter later in the predicate
            for (unsigned int j = i; j < params->size(); j++)
            {
                if (params->at(j).isVariable() && params->at(j).getValue() == param.getValue())
                {
                    // If so, SELECT the Relation for equal values of the two Parameters
                    relation = relation.selectForEqualVariables(i, j);
                }
            }
        }
        else
        {
            relation = relation.selectForConstant(i, param.getValue());
        }
    }

    return relation;
}

/**
 * @brief Calculate the indices of the attributes of the current query that will be left after projecting.
 * @details
 * A list of unsigned ints representing Parameter indices is returned. In effect, it takes attribute indices
 * from after the projection, and maps them to to their corresponding indices from before the projection.
 * Only Parameters that are variables will be kept and only one of each variable.
 *
 * @param params The Parameter list of the current query.
 * @return std::vector<unsigned int> The list of indices.
 */
std::vector<unsigned int> DatalogDatabase::getProjectedIndices(const std::vector<Parameter> *params) const
{
    // TODO. Rename and redoc--make this a lot more understandable
    std::vector<unsigned int> projectedIndices;

    for (unsigned int i = 0; i < params->size(); i++)
    {
        Parameter param = params->at(i);
        if (param.isVariable())
        {
            // Don't include this variable if it was already added at a different index
            bool alreadyContains = false;
            for (unsigned int j = 0; j < i; j++)
            {
                if (params->at(j).getValue() == param.getValue())
                {
                    alreadyContains = true;
                }
            }
            if (!alreadyContains)
            {
                projectedIndices.push_back(i);
            }
        }
    }
    return projectedIndices;
}

/**
 * @brief Apply PROJECT operations to keep only attributes that correspond to the positions of the variables in the predicate in the given order.
 *
 * @param relation The relation to apply PROJECT to.
 * @param projectedIndices The indices of the attributes to keep after the projection.
 * @return const Relation
 */
const Relation DatalogDatabase::projectForPredicate(Relation relation, Predicate predicate) const
{
    std::vector<unsigned int> projectedIndices = getProjectedIndices(predicate.getParams());
    return relation.project(projectedIndices);
}

/**
 * @brief Apply RENAME operations to rename the scheme of the Relation to the names of the variables found in the predicate.
 *
 * @param relation The relation to apply RENAME to.
 * @param params The Parameter list of the current predicate.
 * @param projectedIndices The indices of the attributes kept after projection.
 * @return const Relation
 */
const Relation DatalogDatabase::renameForPredicate(Relation relation, Predicate predicate) const
{
    std::vector<Parameter> *params = predicate.getParams();
    std::vector<unsigned int> projectedIndices = getProjectedIndices(params);

    std::vector<std::string> newNames;

    for (unsigned int finalIndex = 0; finalIndex < projectedIndices.size(); finalIndex++)
    {
        unsigned int originalIndex = projectedIndices.at(finalIndex);
        std::string newName = params->at(originalIndex).getValue();
        newNames.push_back(newName);
    }

    Relation renamedRelation = relation.rename(newNames);
    return renamedRelation;
}

std::string DatalogDatabase::toString() const
{
    std::stringstream ss;
    ss << "-- Datalog Database --" << std::endl
       << std::endl;
    for (Relation relation : this->relations)
    {
        ss << "Relation '" << relation.getName() << "'" << std::endl;
        ss << relation.toString() << std::endl;
    }
    return ss.str();
}

#endif
