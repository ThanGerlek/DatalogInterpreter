#ifndef CS236_LAB4_T2K_SCHEME_H
#define CS236_LAB4_T2K_SCHEME_H

#include <vector>
#include <string>
#include <sstream>

class Scheme : public std::vector<std::string>
{
public:
    Scheme(){};
    Scheme(vector<std::string> attributeNames) : vector<std::string>(attributeNames)
    {
        checkForDuplicateAttributes();
    };

    std::string toString()
    {
        std::string out = "( ";
        for (std::string attribute : *this)
        {
            out += attribute + " ";
        }
        return out + ")";
    }

    unsigned int getAttributeIndex(std::string &attribute) const
    {
        for (unsigned int i = 0; i < this->size(); i++)
        {
            if (this->at(i) == attribute)
            {
                return i;
            }
        }
        std::cerr << "[ERROR] Called getAttributeIndex() on an attribute not in the Scheme." << std::endl;
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
     * @param indices The indices of the attributes to include.
     * @return const Scheme
     */
    const Scheme project(const std::vector<unsigned int> &indices) const
    {
        std::vector<std::string> attributeNames;
        for (unsigned int index : indices)
        {
            std::string attribute = this->at(index);
            attributeNames.push_back(attribute);
        }
        Scheme projectedScheme(attributeNames);
        return projectedScheme;
    }

    /**
     * @brief Return a new Scheme with the attributes renamed.
     *
     * @param newAttributeNames
     * @return const Scheme
     */
    const Scheme rename(std::vector<std::string> &newAttributeNames) const
    {
        if (newAttributeNames.size() != this->size())
        {
            std::cerr << "[ERROR] Renamed a Scheme to a different size." << std::endl;
            throw;
        }
        Scheme renamedScheme(newAttributeNames);
        return renamedScheme;
    }

private:
    /**
     * @brief Throw an error if this Scheme contains duplicate attribute names.
     */
    void checkForDuplicateAttributes()
    {
        std::set<std::string> attributeSet;
        for (std::string attribute : *this)
        {
            attributeSet.insert(attribute);
        }
        if (attributeSet.size() != this->size())
        {
            std::cerr << "[ERROR] Created Scheme with duplicate attribute names." << std::endl;
            throw;
        }
    }
};

#endif
