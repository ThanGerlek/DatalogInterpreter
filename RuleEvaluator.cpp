#ifndef CS236_PROJECT5_T2K_DATALOG_RULE_EVALUATOR_CPP
#define CS236_PROJECT5_T2K_DATALOG_RULE_EVALUATOR_CPP

#include "RuleEvaluator.h"

void RuleEvaluator::evaluateRules()
{
    std::vector<StronglyConnectedComponent> components;
    std::vector<std::set<int>> cliques = dependencyGraph.findAllCliques();
    for (std::set<int> clique : cliques)
    {
        const std::set<Rule> ruleSet = convertIdSetToRuleSet(clique);
        StronglyConnectedComponent component = buildSCCFromRuleSet(ruleSet);
        components.push_back(component);
    }
    printRuleEvaluationResults(components);
}

const std::set<Rule> RuleEvaluator::convertIdSetToRuleSet(std::set<int> clique)
{
    std::set<Rule> ruleSet;
    for (int id : clique)
    {
        Rule rule = convertIdToRule(id);
        ruleSet.insert(rule);
    }
    return ruleSet;
}

Rule RuleEvaluator::convertIdToRule(int id) const
{
    return program.getRuleFromId(id);
}

/**
 * @brief Update the Database with the specified Rules of the DatalogProgram.
 */
StronglyConnectedComponent RuleEvaluator::buildSCCFromRuleSet(const std::set<Rule> &rules)
{
    StronglyConnectedComponent component;

    int numPasses = 0;
    unsigned int prevSize = 0;
    do
    {
        numPasses++;
        prevSize = database.size();

        for (Rule rule : rules)
        {
            Relation newRules = evaluateRule(rule);
            component.addIteration(rule, newRules);
        }
    } while (prevSize != database.size());

    return component;
}

Relation RuleEvaluator::evaluateRule(Rule rule)
{
    // Evaluate the predicates on the right-hand side of the rule
    Relation relation = evaluateRulePredicates(rule);

    // Project the columns that appear in the head predicate
    relation = database.projectForRule(relation, rule);

    // Union with the relation in the database (the table)
    std::string tableName = rule.getName();
    Relation table = database.getRelation(tableName);
    relation = relation.makeUnionCompatibleWith(table);
    database.unionIntoDatabase(relation, tableName);

    Relation newTuples = relation.subtract(table);

    return newTuples;
}

const Relation RuleEvaluator::evaluateRulePredicates(Rule rule) const
{
    // Evaluate each predicate on the right-hand side of the rule
    // Join the relations that result

    const std::vector<Predicate> &predicates = rule.getPredicates();
    Relation result(rule.getName());

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

    std::string relationName = predicate.getName();
    Relation relation = database.getRelation(relationName);

    relation = database.selectForPredicate(relation, predicate);
    relation = database.projectForPredicate(relation, predicate);
    relation = database.renameForPredicate(relation, predicate);

    return relation;
}

void RuleEvaluator::printRuleEvaluationResults(const std::vector<StronglyConnectedComponent> &components) const
{
    std::cout << "Rule Evaluation" << std::endl;
    for (const StronglyConnectedComponent &component : components)
    {
        std::cout << component.toString();
    }
}
#endif
