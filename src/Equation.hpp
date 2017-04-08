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
    Equation() {}
    Equation(std::vector<int> coefficients, ComparisonOperator compOperator)
        : m_coefficients(coefficients)
        , m_comparisonOperator(compOperator)
    {
    }

    int getCoefficient(unsigned int index) const;
    ComparisonOperator getComparisonOperator() const;
    void setCoefficient(Term term);
    void setComparisonOperator(ComparisonOperator comparisonOperator);
    int getIndexOfLastCofficient() const;
    bool operator==(const Equation& equationSecond) const;

private:
    std::vector<int> m_coefficients;
    ComparisonOperator m_comparisonOperator;
};
