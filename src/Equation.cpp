#include "Equation.hpp"
#include <algorithm>
#include <boost/algorithm/string.hpp>

namespace
{
ComparisonOperator convertStringToComparasionOperator(const std::string& expression)
{
    if (expression == "=")
        return ComparisonOperator::Equal;
    if (expression == ">=")
        return ComparisonOperator::GreaterEqual;
    if (expression == "<=")
        return ComparisonOperator::LessEqual;
    if (expression == "<")
        return ComparisonOperator::Less;
    if (expression == ">")
        return ComparisonOperator::Greater;
    return ComparisonOperator::None;
}

std::string convertComparasionOperatorToString(const ComparisonOperator expression)
{
    if (expression == ComparisonOperator::Equal)
        return std::string("=");
    if (expression == ComparisonOperator::Greater)
        return std::string(">");
    if (expression == ComparisonOperator::GreaterEqual)
        return std::string(">=");
    if (expression == ComparisonOperator::Less)
        return std::string("<");
    if (expression == ComparisonOperator::LessEqual)
        return std::string("<=");
    return std::string("");
}
}

std::ostream& operator<<(std::ostream& stream, const Equation& equation)
{
    for (int i = equation.getIndexOfLastCofficient(); i >= 0; i--)
        stream << equation.getCoefficient(i) << "x" << i << " ";
    return stream;
}

int Equation::getCoefficient(unsigned int index) const
{
    if (index < m_coefficients.size())
        return m_coefficients[index];
    else
        return std::numeric_limits<int>::max();
}

ComparisonOperator Equation::getComparisonOperator() const
{
    return m_comparisonOperator;
}

void Equation::setCoefficient(Term term)
{
    if (term.second >= static_cast<int>(m_coefficients.size()))
        m_coefficients.resize(term.second + 1, 0);
    m_coefficients[term.second] += term.first;
}

void Equation::setComparisonOperator(ComparisonOperator comparisonOperator)
{
    m_comparisonOperator = comparisonOperator;
}

void Equation::setComparisonOperator(std::string comparisonOperator)
{
    m_comparisonOperator = convertStringToComparasionOperator(comparisonOperator);
}

int Equation::getIndexOfLastCofficient() const
{
    return m_coefficients.size() - 1;
}

bool Equation::operator==(const Equation& equationSecond) const
{
    if (m_comparisonOperator != equationSecond.getComparisonOperator())
        return false;

    if (!std::equal(m_coefficients.begin(), m_coefficients.end(), equationSecond.m_coefficients.begin()))
        return false;

    return true;
}

std::string Equation::getTermAsString(int index) const
{
    auto coefficient = getCoefficient(index);
    if (coefficient == 0)
    {
        return "";
    }
    std::string equation = "+";
    if (index != 0)
    {
        if (coefficient == 1)
        {
            equation += "x" + std::to_string(index);
        }
        else if (coefficient == -1)
        {
            equation += "-x" + std::to_string(index);
        }
        else
        {
            equation += std::to_string(coefficient) + "x" + std::to_string(index);
        }
    }
    else
    {
        equation += std::to_string(m_coefficients[0]);
    }
    boost::replace_all(equation, "+-", "-");
    return equation;
}

std::string Equation::getNonFirstElementAsString() const
{
    std::string equation = "";
    for (int index = m_coefficients.size() - 2; index >= 0; index--)
    {
        equation += getTermAsString(index);
    }
    return equation;
}

std::string Equation::getFirstElementAsString() const
{
    auto index = getIndexOfLastCofficient();
    auto coefficient = getCoefficient(index);
    if (coefficient == 0)
    {
        return "";
    }
    if (coefficient == 1)
    {
        return "x" + std::to_string(index);
    }
    if (coefficient == -1)
    {
        return "-x" + std::to_string(index);
    }
    return std::to_string(m_coefficients[index]) + "x" + std::to_string(index);
}

std::string Equation::getComparisonOperatorAndZeroAsString() const
{
    return convertComparasionOperatorToString(m_comparisonOperator) + std::string("0");
}

std::string Equation::toString() const
{
    return getFirstElementAsString() + getNonFirstElementAsString() + getComparisonOperatorAndZeroAsString();
}
