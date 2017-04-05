#pragma once
#include "ComparisonOperator.hpp"
#include <limits>
#include <vector>

using Coefficient = int;
using Index = int;
using Term = std::pair<Coefficient, Index>;

class Equation
{
public:
    Equation();
    int getCoefficient(unsigned int index) const;
    ComparisonOperator getComparisonOperator() const;
    void setCoefficient(int value, unsigned int index);
    void setCoefficient(Term term);
    void setComparisonOperator(ComparisonOperator comparisonOperator);
    int getIndexOfLastCofficient();
    bool operator==(const Equation& equationSecond) const;

private:
    std::vector<int> m_coefficients;
    ComparisonOperator m_comparisonOperator;
};
