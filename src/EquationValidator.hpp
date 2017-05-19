#pragma once
#include "Equation.hpp"
#include <regex>

class EquationValidator
{
public:
    static bool isObjFunValid(const std::string& objFun);
    static bool isConstraintsValid(const std::string &constraints);

private:
    const static std::regex m_objectiveFunctionPattern;
    const static std::regex m_contructionPattern;
};
