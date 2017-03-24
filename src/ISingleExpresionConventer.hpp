#pragma once
#include <utility>
#include <string>

class ISingleExpresionConventer
{
    virtual std::pair< int, int > convert( const std::string& expresion ) = 0;
};
