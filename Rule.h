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
    const std::vector<Predicate> &getPredicates() const { return body; }
    void addPredicate(Predicate p) { body.push_back(p); }

    std::string toString()
    {
        if (body.size() == 0)
        {
            std::cerr << "Error: tried to access a Rule with no body." << std::endl;
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
    Predicate head;
    std::vector<Predicate> body;
};

#endif
