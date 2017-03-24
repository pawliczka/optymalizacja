#pragma once
#include "ITermConverter.hpp"
#include <vector>

class TermConverter : public ITermConverter
{
public:
    Term convert( std::string expresion ) override;

private:
    std::string m_expresionWithoutWhiteCharacters;
    std::vector< std::string > m_splitedExpresion;

    std::string& removeWhiteCharacters( std::string& expresion );
    Term splitExpresionToPair();
    Term convertFullyExpresion();
    Term convertWithoutVariable( const std::vector< std::string >& splitedExpresion );
    void splitExpresionByX();
    bool isExpresionWithoutCoefficient();
    bool isFullyExpresion();
};
