#include "Equation.hpp"
#include <algorithm>

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
    if (term.second >= m_coefficients.size())
        m_coefficients.resize(term.second + 1, 0);
    m_coefficients[term.second] += term.first;
}

void Equation::setComparisonOperator(ComparisonOperator comparisonOperator)
{
    m_comparisonOperator = comparisonOperator;
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
