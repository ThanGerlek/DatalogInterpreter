#ifndef T2K_236PROJECT_PARAMETER_H
#define T2K_236PROJECT_PARAMETER_H

#include <string>

class Parameter
{
public:
    Parameter(std::string _text, bool _isVariable) : text(_text), isVar(_isVariable){};
    ~Parameter(){};
    bool isVariable() const { return isVar; };
    void setIsVariable(bool _isVar) { isVar = _isVar; }
    std::string toString() const { return getValue(); };
    std::string getValue() const { return text; }

    bool operator==(Parameter const &other)
    {
        return this->text == other.text && this->isVar == other.isVar;
    }

    bool operator!=(Parameter const &other) {
        return !(*this == other);
    }

private:
    std::string text;
    bool isVar;
};

#endif
