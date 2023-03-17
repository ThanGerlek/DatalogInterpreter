#ifndef T2K_236PROJECT_PREDICATE_H
#define T2K_236PROJECT_PREDICATE_H

#include <string>
#include <vector>
#include "Parameter.h"

class Predicate
{
private:
    std::string id;
    std::vector<Parameter> params;

public:
    Predicate(std::string _id) : id(_id){};
    ~Predicate(){};

    void addParam(Parameter param) { params.push_back(param); }
    std::string getId() const { return id; }

    /**
     * @brief Get a pointer to the Params object.
     *
     * @return std::vector<Parameter>*
     */
    std::vector<Parameter> *getParams()
    {
        return &params;
    }

    /**
     * @brief Get the Param object with Parameters converted to strings.
     *
     * @return std::vector<std::string>
     */
    std::vector<std::string> getParamStrings() const
    {
        std::vector<std::string> strs;
        for (Parameter param : params)
        {
            strs.push_back(param.toString());
        }
        return strs;
    }

    std::string toString() const
    {
        if (params.size() == 0)
        {
            return id + "()";
        }

        std::string out = id + "(" + params.at(0).toString();
        std::vector<Parameter>::const_iterator i = params.begin();
        for (i++; i != params.end(); i++)
        {
            out += "," + i->toString();
        }
        return out + ")";
    }
};

#endif
