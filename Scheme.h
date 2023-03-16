#ifndef CS236_LAB4_T2K_SCHEME_H
#define CS236_LAB4_T2K_SCHEME_H

#include <vector>
#include <string>
#include <sstream>

class Scheme : public std::vector<std::string>
{
public:
    Scheme(vector<std::string> attributeNames) : vector<std::string>(attributeNames){};

    std::string toString()
    {
        std::stringstream out;
        out << "( ";
        for (std::string name : *this)
        {
            out << name << " ";
        }
        out << ")";
        return out.str();
    }

    /**
     * @brief Return a new Scheme which includes only the selected attributes in the given order.
     *
     * @param attributeIndices The indices of the attributes to include.
     * @return Scheme
     */
    Scheme project(std::vector<int> &indices) const
    {
        std::vector<std::string> names;
        for (int index : indices)
        {
            std::string name = this->at(static_cast<unsigned int>(index));
            names.push_back(name);
        }
        Scheme projectedScheme(names);
        return projectedScheme;
    }

    Scheme rename(int index, const std::string &newName) const
    {
        std::vector<std::string> names;
        for (unsigned int ui = 0; ui < this->size(); ui++)
        {
            if (static_cast<int>(ui) == index)
            {
                names.push_back(newName);
            }
            else
            {
                names.push_back(this->at(ui));
            }
        }
        Scheme renamedScheme(names);
        return renamedScheme;
    }
};

#endif
