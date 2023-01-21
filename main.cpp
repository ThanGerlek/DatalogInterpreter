#ifndef PROJECT1_T2K_MAIN_CPP
#define PROJECT1_T2K_MAIN_CPP

#include <fstream>
#include <iostream>
#include "Scanner.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "Please include a file name." << std::endl;
        throw;
    }

    std::string filename = argv[1];
    filename = "input.txt"; // TODO Un-hardcode input file
    std::ifstream ifs = std::ifstream(filename);
    if (!ifs.is_open())
    {
        std::cout << "Failed to open file." << std::endl;
        throw;
    }

    //? Can this be more efficient?
    std::stringstream input;
    std::string line;
    while (std::getline(ifs, line))
    {
        input << std::endl
              << line;
    }

    Scanner scanner = Scanner(input.str());

    Token token;
    int numTokens = 0;
    while (scanner.hasNext())
    {
        token = scanner.scanToken();
        std::cout << token.toString() << std::endl;
        numTokens++;
    }

    std::cout << "Total Tokens = " << numTokens << std::endl;

    return 0;
}

#endif
