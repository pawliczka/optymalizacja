#pragma once
#include "IEquationManager.hpp"
#include <gmock/gmock.h>

class EquationManagerMock : public IEquationManager
{
public:
    MOCK_METHOD1(convertToEquations, void(std::string));
    MOCK_CONST_METHOD0(convertEquationsToString, std::string());
    MOCK_CONST_METHOD1(getObjectiveFunction, const Equation &());
    MOCK_CONST_METHOD1(getConstraintFunction, const Equation &(const int));
};
