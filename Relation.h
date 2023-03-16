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
    Relation(const std::string &name, const Scheme &scheme)
        : name(name), scheme(scheme) {}

    void addTuple(const Tuple &tuple)
    {
        if (tuple.size() != scheme.size())
        {
            std::cerr << "Tried to add tuple to a relation with a scheme of a different size" << std::endl;
            throw;
        }

        tuples.insert(tuple);
    }

    std::string toString() const
    {
        std::stringstream out;
        for (auto &tuple : tuples)
            out << tuple.toString(scheme) << std::endl;
        return out.str();
    }
};

#endif
