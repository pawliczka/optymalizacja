#pragma once
#include "ISingleExpresionConventer.hpp"

class SingleExpresionConventer : public ISingleExpresionConventer
{
public:
    SingleExpresionConventer();
    std::pair< int, int > convert( std::string& expresion ) override;

private:
    std::string& removeWhiteCharacters( std::string& expresion );
    std::pair<int, int> splitExpresionToPair(std::string &expresion);
};
