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
    Tuple(vector<std::string> values) : vector<std::string>(values){};

    std::string toString(const Scheme &scheme) const
    {
        if (scheme.size() != this->size())
        {
            std::cerr << "[ERROR] Called toString() with a scheme and a tuple of different sizes." << std::endl;
            throw;
        }

        std::stringstream out;
        for (unsigned int i = 0; i < this->size(); i++)
        {
            if (i != 0)
            {
                out << " ";
            }
            out << scheme.at(i) << "=" << this->at(i);
        }
        return out.str();
    }

    /**
     * @brief Return a new Tuple which includes only the selected values in the given order.
     *
     * @param indices The indices of the values to include.
     * @return Tuple
     */
    const Tuple project(const std::vector<unsigned int> &indices) const
    {
        std::vector<std::string> values;
        for (unsigned int index : indices)
        {
            std::string value = this->at(index);
            values.push_back(value);
        }
        Tuple projectedTuple(values);
        return projectedTuple;
    }

    /**
     * @brief Return a copy of this Tuple.
     */
    const Tuple copy() const
    {
        std::vector<std::string> values;
        for (std::string value : *this)
        {
            values.push_back(value);
        }
        Tuple result(values);
        return result;
    }
};

#endif
