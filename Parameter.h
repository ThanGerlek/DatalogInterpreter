#ifndef T2K_236PROJECT_PARAMETER_H
#define T2K_236PROJECT_PARAMETER_H

#include <string>

// TODO Implement

class Parameter
{
public:
    Parameter(std::string _text, bool _isVariable) : text(_text), isVar(_isVariable){};
    ~Parameter(){};
    bool isVariable() const { return isVar; };
    std::string toString() const { return text; };

private:
    std::string text;
    bool isVar;
};

#endif
