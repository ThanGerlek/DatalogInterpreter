#ifndef CS236_PROJECT3_T2K_QUERY_RESULT_H
#define CS236_PROJECT3_T2K_QUERY_RESULT_H

#include "Relation.h"
#include "Predicate.h"

// TODO

class QueryResult
{
private:
    Predicate predicate;
    Relation relation;

public:
    QueryResult(Predicate queryPredicate, Relation resultsRelation) : predicate(queryPredicate), relation(resultsRelation){};

    std::string toString()
    {
        // TODO
        std::stringstream ss;
        ss << predicate.toString() << "? ";

        if (relation.size() == 0)
        {
            ss << "No" << std::endl;
        }
        else
        {
            ss << "Yes(" << relation.size() << ")" << std::endl;

            // Print Tuples
            for (Tuple tuple : relation.getTuples())
            {
                // TODO Handle no variables?
                ss << "  " << tuple.toString(relation.getScheme()) << std::endl;
            }
        }
        return ss.str();
    }

    /*
    For each query, output the query and a space. If the relation resulting from evaluating the query is empty, output 'No'. If the resulting relation is not empty, output 'Yes(n)' where n is the number of tuples in the resulting relation.

If there are variables in the query, output the tuples from the resulting relation.

Output each tuple on a separate line as a comma-space-separated list of pairs. Each pair has the form N='V', where N is the attribute name from the scheme and V is the value from the tuple. Output the name-value pairs in the same order as the variable names appear in the query. Indent the output of each tuple by two spaces.

Output the tuples in sorted order. Sort the tuples alphabetically based on the values in the tuples. Sort first by the value in the first position and if needed up to the value in the nth position.
*/
};

#endif
