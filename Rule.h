#ifndef T2K_236PROJECT_RULE_H
#define T2K_236PROJECT_RULE_H

#include <vector>
#include "Predicate.h"

class Rule
{
public:
    Rule(Predicate _head) : head(_head) {};
    ~Rule(){};
    void addPredicate(Predicate p);
    Predicate getHead() const;
    Predicate getPredicate(int index) const;

private:
    const Predicate head;
    std::vector<Predicate> body;
};

#endif
