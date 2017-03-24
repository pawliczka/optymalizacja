#pragma once
#include <string>
class IEquationConventer
{
public:
    virtual int convert( std::string expresion ) = 0;
};
