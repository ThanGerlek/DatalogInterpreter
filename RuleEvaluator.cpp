#ifndef CS236_PROJECT5_T2K_DATALOG_RULE_EVALUATOR_CPP
#define CS236_PROJECT5_T2K_DATALOG_RULE_EVALUATOR_CPP

#include "RuleEvaluator.h"

void RuleEvaluator::evaluate()
{
    std::vector<std::set<Node>> cliques = dependencyGraph.findAllCliques();
    for (std::set<Node> clique : cliques)
    {
        const std::set<Rule> ruleSet = convertNodeSetToRuleSet(clique);
        evaluateRuleSet(ruleSet);
    }
}

const std::set<Rule> RuleEvaluator::convertNodeSetToRuleSet(std::set<Node> clique)
{
    std::set<Rule> ruleSet;
    for (Node node : clique)
    {
        Rule rule = convertNodeToRule(node);
        ruleSet.insert(rule);
    }
    return ruleSet;
}

Rule RuleEvaluator::convertNodeToRule(Node node) const
{
    int ruleId = node.nodeId;
    Rule rule = program.getRuleFromId(ruleId);
}

/**
 * @brief Update the Database with the specified Rules of the DatalogProgram.
 */
void RuleEvaluator::evaluateRuleSet(const std::set<Rule> &rules)
{
    int iterations = 0;
    unsigned int prevSize = 0;
    do
    {
        iterations++;
        prevSize = database.size();

        for (Rule rule : rules)
        {
            evaluateRule(rule);
        }
    } while (prevSize != database.size());

    std::cout << std::endl
              << "Schemes populated after " << iterations << " passes through the Rules." << std::endl
              << std::endl;
}

void RuleEvaluator::evaluateRule(Rule rule)
{
    // Evaluate the predicates on the right-hand side of the rule
    Relation relation = evaluateRulePredicates(rule);

    // Project the columns that appear in the head predicate
    relation = database.projectForRule(relation, rule);

    // Union with the relation in the database (the table)
    std::string tableName = rule.getId();
    Relation table = database.getRelation(tableName);
    relation = relation.makeUnionCompatibleWith(table);
    // relation = relation.unionWith(table);

    // Print new results
    Relation newTuples = relation.subtract(table);
    printRuleResult(rule, newTuples); // TODO? Extract output?

    // Update relation in the database to the new relation
    database.unionIntoDatabase(relation, tableName);
}

const Relation RuleEvaluator::evaluateRulePredicates(Rule rule) const
{
    // Evaluate each predicate on the right-hand side of the rule
    // Join the relations that result

    const std::vector<Predicate> &predicates = rule.getPredicates();
    Relation result(rule.getId());

    for (Predicate predicate : predicates)
    {
        const Relation predicateRelation = evaluateRulePredicate(predicate);
        result = result.join(predicateRelation);
    }

    return result;
}

const Relation RuleEvaluator::evaluateRulePredicate(Predicate predicate) const
{
    // Use a sequence of select, project, and rename operations on the Database to evaluate the Rule predicate.

    std::string relationName = predicate.getId();
    Relation relation = database.getRelation(relationName);

    relation = database.selectForPredicate(relation, predicate);
    relation = database.projectForPredicate(relation, predicate);
    relation = database.renameForPredicate(relation, predicate);

    return relation;
}

void RuleEvaluator::printRuleResult(Rule rule, Relation results) const
{
    std::cout << rule.toString() << "." << std::endl;

    // Print Tuples
    for (Tuple tuple : results.getTuples())
    {
        if (tuple.size() > 0)
        {
            std::cout << "  " << tuple.toString(results.getScheme()) << std::endl;
        }
    }
}
#endif
