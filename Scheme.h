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
     * @param u_indices The (unsigned) indices of the attributes to include.
     * @return Scheme
     */
    const Scheme project(const std::vector<unsigned int> &u_indices) const
    {
        std::vector<std::string> names;
        for (unsigned int u_index : u_indices)
        {
            std::string name = this->at(u_index);
            names.push_back(name);
        }
        Scheme projectedScheme(names);
        return projectedScheme;
    }

    const Scheme rename(unsigned int u_index, const std::string &newName) const
    {
        std::vector<std::string> names;
        for (unsigned int ui = 0; ui < this->size(); ui++)
        {
            if (ui == u_index)
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
