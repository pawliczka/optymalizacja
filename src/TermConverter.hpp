#pragma once
#include "ITermConverter.hpp"
#include <vector>

class TermConverter : public ITermConverter
{
public:
    Term convert( std::string expresion ) override;

private:
    std::string m_expresionWithoutWhiteCharacters;
    Term m_splitedExpresion;

    void splitTermByX();
};
