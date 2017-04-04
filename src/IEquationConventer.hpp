#pragma once
#include <string>
#include "Equation.hpp"


class IEquationConventer
{
public:
    virtual Equation convert(const std::string expresion) = 0;
};
