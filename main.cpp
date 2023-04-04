#ifndef PROJECT1_T2K_MAIN_CPP
#define PROJECT1_T2K_MAIN_CPP

#include <fstream>
#include <iostream>
#include "Scanner.h"
#include "Parser.h"
#include "DatalogDatabase.h"

std::string convertIFStreamToString(std::ifstream &ifs);

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

    std::string inputString = convertIFStreamToString(ifs);
    ifs.close();

    Scanner scanner(inputString);

    std::vector<Token> tokens;
    scanner.scanTokensInto(tokens);

    ////
    ////
    // Parse tokens

    DatalogProgram dlProgram;
    Parser parser(&tokens, &dlProgram);

    parser.parse();

    ////
    ////
    // Evaluate Database

    DatalogDatabase datalogdb(&dlProgram);

    datalogdb.evaluate();

    return 0;
}

std::string convertIFStreamToString(std::ifstream &ifs)
{
    std::string outStr = "";
    ifs.seekg(0, std::ios_base::end);                           // offset 0 from end
    outStr.resize(static_cast<long unsigned>(ifs.tellg()));     // resize string
    ifs.seekg(0, std::ios_base::beg);                           // offset 0 from beginning
    ifs.read(&outStr[0], static_cast<long int>(outStr.size())); // read data
    return outStr;
}

#endif
