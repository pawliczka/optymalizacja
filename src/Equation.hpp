#pragma once
#include "ComparisonOperator.hpp"
#include <vector>

class Equation
{
public:
    Equation();
    int getCoefficient(int index);
    ComparisonOperator getComparisonOperator();
    void setCoefficient(int value, int index);
    void setComparisonOperator(ComparisonOperator comparisonOperator);
private:
    std::vector<int> m_coefficients;
    ComparisonOperator m_comparisonOperator;
};


