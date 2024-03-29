#ifndef CS236_LAB5_T2K_DATALOG_DATALOG_INTERPRETER_H
#define CS236_LAB5_T2K_DATALOG_DATALOG_INTERPRETER_H

#include <string>
#include "DatalogDatabase.h"
#include "Graph.h"
#include "Scanner.h"

// TODO. DatalogFileReader

class DatalogInterpreter
{
private:
    std::string filename;

    void readFile(DatalogProgram &program);
    void evaluate(DatalogDatabase &dlDatabase,
                  DatalogProgram &program,
                  Graph &dependencyGraph);

    static void printDependencies(Graph &dependencyGraph);

    Scanner createScanner() const;
    static std::string convertIFStreamToString(std::ifstream &ifs);

public:
    DatalogInterpreter(std::string _filename) : filename(_filename){};
    void run();
};

#endif
