#ifndef T2K_236PROJECT_PREDICATE_H
#define T2K_236PROJECT_PREDICATE_H

#include <string>
#include <vector>
#include "Parameter.h"

class Predicate
{
public:
    Predicate(std::string _id) : id(_id){};
    ~Predicate(){};
    void addParam(Parameter param);
    std::string getId() const;
    Parameter getParam(int index) const;

private:
    std::string id;
    std::vector<Parameter> params;
};

#endif
