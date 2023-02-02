#ifndef T2K_236PROJECT_PREDICATE_H
#define T2K_236PROJECT_PREDICATE_H

#include <string>
#include <vector>
#include "Parameter.h"

// TODO Implement

class Predicate
{
public:
    Predicate(std::string _id) : id(_id){};
    ~Predicate(){};
    void addParam(Parameter param) { params.push_back(param); }
    int numParams() const { return params.size(); }
    Parameter getParam(int index) const { return params.at(index); }
    std::string getId() const { return id; }

    std::string toString() const
    {
        std::string out = id + "(" + params.at(0).toString();
        for (std::vector<Parameter>::const_iterator i = params.begin(); i != params.end(); i++)
        {
            // TODO
        }
        return "";
    }

private:
    std::string id;
    std::vector<Parameter> params;
};

#endif
