#pragma once
#include "IEquationConventer.hpp"

class EquationConventer : public IEquationConventer
{
public:
    int convert( const std::string& expresion ) override;
};
