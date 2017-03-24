#pragma once
#include "ISingleExpresionConventer.hpp"

class SingleExpresionConventer : public ISingleExpresionConventer
{
public:
    SingleExpresionConventer();
    std::pair< int, int > convert( const std::string& expresion ) override;
};
