#include "EquationValidator.hpp"
#include <boost/algorithm/string.hpp>
#include <QDebug>

bool EquationValidator::isObjFunValid(const std::string& objFun)
{
    return std::regex_match(objFun, m_objectiveFunctionPattern);
}

bool EquationValidator::isConstraintsValid(const std::string& constraints)
{
    std::vector<std::string> result;
    boost::split(result, constraints, boost::is_any_of("\n"));
    for (const auto& equation : result)
    {
        if (equation == "")
            continue;
        if (!std::regex_match(equation, m_contructionPattern))
        {
            return false;
        }
    }
    return true;
}

const std::regex EquationValidator::m_contructionPattern =
    std::regex("(?:[+-]?[\\d\\.]*x[1-9][\\d\\.]*|[+-]?\\d+)(?:[+-][\\d\\.]*x[1-9][\\d\\.]*|[+-]\\d+)*(?:<=|>=)(?:[+-]?["
               "\\d\\.]*x[1-9][\\d\\.]*|[+-]?[\\d\\.]+)(?:[+-][\\d\\.]*x[1-9][\\d\\.]*|[+-][\\d\\.]+)*");

const std::regex EquationValidator::m_objectiveFunctionPattern =
    std::regex("[+-]?[\\d\\.]*x[1-9]([\\d\\.]*)(?:[+-][\\d\\.]*x[1-9][\\d\\.]*)*");
