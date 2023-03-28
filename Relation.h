#ifndef CS236_LAB4_T2K_RELATION_H
#define CS236_LAB4_T2K_RELATION_H

#include <set>
#include "Tuple.h"

// TODO Check/test for func(&x, &x) problems

class Relation
{
private:
    std::string name;
    Scheme scheme;
    std::set<Tuple> tuples;

public:
    Relation(const std::string &_name, const Scheme &_scheme)
        : name(_name), scheme(_scheme){};

    static bool joinable(const Scheme &leftScheme, const Scheme &rightScheme,
                         const Tuple &leftTuple, const Tuple &rightTuple);

    void addTuple(const Tuple &tuple);
    std::string toString() const;

    const Relation join(const Relation &right);
    std::string joinNames(std::string left, std::string right);
    const Scheme joinSchemes(const Scheme &left, const Scheme &right);
    const Tuple joinTuples(const Scheme &leftScheme, const Scheme &rightScheme, const Scheme &resultScheme, const Tuple &left, const Tuple &right);

    const Relation cross(const Relation &right);
    std::string crossNames(std::string left, std::string right);
    const Scheme crossSchemes(const Scheme &left, const Scheme &right);
    const Tuple crossTuples(const Tuple &left, const Tuple &right);

    const Relation selectForConstant(unsigned int u_index, const std::string &value) const;
    const Relation selectForEqualVariables(unsigned int u_index1, unsigned int u_index2) const;
    const Relation project(const std::vector<unsigned int> &u_indices) const;
    const Relation rename(std::vector<std::string> &newNames) const;

    Scheme getScheme() const { return scheme; }
    std::string getName() const { return name; }
    int size() const { return static_cast<int>(tuples.size()); }
    std::set<Tuple> getTuples() { return tuples; }
};

#endif
