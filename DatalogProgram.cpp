#ifndef T2K_236PROJECT_DATALOG_PROGRAM_CPP
#define T2K_236PROJECT_DATALOG_PROGRAM_CPP

#include <sstream>
#include "DatalogProgram.h"

void DatalogProgram::addScheme(Predicate scheme) { schemes.push_back(scheme); };
void DatalogProgram::addFact(Predicate fact) { facts.push_back(fact); };
void DatalogProgram::addQuery(Predicate query) { queries.push_back(query); };
void DatalogProgram::addRule(Rule rule) { rules.push_back(rule); };

std::vector<Predicate> *DatalogProgram::getSchemes() { return &schemes; };
std::vector<Predicate> *DatalogProgram::getFacts() { return &facts; };
std::vector<Predicate> *DatalogProgram::getQueries() { return &queries; };
std::vector<Rule> *DatalogProgram::getRules() { return &rules; };

std::string DatalogProgram::toString()
{
    // TODO
    std::stringstream ss;
    std::vector<Predicate>::iterator ip;
    std::vector<Rule>::iterator ir;

    ss << "Schemes(" << schemes.size() << "):" << std::endl;
    for (ip = schemes.begin(); ip != schemes.end(); ip++)
    {
        ss << ip->toString() << std::endl;
    }

    ss << "Facts(" << facts.size() << "):" << std::endl;
    for (ip = facts.begin(); ip != facts.end(); ip++)
    {
        ss << ip->toString() << std::endl;
    }

    ss << "Rules(" << rules.size() << "):" << std::endl;
    for (ir = rules.begin(); ir != rules.end(); ir++)
    {
        ss << ir->toString() << std::endl;
    }

    ss << "Queries(" << queries.size() << "):" << std::endl;
    for (ip = queries.begin(); ip != queries.end(); ip++)
    {
        ss << ip->toString() << std::endl;
    }

    ss << "[WIP] Domain" << std::endl;
    // TODO: Domain toString

    return ss.str();
}

#endif
