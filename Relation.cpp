#ifndef CS236_LAB4_T2K_RELATION_CPP
#define CS236_LAB4_T2K_RELATION_CPP

#include "Relation.h"

void Relation::addTuple(const Tuple &tuple)
{
    if (tuple.size() != scheme.size())
    {
        std::cerr << "Tried to add tuple to a relation with a scheme of a different size" << std::endl;
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

#endif
