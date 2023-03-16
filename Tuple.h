#ifndef CS236_LAB4_T2K_TUPLE_H
#define CS236_LAB4_T2K_TUPLE_H

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include "Scheme.h"

class Tuple : public std::vector<std::string>
{
public:
    Tuple(vector<std::string> values) : vector<std::string>(values){}; // TODO? Is this calling the base class's construstor?

    std::string toString(const Scheme &scheme) const
    {
        const Tuple &tuple = *this; // TODO? When is this needed?

        if (scheme.size() != tuple.size())
        {
            std::cerr << "Called toString() with a scheme and tuple of different sizes" << std::endl;
            throw;
        }

        std::stringstream out;
        for (unsigned int ui = 0; ui < tuple.size(); ui++)
        {
            if (ui != 0)
            {
                out << ", ";
            }
            out << scheme.at(ui) << "=" << tuple.at(ui);
        }
        return out.str();
    }

private:
};

#endif
