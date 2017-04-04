#pragma once
#include "ComparisonOperator.hpp"
#include <limits>
#include <vector>


class Equation
{
public:
    Equation();
    int getCoefficient(unsigned int index) const;
    ComparisonOperator getComparisonOperator() const;
    void setCoefficient(int value, unsigned int index);
    void setComparisonOperator(ComparisonOperator comparisonOperator);
    int getIndexOfLastCofficient();
    bool operator==(const Equation& equationSecond) const;

private:
    std::vector<int> m_coefficients;
    ComparisonOperator m_comparisonOperator;
};
