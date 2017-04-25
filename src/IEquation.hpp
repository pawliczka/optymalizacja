#pragma once
#include "ComparisonOperator.hpp"
#include "ITermConverter.hpp"

class IEquation
{
public:
    virtual int getCoefficient(unsigned int index) const = 0;
    virtual ComparisonOperator getComparisonOperator() const = 0;
    virtual void setCoefficient(Term term) = 0;
    virtual void setComparisonOperator(ComparisonOperator comparisonOperator) = 0;
    virtual int getIndexOfLastCofficient() const = 0;
    virtual std::string toString() const = 0;
};
