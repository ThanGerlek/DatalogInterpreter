#ifndef CS236_PROJECT3_T2K_DATALOG_DATABASE_CPP
#define CS236_PROJECT3_T2K_DATALOG_DATABASE_CPP

#include "DatalogDatabase.h"

/**
 * @brief (WIP) Evaluate and load the results of the DatalogProgram's queries.
 * WIP: does not yet evaluate Rules.
 */
void DatalogDatabase::evaluate()
{
    evaluateSchemes();
    evaluateFacts();
    evaluateRules();
    evaluateQueries();
}

/**
 * @brief Print the results of the DatalogProgram's queries.
 */
void DatalogDatabase::printQueries() const
{
    for (QueryResult queryResult : queryResults)
    {
        std::cout << queryResult.toString();
    }
}

/**
 * @brief Update the internal Database with the data from the Scheme list of the DatalogProgram.
 */
void DatalogDatabase::evaluateSchemes()
{
    for (Predicate predicate : *(dlProgram->getSchemes()))
    {
        std::vector<std::string> attributeNames = predicate.getParamStrings();
        std::string relationName = predicate.getId();
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
    // TODO? Check if facts ever contain variables (I'm assuming they don't)
    for (Predicate predicate : *(dlProgram->getFacts()))
    {
        std::vector<std::string> values = predicate.getParamStrings();
        std::string relationName = predicate.getId();
        Tuple tuple(values);
        addTuple(tuple, relationName);
    }
}

/**
 * @brief Update the internal Database with the Rule list of the DatalogProgram.
 */
void DatalogDatabase::evaluateRules()
{
    for (Rule rule : *(this->dlProgram->getRules()))
    {
        evaluateRule(rule);
    }
}

/**
 * @brief Update the internal Database with the data from the Query list of the DatalogProgram.
 */
void DatalogDatabase::evaluateQueries()
{
    // For each query in the Datalog program:
    for (Predicate queryPredicate : *(dlProgram->getQueries()))
    {
        // Get the Relation from the Database with the same name as the predicate name in the query.

        std::vector<Parameter> *params = queryPredicate.getParams();
        std::string relationName = queryPredicate.getId();

        int index = getIndex(relationName);
        if (index < 0)
        {
            std::cerr << "[ERROR] Invalid query: no such relation." << std::endl;
            throw;
        }
        Relation relation = relations.at(static_cast<unsigned int>(index));

        // Use a sequence of select, project, and rename operations on the Database to evaluate the query.
        relation = selectForQuery(relation, params);
        std::vector<unsigned int> projectedIndices = getProjectedIndices(params);
        relation = projectForQuery(relation, projectedIndices);
        relation = renameForQuery(relation, params, projectedIndices);

        QueryResult qResult(queryPredicate, relation);
        queryResults.push_back(qResult);
    }

    hasEvaluatedQueries = true;
}

void DatalogDatabase::evaluateRule(Rule rule)
{
    // Evaluate the predicates on the right-hand side of the rule
    Relation relation = evaluateRulePredicates(rule);

    // Project the columns that appear in the head predicate
    relation = projectRuleColumns(relation, rule);

    // Union with the relation in the database (the table)
    std::string tableName = rule.getTableName();
    Relation table = this->getRelation(tableName);
    relation = relation.makeUnionCompatibleWith(table);
    relation = relation.unionWith(table);

    // Update relation in the database to the new relation
    updateRelation(tableName, relation);
}

const Relation DatalogDatabase::evaluateRulePredicates(Rule rule) const
{
    // Evaluate each predicate on the right-hand side of the rule
    // Join the relations that result

    const std::vector<Predicate> &predicates = rule.getPredicates();
    Relation result(rule.getTableName());

    for (Predicate predicate : predicates)
    {
        const Relation predicateRelation = evaluateRulePredicate(predicate);
        result = result.join(predicateRelation);
    }

    return result;
}

const Relation DatalogDatabase::evaluateRulePredicate(Predicate predicate) const
{
    // TODO
}

const Relation DatalogDatabase::projectRuleColumns(const Relation &relation, Rule rule) const
{
    // TODO
}

////
////
////
////
////
////

/**
 * @brief Apply SELECT operations to select the tuples from the given Relation that match the query.
 *
 * @param relation The relation to apply SELECT to.
 * @param params The Parameter list of the current query.
 * @return const Relation
 */
const Relation DatalogDatabase::selectForQuery(Relation relation, const std::vector<Parameter> *params) const
{
    // Iterate over the parameters of the query: If the parameter is a constant, select the tuples from the Relation that have the same value as the constant in the same position as the constant. If the parameter is a variable and the same variable name appears later in the query, select the tuples from the Relation that have the same value in both positions where the variable name appears.
    // TODO Error if params and relation.scheme don't match in size?

    for (unsigned int ui = 0; ui < params->size(); ui++)
    {
        Parameter param = params->at(ui);
        if (param.isVariable())
        {
            // Check if this variable is also used in another Parameter later in the query
            for (unsigned int uj = ui; uj < params->size(); uj++)
            {
                if (params->at(uj).isVariable() && params->at(uj).getValue() == param.getValue())
                {
                    // If so, SELECT the Relation for equal values of the two Parameters
                    relation = relation.selectForEqualVariables(ui, uj);
                }
            }
        }
        else
        {
            relation = relation.selectForConstant(ui, param.getValue());
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
 * @brief Apply PROJECT operations to keep only attributes that correspond to the positions of the variables in the query in the given order.
 *
 * @param relation The relation to apply PROJECT to.
 * @param projectedIndices The indices of the attributes to keep after the projection.
 * @return const Relation
 */
const Relation DatalogDatabase::projectForQuery(Relation relation, std::vector<unsigned int> projectedIndices) const
{
    return relation.project(projectedIndices);
}

/**
 * @brief Apply RENAME operations to rename the scheme of the Relation to the names of the variables found in the query.
 *
 * @param relation The relation to apply RENAME to.
 * @param params The Parameter list of the current query.
 * @param projectedIndices The indices of the attributes kept after projection.
 * @return const Relation
 */
const Relation DatalogDatabase::renameForQuery(Relation relation, const std::vector<Parameter> *params,
                                               std::vector<unsigned int> projectedIndices) const
{
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
