#pragma once
#include "ComparisonOperator.hpp"
#include <limits>
#include <vector>
#include <string>
#include <ostream>

using Coefficient = float;
using Index = int;
using Term = std::pair<Coefficient, Index>;

class Equation
{
public:
    Equation() {}
    Equation(std::vector<Coefficient> coefficients, ComparisonOperator compOperator)
        : m_coefficients(coefficients)
        , m_comparisonOperator(compOperator)
    {
    }
    friend std::ostream& operator<<(std::ostream& stream, Equation const& equation);
    Coefficient getCoefficient(unsigned int index) const;
    ComparisonOperator getComparisonOperator() const;
    void resizeEquation(int indexOfNewMaxCoefficient);
    void setCoefficient(Term term);
    void setComparisonOperator(ComparisonOperator comparisonOperator);
    void setComparisonOperator(const std::string& comparisonOperator);
    Equation getWithNegativeSign() const;
    int getIndexOfLastCofficient() const;
    bool operator==(const Equation& equationSecond) const;
    std::string toString() const;

private:
    std::string getFirstElementAsString() const;
    std::string getNonFirstElementAsString() const;
    std::string getComparisonOperatorAndZeroAsString() const;
    std::string getTermAsString(int index) const;

    std::vector<Coefficient> m_coefficients;
    ComparisonOperator m_comparisonOperator;
};
