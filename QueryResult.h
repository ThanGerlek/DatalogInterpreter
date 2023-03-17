#ifndef CS236_PROJECT3_T2K_QUERY_RESULT_H
#define CS236_PROJECT3_T2K_QUERY_RESULT_H

#include "Relation.h"
#include "Predicate.h"

// TODO

class QueryResult
{
private:
    Predicate predicate;
    Relation results;

public:
    QueryResult(Predicate queryPredicate, Relation resultsRelation) : predicate(queryPredicate), results(resultsRelation){};
    std::string toString()
    {
        // TODO
    }
};

#endif
