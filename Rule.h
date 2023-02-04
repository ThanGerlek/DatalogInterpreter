#ifndef T2K_236PROJECT_RULE_H
#define T2K_236PROJECT_RULE_H

#include <vector>
#include "Predicate.h"

// TODO Implement toString
// TODO Set to return const vector

class Rule
{
public:
    Rule(Predicate _head) : head(_head){};
    ~Rule(){};
    void addPredicate(Predicate p) { body.push_back(p); }
    Predicate getHead() const { return head; }
    Predicate getPredicate(unsigned uindex) const { return body.at(uindex); }
    int numPredicates() const { return static_cast<int>(body.size()); }
    std::string toString() { return ""; }

private:
    const Predicate head;
    std::vector<Predicate> body;
};

#endif
