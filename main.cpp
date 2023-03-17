#ifndef PROJECT1_T2K_MAIN_CPP
#define PROJECT1_T2K_MAIN_CPP

#include <fstream>
#include <iostream>
#include "Scanner.h"
#include "Parser.h"
#include "DatalogDatabase.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "Please include a file name." << std::endl;
        return 0;
    }

    ////
    ////
    // Scan file

    std::string filename = argv[1];

    std::ifstream ifs = std::ifstream(filename);
    if (!ifs.is_open())
    {
        std::cout << "Failed to open file." << std::endl;
        return 0;
    }

    Scanner scanner = Scanner(ifs);
    ifs.close();

    std::vector<Token> tokens;
    scanner.scan(tokens);

    ////
    ////
    // Parse tokens

    DatalogProgram dlProgram;
    Parser parser(&tokens, &dlProgram);

    parser.parse();

    ////
    ////
    // Load Database

    DatalogDatabase datalogdb(&dlProgram);

    datalogdb.evaluate();
    datalogdb.printQueries();

    return 0;
}

#endif
