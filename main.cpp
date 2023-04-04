#ifndef PROJECT1_T2K_MAIN_CPP
#define PROJECT1_T2K_MAIN_CPP

#include "DatalogInterpreter.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "Please include a file name." << std::endl;
        return 0;
    }
    std::string filename = argv[1];

    DatalogInterpreter interpreter(filename);
    interpreter.run();

    return 0;
}

#endif
