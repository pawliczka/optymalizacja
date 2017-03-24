#pragma once
#include "IEquationConventer.hpp"

class EquationConventer: public IEquationConventer
{
public:
    int convert() override;
};
