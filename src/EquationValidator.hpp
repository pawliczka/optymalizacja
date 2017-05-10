#pragma once
#include <regex>

class EquationValidator
{
public:
    EquationValidator();

private:
    const static std::regex m_objectiveFunctionPattern;
    const static std::regex m_contructionPattern;
};
