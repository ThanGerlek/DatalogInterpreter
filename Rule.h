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
    std::string getName() const { return head.getName(); }
    unsigned size() const { return static_cast<unsigned>(bodyPredicates.size()); }
    Predicate getBodyPredicate(unsigned index) const { return bodyPredicates.at(index); }

    const std::vector<Predicate> &getPredicates() const { return bodyPredicates; } // TODO. Remove
    void addBodyPredicate(Predicate p) { bodyPredicates.push_back(p); }

    std::string toString() const
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

    bool operator<(Rule other) const
    {
        return this->ruleId < other.ruleId;
    }
    bool operator>(Rule other) const
    {
        return this->ruleId > other.ruleId;
    }

    int getRuleId() const
    {
        return ruleId;
    }

private:
    Predicate head;
    std::vector<Predicate> bodyPredicates;
    int ruleId;
};

#endif
