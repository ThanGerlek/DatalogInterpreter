#ifndef CS236_LAB4_T2K_RELATION_H
#define CS236_LAB4_T2K_RELATION_H

#include <set>
#include "Tuple.h"

class Relation
{
private:
    std::string name;
    Scheme scheme;
    std::set<Tuple> tuples;

public:
    Relation(const std::string &_name, const Scheme &_scheme)
        : name(_name), scheme(_scheme){};

    void addTuple(const Tuple &tuple);
    std::string toString() const;

    Relation selectForConstant(int index, const std::string &value) const;
    Relation selectForEqualVariables(int index1, int index2) const;
};

#endif
