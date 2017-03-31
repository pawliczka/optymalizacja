#include "Equation.hpp"

Equation::Equation()
{

}

int Equation::getCoefficient(unsigned int index)
{
    if(index<m_coefficients.size())
        return m_coefficients[index];
    else
        return std::numeric_limits<int>::max();
}

ComparisonOperator Equation::getComparisonOperator()
{
    return m_comparisonOperator;
}

void Equation::setCoefficient(int value, unsigned int index)
{
    if (index >= m_coefficients.size())
        m_coefficients.resize(index+1);
    m_coefficients[index]=value;
}

void Equation::setComparisonOperator(ComparisonOperator comparisonOperator)
{
    m_comparisonOperator=comparisonOperator;
}

