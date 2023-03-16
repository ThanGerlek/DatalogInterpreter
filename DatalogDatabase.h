#ifndef CS236_PROJECT3_T2K_DATALOG_DATABASE_H
#define CS236_PROJECT3_T2K_DATALOG_DATABASE_H

#include "Database.h"
#include "DatalogProgram.h"

class DatalogDatabase : public Database
{
private:
    DatalogProgram *dlProgram;
    Relation selectForQuery(Relation relation, const std::vector<Parameter> *params);
    Relation projectForQuery(Relation relation, const std::vector<Parameter> *params);
    Relation renameForQuery(Relation relation, const std::vector<Parameter> *params);

public:
    DatalogDatabase(DatalogProgram *_dlProgram) : dlProgram(_dlProgram){};
    void evaluateFacts();
    void evaluateSchemes();
    void evaluateQueries();
    std::string toString();
};

#endif
