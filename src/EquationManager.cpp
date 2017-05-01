#include "EquationManager.hpp"
#include <boost/algorithm/string.hpp>

void EquationManager::convertToEquations(std::string equations)
{
    m_constraintsVector.clear();
    std::vector<std::string> result;
    boost::split(result, equations, boost::is_any_of("\n"));
    bool isObjFunConv = false;
    for (const auto& equation : result)
    {
        if (equation == "")
            continue;
        auto conv = m_eqationConverter->convert(equation);
        if (!isObjFunConv)
        {
            m_objFun = conv;
            isObjFunConv = true;
            continue;
        }
        m_constraintsVector.push_back(conv);
    }
}

std::string EquationManager::convertEquationsToString() const
{
    std::string expresionStr = (m_objFun.toString() + "\n");
    std::for_each(m_constraintsVector.begin(), m_constraintsVector.end(),
        [&expresionStr](const auto& expresion) { expresionStr += (expresion.toString() + "\n"); });
    return expresionStr;
}

const Equation& EquationManager::getObjectiveFunction() const
{
    return m_objFun;
}

const std::vector<Equation>& EquationManager::getConstraintFunctions() const
{
    return m_constraintsVector;
}
