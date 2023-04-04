#ifndef T2K_236PROJECT_RULE_H
#define T2K_236PROJECT_RULE_H

#include <iostream>
#include <vector>
#include "Predicate.h"

class Rule
{
public:
    Rule(Predicate _head) : head(_head){};
    ~Rule(){};

    Predicate getHead() const { return head; }
    std::string getId() const { return head.getId(); }
    const std::vector<Predicate> &getPredicates() const { return bodyPredicates; }
    void addBodyPredicate(Predicate p) { bodyPredicates.push_back(p); }

    std::string toString()
    {
        if (bodyPredicates.size() == 0)
        {
            std::cerr << "[ERROR] Tried to access a Rule with no body." << std::endl;
            throw;
        }

        std::string out = head.toString() + " :- " + bodyPredicates.at(0).toString();

        std::vector<Predicate>::const_iterator i = bodyPredicates.begin();
        for (i++; i != bodyPredicates.end(); i++)
        {
            out += "," + i->toString();
        }
        return out;
    }

private:
    Predicate head;
    std::vector<Predicate> bodyPredicates;
};

#endif
