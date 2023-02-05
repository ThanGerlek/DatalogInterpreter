#ifndef PROJECT1_T2K_MAIN_CPP
#define PROJECT1_T2K_MAIN_CPP

#include <fstream>
#include <iostream>
#include "Scanner.h"
#include "Parser.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "Please include a file name." << std::endl;
        throw;
    }

    // Scan file

    std::string filename = argv[1];
#ifdef DEBUG
    std::cout << "Scanning file '" << filename << "'" << std::endl;
#endif

    std::ifstream ifs = std::ifstream(filename);
    if (!ifs.is_open())
    {
        std::cout << "Failed to open file." << std::endl;
        throw;
    }

    Scanner scanner = Scanner(ifs);
    ifs.close();

    std::vector<Token> tokens;
    scanner.scan(tokens);

    // DEBUG
    for (std::vector<Token>::iterator i = tokens.begin(); i != tokens.end(); i++)
    {
        std::cout << i->toString() << "  ";
    }
    std::cout << std::endl;

#ifdef DEBUG
    std::cout << "Finished scanning, total tokens = " << tokens.size() << ". Attempting to parse..." << std::endl;
#endif

    // Parse tokens

    DatalogProgram dlp;
    Parser p(&tokens, &dlp);

    p.parse();

#ifdef DEBUG
    std::cout << "Finished parsing." << std::endl;
#endif

    return 0;
}

#endif
