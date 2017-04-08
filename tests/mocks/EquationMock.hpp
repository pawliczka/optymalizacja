#pragma once
#include "IEquation.hpp"
#include <gmock/gmock.h>

class EquationMock: public IEquation
{
public:
    MOCK_CONST_METHOD1(getCoefficient, int(unsigned int));
    MOCK_CONST_METHOD0(getComparisonOperator, ComparisonOperator());
    MOCK_METHOD1(setCoefficient, void(Term));
    MOCK_METHOD1(setComparisonOperator, void(ComparisonOperator));
    MOCK_METHOD0(getIndexOfLastCofficient, int());
};
