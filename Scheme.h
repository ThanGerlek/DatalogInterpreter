#ifndef CS236_LAB4_T2K_SCHEME_H
#define CS236_LAB4_T2K_SCHEME_H

#include <vector>
#include <string>
#include <sstream>

// TODO. Standardize variable names and signedness

class Scheme : public std::vector<std::string>
{
public:
    Scheme(){};
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

    unsigned int getAttributeIndex(std::string attribute) const
    {
        for (unsigned int i = 0; i < this->size(); i++)
        {
            if (this->at(i) == attribute)
            {
                return i;
            }
        }
        std::cout << "[ERROR] getAttributeIndex() couldn't find given attribute." << std::endl;
        throw;
    }

    bool hasAttribute(std::string &attribute) const
    {
        for (std::string currentAttribute : *this)
        {
            if (currentAttribute == attribute)
            {
                return true;
            }
        }
        return false;
    }

    /**
     * @brief Return a new Scheme which includes only the selected attributes in the given order.
     *
     * @param u_indices The (unsigned) indices of the attributes to include.
     * @return const Scheme
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

    /**
     * @brief Return a new Scheme with the given attribute renamed.
     *
     * @param oldName The attribute to rename.
     * @param newName The new name.
     * @return const Scheme
     */
    const Scheme rename(std::vector<std::string> &newNames) const
    {
        if (newNames.size() != this->size())
        {
            std::cerr << "[ERROR] Renamed a Scheme to a different size." << std::endl;
            throw;
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
