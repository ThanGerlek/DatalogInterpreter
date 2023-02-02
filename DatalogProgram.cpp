#ifndef T2K_236PROJECT_DATALOG_PROGRAM_CPP
#define T2K_236PROJECT_DATALOG_PROGRAM_CPP

#include <sstream>
#include "DatalogProgram.h"

void DatalogProgram::addScheme(Predicate scheme) {schemes.push_back(scheme); };
void DatalogProgram::addFact(Predicate fact) { facts.push_back(fact); };
void DatalogProgram::addQuery(Predicate query) { queries.push_back(query); };
void DatalogProgram::addRule(Rule rule) { rules.push_back(rule); };

std::vector<Predicate> *DatalogProgram::getSchemes() { return &schemes; };
std::vector<Predicate> *DatalogProgram::getFacts() { return &facts; };
std::vector<Predicate> *DatalogProgram::getQueries() { return &queries; };
std::vector<Rule> *DatalogProgram::getRules() { return &rules; };


#endif
