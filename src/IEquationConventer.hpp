#pragma once
#include <string>

class IEquationConventer
{
public:
    virtual int convert( const std::string expresion ) = 0;
};
