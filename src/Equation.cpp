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

int Equation::getIndexOfLastCofficient()
{
    return m_coefficients.size()-1;
}

bool Equation::operator== (Equation equationSecond) const
{
    if (m_comparisonOperator == equationSecond.getComparisonOperator())
    {
        bool isTheSame = true;
        if ((m_coefficients.size()-1) == equationSecond.getIndexOfLastCofficient())
        {
            unsigned int index = 0;
            while(isTheSame && (index < m_coefficients.size()))
            {
                if(m_coefficients[index] != equationSecond.getCoefficient(index))
                    isTheSame=false;
                index++;
            }
        }
        return isTheSame;
    }
    else
        return false;
}

