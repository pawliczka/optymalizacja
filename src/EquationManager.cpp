#include "EquationManager.hpp"
#include <boost/algorithm/string.hpp>

void EquationManager::convertToEquations(std::string equations)
{
    std::vector<std::string> result;
    boost::split(result, equations, boost::is_any_of("\n"));
    for (const auto & equation : result)
    {
        if (equation == "")
            continue;
        auto conv = m_eqationConverter->convert(equation);
        m_equationVector.push_back(std::make_shared<Equation>(conv));
    }
}

std::string EquationManager::convertEquationsToString() const
{
    std::string expresionStr = "";
    std::for_each(m_equationVector.begin(), m_equationVector.end(), [&expresionStr](const auto & expresion) {
        expresionStr += (expresion->toString() + " ");
    });
    return expresionStr;
}
