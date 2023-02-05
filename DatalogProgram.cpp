#ifndef T2K_236PROJECT_DATALOG_PROGRAM_CPP
#define T2K_236PROJECT_DATALOG_PROGRAM_CPP

#include <sstream>
#include "DatalogProgram.h"

void DatalogProgram::addScheme(Predicate scheme) { schemes.push_back(scheme); }
void DatalogProgram::addQuery(Predicate query) { queries.push_back(query); }
void DatalogProgram::addRule(Rule rule) { rules.push_back(rule); }
void DatalogProgram::addFact(Predicate fact)
{
    facts.push_back(fact);

    // Update domain
    for (std::vector<Parameter>::const_iterator i = fact.getParams().begin(); i != fact.getParams().end(); i++)
    {
        if (!i->isVariable())
        {
            domain.push_back(i->toString());
        }
    }
}

const std::vector<Predicate> *DatalogProgram::getSchemes() const { return &schemes; }
const std::vector<Predicate> *DatalogProgram::getFacts() const { return &facts; }
const std::vector<Predicate> *DatalogProgram::getQueries() const { return &queries; }
const std::vector<Rule> *DatalogProgram::getRules() const { return &rules; }

std::string DatalogProgram::toString()
{
    std::stringstream ss;
    std::vector<Predicate>::iterator ip;
    std::vector<Rule>::iterator ir;
    std::vector<std::string>::iterator is;

    ss << "Schemes(" << schemes.size() << "):" << std::endl;
    for (ip = schemes.begin(); ip != schemes.end(); ip++)
    {
        ss << "  " << ip->toString() << std::endl;
    }

    ss << "Facts(" << facts.size() << "):" << std::endl;
    for (ip = facts.begin(); ip != facts.end(); ip++)
    {
        ss << "  " << ip->toString() << "." << std::endl;
    }

    ss << "Rules(" << rules.size() << "):" << std::endl;
    for (ir = rules.begin(); ir != rules.end(); ir++)
    {
        ss << "  " << ir->toString() << "." << std::endl;
    }

    ss << "Queries(" << queries.size() << "):" << std::endl;
    for (ip = queries.begin(); ip != queries.end(); ip++)
    {
        ss << "  " << ip->toString() << "?" << std::endl;
    }

    ss << "Domain(" << domain.size() << "):" << std::endl;
    for (is = domain.begin(); is != domain.end(); is++)
    {
        ss << "  " << &is << std::endl;
    }

    // TODO: Domain toString

    return ss.str();
}

#endif
