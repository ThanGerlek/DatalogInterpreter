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
    // TODO? Check what this line is doing (calling the base class's construstor?)
    Tuple(vector<std::string> values) : vector<std::string>(values){};

    std::string toString(const Scheme &scheme) const
    {
        if (scheme.size() != this->size())
        {
            std::cerr << "Called toString() with a scheme and tuple of different sizes" << std::endl;
            throw;
        }

        std::stringstream out;
        for (unsigned int ui = 0; ui < this->size(); ui++)
        {
            if (ui != 0)
            {
                out << ", ";
            }
            out << scheme.at(ui) << "=" << this->at(ui);
        }
        return out.str();
    }

    /**
     * @brief Return a new Scheme which includes only the selected attributes in the given order.
     *
     * @param attributeIndices The indices of the attributes to include.
     * @return Tuple
     */
    Tuple project(std::vector<int> &attributeIndices) const
    {
        std::vector<std::string> values;
        for (unsigned int ui = 0; ui < attributeIndices.size(); ui++) // TODO? Clean up
        {
            int attributeIndex = attributeIndices.at(ui);

            std::string value = this->at(static_cast<unsigned int>(attributeIndex));
            values.push_back(value);
        }
        Tuple projectedTuple(values);
        return projectedTuple;
    }

    /**
     * @brief Return a copy of this Tuple.
     * @return Tuple
     */
    Tuple copy() const
    {
        std::vector<std::string> values;
        for (unsigned int ui = 0; ui < this->size(); ui++)
        {
            std::string value = this->at(ui);
            values.push_back(value);
        }
        Tuple result(values);
        return result;
    }
};

#endif
