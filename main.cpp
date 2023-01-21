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

    // Get data from file into string
    std::string input;
    ifs.seekg(0, std::ios_base::end);  // offset 0 from end
    input.resize(ifs.tellg());         // resize string
    ifs.seekg(0, std::ios_base::beg);  // offset 0 from beginning
    ifs.read(&input[0], input.size()); // read data
    ifs.close();

    Scanner scanner = Scanner(input);

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
