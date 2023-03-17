#ifndef CS236_PROJECT3_T2K_DATALOG_DATABASE_H
#define CS236_PROJECT3_T2K_DATALOG_DATABASE_H

#include "Database.h"
#include "DatalogProgram.h"

class DatalogDatabase : public Database
{
private:
    DatalogProgram *dlProgram;
    const Relation selectForQuery(Relation relation, const std::vector<Parameter> *params) const;
    const Relation projectForQuery(Relation relation, const std::vector<Parameter> *params) const;
    const Relation renameForQuery(Relation relation, const std::vector<Parameter> *params) const;

public:
    DatalogDatabase(DatalogProgram *_dlProgram) : dlProgram(_dlProgram){};
    void evaluateFacts();
    void evaluateSchemes();
    void evaluateQueries();
    std::string toString() const;
};

#endif
