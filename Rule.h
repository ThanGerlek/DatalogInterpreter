#ifndef T2K_236PROJECT_RULE_H
#define T2K_236PROJECT_RULE_H

#include <iostream>
#include <vector>
#include "Predicate.h"

// TODO Test toString
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
    std::string toString()
    {
        if (body.size() == 0)
        {
            std::cout << "Error: rule with no body." << std::endl;
            throw;
        }

        std::string out = head.toString() + " :- " + body.at(0).toString();
        std::vector<Predicate>::const_iterator i = body.begin();
        for (i++; i != body.end(); i++)
        {
            out += "," + i->toString();
        }
        return out;
    }

private:
    const Predicate head;
    std::vector<Predicate> body;
};

#endif
