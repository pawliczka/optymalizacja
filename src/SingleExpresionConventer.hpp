#pragma once
#include "ISingleExpresionConventer.hpp"
#include <vector>

class SingleExpresionConventer : public ISingleExpresionConventer
{
public:
    SingleExpresionConventer();
    std::pair< int, int > convert( std::string& expresion ) override;

private:
    std::string& removeWhiteCharacters( std::string& expresion );
    std::pair< int, int > splitExpresionToPair( std::string& expresion );
    std::pair< int, int > convertFullyExpansion( std::vector< std::string >& splitedExpresion );
    std::pair< int, int > convertWithoutVariable( std::vector< std::string >& splitedExpresion );
};
