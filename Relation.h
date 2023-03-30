#ifndef CS236_LAB4_T2K_RELATION_H
#define CS236_LAB4_T2K_RELATION_H

#include <set>
#include "Tuple.h"

// TODO. Check/test for func(&x, &x) problems
// TODO? Change QueryResult to not need getTuples()?

class Relation
{
private:
    // Private variables
    std::string name;
    Scheme scheme;
    std::set<Tuple> tuples;

    // join() functions
    static std::string joinNames(std::string left, std::string right);
    static const Scheme joinSchemes(const Scheme &left, const Scheme &right);
    static const Tuple joinTuples(const Scheme &leftScheme, const Scheme &rightScheme, const Tuple &left, const Tuple &right);

    // cross() functions
    static std::string crossNames(std::string left, std::string right);
    static const Scheme crossSchemes(const Scheme &left, const Scheme &right);
    static const Tuple crossTuples(const Tuple &left, const Tuple &right);

    // unionWith() functions
    static std::string unionNames(std::string &left, std::string &right);

    // Misc
    static bool contains(std::vector<std::string> strs, std::string str);
    static bool joinable(const Scheme &leftScheme, const Scheme &rightScheme,
                         const Tuple &leftTuple, const Tuple &rightTuple);

public:
    // Constructors
    Relation(const std::string &_name) : name(_name){};
    Relation(const std::string &_name, const Scheme &_scheme)
        : name(_name), scheme(_scheme){};

    // Manipulators
    void addTuple(const Tuple &tuple);
    void setName(std::string &newName);

    // Accessors
    std::string getName() const { return name; }
    Scheme getScheme() const { return scheme; }
    std::set<Tuple> getTuples() { return tuples; }
    int size() const { return static_cast<int>(tuples.size()); }

    bool containsTuple(Tuple &tuple) const;
    std::string toString() const;

    // Mathematical Relation operations
    const Relation join(const Relation &right) const;
    const Relation cross(const Relation &right) const;
    const Relation selectForConstant(unsigned int u_index, const std::string &value) const;
    const Relation selectForEqualVariables(unsigned int u_index1, unsigned int u_index2) const;
    const Relation project(const std::vector<unsigned int> &u_indices) const;
    const Relation project(const std::vector<std::string> &attributes) const;
    const Relation rename(std::vector<std::string> &newNames) const;

    const Relation makeUnionCompatibleWith(const Relation &other) const;
    bool isUnionCompatibleWith(const Relation &other) const;

    // Mathematical set operations
    const Relation unionWith(const Relation &other) const;
};

#endif
