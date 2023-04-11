#ifndef CS236_LAB4_T2K_RELATION_H
#define CS236_LAB4_T2K_RELATION_H

#include <set>
#include "Tuple.h"

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

    // Other set-operation helper functions
    static std::string unionNames(std::string left, std::string right);
    static std::string subtractNames(std::string left, std::string right);

    // Misc
    static bool contains(std::vector<std::string> &strs, std::string &str);
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
    std::set<Tuple> getTuples() const { return tuples; }
    unsigned int size() const { return static_cast<unsigned int>(tuples.size()); }

    bool containsTuple(Tuple &tuple) const;
    std::string toString() const;

    // Mathematical Relation operations
    const Relation join(const Relation &right) const;
    const Relation selectForConstant(unsigned int index, const std::string &value) const;
    const Relation selectForEqualVariables(unsigned int index1, unsigned int index2) const;
    const Relation project(const std::vector<unsigned int> &indices) const;
    const Relation project(const std::vector<std::string> &attributes) const;
    const Relation rename(std::vector<std::string> &newAttributeNames) const;

    const Relation makeUnionCompatibleWith(const Relation &other) const;
    bool isUnionCompatibleWith(const Relation &other) const;

    // Mathematical set operations
    const Relation unionWith(const Relation &other) const;
    const Relation subtract(const Relation &right) const;
};

#endif
