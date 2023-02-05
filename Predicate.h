#ifndef T2K_236PROJECT_PREDICATE_H
#define T2K_236PROJECT_PREDICATE_H

#include <string>
#include <vector>
#include "Parameter.h"

class Predicate
{
public:
    Predicate(){};
    Predicate(std::string _id) : id(_id){};
    ~Predicate(){};
    std::string getId() const { return id; } // TODO? Remove
    const std::vector<Parameter> &getParams() const { return params; }
    void addParam(Parameter param) { params.push_back(param); }
    void eraseParam() { params.pop_back(); }

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

private:
    std::string id;
    std::vector<Parameter> params;
};

#endif
