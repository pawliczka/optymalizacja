#pragma once
#include "ISingleExpresionConventer.hpp"
#include <vector>

class SingleExpresionConventer : public ISingleExpresionConventer
{
public:
    SingleExpresionConventer();
    std::pair< int, int > convert( std::__cxx11::string expresion ) override;

private:
    std::string m_expresionWithoutWhiteCharacters;
    std::vector< std::string > m_splitedExpresion;

    std::string& removeWhiteCharacters( std::string& expresion );
    std::pair< int, int > splitExpresionToPair();
    std::pair< int, int > convertFullyExpansion();
    std::pair< int, int > convertWithoutVariable( const std::vector< std::string >& splitedExpresion );
    void splitExpresionByX();
    bool isEmptyExpresion();
    bool isExpresionWithoutCoefficient();
};
