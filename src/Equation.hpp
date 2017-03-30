#pragma once
#include "ComparisonOperator.hpp"
#include <vector>

class Equation
{
public:
    Equation();
private:
    std::vector<int> m_coefficients;
    ComparisonOperator m_comparisonOperator;
};


