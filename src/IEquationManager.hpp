#pragma once
#include <string>

class IEquationManager
{
    virtual void convertToEquations(std::string) = 0;
    virtual std::string convertEquationsToString() const = 0;
};
