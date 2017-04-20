#pragma once
#include "ComparisonOperator.hpp"
#include "IEquation.hpp"
#include <limits>
#include <vector>
#include <string>
#include <ostream>

using Coefficient = int;
using Index = int;
using Term = std::pair<Coefficient, Index>;

class Equation: public IEquation
{
public:
    Equation() {}
    Equation(std::vector<int> coefficients, ComparisonOperator compOperator)
        : m_coefficients(coefficients)
        , m_comparisonOperator(compOperator)
    {
    }
    friend std::ostream& operator<<(std::ostream& stream, Equation const& equation);
    int getCoefficient(unsigned int index) const;
    ComparisonOperator getComparisonOperator() const;
    void setCoefficient(Term term);
    void setComparisonOperator(ComparisonOperator comparisonOperator);
    void setComparisonOperator(std::string comparisonOperator);
    int getIndexOfLastCofficient() const;
    bool operator==(const Equation& equationSecond) const;
    std::string toString();

private:
    std::string getFirstElementAsString();

    std::vector<int> m_coefficients;
    ComparisonOperator m_comparisonOperator;
    std::__cxx11::string getNonFirstElementAsString();
    std::__cxx11::string getComparisonOperatorAndZeroAsString();
};
