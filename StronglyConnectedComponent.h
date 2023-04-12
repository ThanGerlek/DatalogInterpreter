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
    std::stringstream resultStream;

public:
    StronglyConnectedComponent(){};

    std::string toString()
    {
        std::stringstream out;
        out << "SCC: " << ruleList() << std::endl;
        out << resultStream.str();
        out << numPasses << " passes: " << ruleList() << std::endl;
        return out.str();
    }

    void addIteration(Rule rule, Relation &resultRelation)
    {
        resultStream << rule.toString() << "."
                     << std::endl;

        for (Tuple tuple : resultRelation.getTuples())
        {
            if (tuple.size() > 0)
            {
                resultStream << "  " << tuple.toString(resultRelation.getScheme())
                             << std::endl;
            }
        }
    }

private:
    std::string ruleList()
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
