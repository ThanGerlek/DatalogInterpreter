#ifndef CS236_LAB5_T2K_DATALOG_DATALOG_INTERPRETER_CPP
#define CS236_LAB5_T2K_DATALOG_DATALOG_INTERPRETER_CPP

#include <fstream>
#include <iostream>
#include "DependencyGraphBuilder.h"
#include "DatalogInterpreter.h"
#include "Parser.h"
#include "RuleEvaluator.h"

void DatalogInterpreter::run()
{
    DatalogProgram program;

    Graph dependencyGraph =
        DependencyGraphBuilder::buildGraphFromProgram(program);
    printDependencies(dependencyGraph);

    DatalogDatabase dlDatabase(&program);
    dlDatabase.evaluateSchemes();
    dlDatabase.evaluateFacts();
    evaluateRules(dlDatabase, program, dependencyGraph);
    dlDatabase.evaluateQueries();
}

void DatalogInterpreter::readFile(DatalogProgram &program)
{
    std::vector<Token> tokens;
    Scanner scanner = createScanner();
    scanner.scanTokensInto(tokens);
    Parser parser(&tokens, &program);
    parser.parseTokensIntoDatalogProgram();
}

Scanner DatalogInterpreter::createScanner() const
{
    std::ifstream ifs = std::ifstream(filename);
    if (!ifs.is_open())
    {
        std::cout << "Failed to open file." << std::endl;
        throw;
    }
    std::string inputString = convertIFStreamToString(ifs);
    ifs.close();

    return Scanner(inputString);
}

void DatalogInterpreter::printDependencies(Graph &dependencyGraph)
{
    std::cout << "Dependency Graph" << std::endl
              << dependencyGraph.toString() << std::endl;
}

void DatalogInterpreter::evaluateRules(DatalogDatabase &dlDatabase,
                                       DatalogProgram &program,
                                       Graph &dependencyGraph)
{
    RuleEvaluator evaluator(dlDatabase, program, dependencyGraph);
    evaluator.evaluate();
}

std::string DatalogInterpreter::convertIFStreamToString(std::ifstream &ifs)
{
    std::string outStr = "";
    ifs.seekg(0, std::ios_base::end);                           // offset 0 from end
    outStr.resize(static_cast<long unsigned>(ifs.tellg()));     // resize string
    ifs.seekg(0, std::ios_base::beg);                           // offset 0 from beginning
    ifs.read(&outStr[0], static_cast<long int>(outStr.size())); // read data
    return outStr;
}

#endif
