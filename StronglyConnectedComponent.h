#ifndef CS236_PROJECT5_T2K_DATALOG_STONGLY_CONNECTED_COMPONENT_H
#define CS236_PROJECT5_T2K_DATALOG_STONGLY_CONNECTED_COMPONENT_H

#include <string>
#include <sstream>
#include "Rule.h"
#include "Relation.h"

struct StronglyConnectedComponent
{
private:
    std::vector<Rule> rules;
    int numPasses;
    std::string resultString;

public:
    StronglyConnectedComponent(){};

    std::string toString() const
    {
        std::stringstream out;
        out << "SCC: " << ruleList() << std::endl;
        out << resultString;
        out << numPasses << " passes: " << ruleList() << std::endl;
        return out.str();
    }

    void addIteration(Rule rule, Relation &resultRelation)
    {
        std::stringstream sstream;
        sstream << rule.toString() << "."
                     << std::endl;

        for (Tuple tuple : resultRelation.getTuples())
        {
            if (tuple.size() > 0)
            {
                sstream << "  " << tuple.toString(resultRelation.getScheme())
                             << std::endl;
            }
        }
        resultString += sstream.str();
    }

private:
    std::string ruleList() const
    {
        std::string out = "";
        for (Rule rule : rules)
        {
            if (out.length() != 0)
            {
                out += ", ";
            }
            out += "R" + rule.getRuleId();
        }
        return out;
    }
};

#endif
