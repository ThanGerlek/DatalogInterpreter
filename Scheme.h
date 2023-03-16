#ifndef CS236_LAB4_T2K_SCHEME_H
#define CS236_LAB4_T2K_SCHEME_H

#include <vector>
#include <string>

class Scheme : public std::vector<std::string>
{
public:
    Scheme(vector<std::string> names) : vector<std::string>(names){};
};

#endif
