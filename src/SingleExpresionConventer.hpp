#pragma once
#include "ISingleExpresionConventer.hpp"

class SingleExpresionConventer : public ISingleExpresionConventer
{
public:
    SingleExpresionConventer();
    std::pair< int, int > convert( std::string expresion ) override;
};
