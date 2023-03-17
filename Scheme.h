#ifndef CS236_LAB4_T2K_SCHEME_H
#define CS236_LAB4_T2K_SCHEME_H

#include <vector>
#include <string>
#include <sstream>

class Scheme : public std::vector<std::string>
{
public:
    Scheme(vector<std::string> attributeNames) : vector<std::string>(attributeNames)
    {
        checkForDuplicateNames();
    };

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

    const Scheme rename(const std::string &oldName, const std::string &newName) const
    {
        std::vector<std::string> newNames;
        for (std::string name : *this)
        {
            if (name == newName)
            {
                std::cerr << "[ERROR] Tried to rename an attribute to an already existing name." << std::endl;
                throw;
            }
            else if (name == oldName)
            {
                newNames.push_back(newName);
            }
            else
            {
                newNames.push_back(name);
            }
        }
        Scheme renamedScheme(newNames);
        return renamedScheme;
    }

private:
    /**
     * @brief Throw an error if this Scheme contains duplicate attribute names.
     */
    void checkForDuplicateNames()
    {
        std::set<std::string> nameSet;
        for (std::string name : *this)
        {
            nameSet.insert(name);
        }
        if (nameSet.size() != this->size())
        {
            std::cerr << "[ERROR] Created Scheme with duplicate attribute names." << std::endl;
            throw;
        }
    }
};

#endif
