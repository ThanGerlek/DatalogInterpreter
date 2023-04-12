#ifndef T2K_236PROJECT_DATALOG_PROGRAM_CPP
#define T2K_236PROJECT_DATALOG_PROGRAM_CPP

#include <sstream>
#include "DatalogProgram.h"

const std::vector<Predicate> *DatalogProgram::getSchemes() const { return &schemes; }
const std::vector<Predicate> *DatalogProgram::getFacts() const { return &facts; }
const std::vector<Predicate> *DatalogProgram::getQueries() const { return &queries; }
const std::vector<Rule> *DatalogProgram::getRules() const { return &rules; }
const std::set<std::string> *DatalogProgram::getDomain() const { return &domain; }

void DatalogProgram::addScheme(Predicate scheme) { schemes.push_back(scheme); }
void DatalogProgram::addQuery(Predicate query) { queries.push_back(query); }
void DatalogProgram::addFact(Predicate fact) { facts.push_back(fact); }
void DatalogProgram::addToDomain(std::string str) { domain.insert(str); }

void DatalogProgram::addRule(Rule rule)
{
    int ruleId = static_cast<int>(rules.size());
    rule.setId(ruleId);
    rules.push_back(rule);
}

Rule DatalogProgram::getRuleFromId(int ruleId) const
{
    unsigned index = static_cast<unsigned>(ruleId);
    return rules.at(index);
}

std::string DatalogProgram::toString()
{
    std::stringstream ss;

    ss << "Schemes(" << schemes.size() << "):" << std::endl;
    for (Predicate p : schemes)
    {
        ss << "  " << p.toString() << std::endl;
    }

    ss << "Facts(" << facts.size() << "):" << std::endl;
    for (Predicate p : facts)
    {
        ss << "  " << p.toString() << "." << std::endl;
    }

    ss << "Rules(" << rules.size() << "):" << std::endl;
    for (Rule r : rules)
    {
        ss << "  " << r.toString() << "." << std::endl;
    }

    ss << "Queries(" << queries.size() << "):" << std::endl;
    for (Predicate p : queries)
    {
        ss << "  " << p.toString() << "?" << std::endl;
    }

    ss << "Domain(" << domain.size() << "):" << std::endl;
    for (std::string str : domain)
    {
        ss << "  " << str << std::endl;
    }

    return ss.str();
}

#endif
