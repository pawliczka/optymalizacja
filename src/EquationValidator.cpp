#include "EquationValidator.hpp"

EquationValidator::EquationValidator()
{
}

const std::regex EquationValidator::m_objectiveFunctionPattern =
    std::regex("(?:[+-]?\\d*x[1-9]\\d*|[+-]?\\d+)(?:[+-]\\d*x[1-9]\\d*|[+-]\\d+)*(?:<=|>=)(?:[+-]?\\d*x[1-9]\\d*|[+-]?\\d+)(?:[+"
               "-]\\d*x[1-9]\\d*|[+-]\\d+)*");

const std::regex EquationValidator::m_contructionPattern = std::regex("[+-]?\\d*x[1-9]\\d*(?:[+-]\\d*x[1-9]\\d*)*");
