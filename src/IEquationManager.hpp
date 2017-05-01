#pragma once
#include <string>
#include <Equation.hpp>

class IEquationManager
{
    virtual void convertToEquations(std::string) = 0;
    virtual std::string convertEquationsToString() const = 0;
    virtual const Equation & getObjectiveFunction() const = 0;
    virtual const std::vector<Equation>& getConstraintFunctions() const = 0;
};
