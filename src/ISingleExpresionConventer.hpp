#pragma once
#include <utility>
#include <string>

class ISingleExpresionConventer
{
    virtual std::pair< int, int > convert( std::string expresion ) = 0;
};
