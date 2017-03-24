#include "TermConverter.hpp"
#include <boost/algorithm/string.hpp>
#include <algorithm>
#include <cctype>
#include <boost/lexical_cast.hpp>

TermConverter::TermConverter()
{
}

Term TermConverter::convert( std::string expresion )
{
    m_expresionWithoutWhiteCharacters = removeWhiteCharacters( expresion );
    if ( isEmptyExpresion() )
        return std::make_pair( 0, 0 );
    return splitExpresionToPair();
}

bool TermConverter::isEmptyExpresion()
{
    return m_expresionWithoutWhiteCharacters == "";
}

std::string& TermConverter::removeWhiteCharacters( std::string& expresion )
{
    expresion.erase( std::remove( expresion.begin(), expresion.end(), ' ' ), expresion.end() );
    return expresion;
}

void TermConverter::splitExpresionByX()
{
    boost::split( m_splitedExpresion, m_expresionWithoutWhiteCharacters, boost::is_any_of( "x" ) );
}

Term TermConverter::splitExpresionToPair()
{
    splitExpresionByX();
    if ( isFullyExpresion() )
        return convertFullyExpresion();
    else
        return std::make_pair( boost::lexical_cast< int >( m_splitedExpresion[ 0 ] ), 0 );
}

Term TermConverter::convertFullyExpresion()
{
    if ( isExpresionWithoutCoefficient() )
        return std::make_pair( 1, boost::lexical_cast< int >( m_splitedExpresion[ 1 ] ) );
    else
        return std::make_pair( boost::lexical_cast< int >( m_splitedExpresion[ 0 ] ),
            boost::lexical_cast< int >( m_splitedExpresion[ 1 ] ) );
}

bool TermConverter::isExpresionWithoutCoefficient()
{
    return m_splitedExpresion[ 0 ] == "";
}

bool TermConverter::isFullyExpresion()
{
    return m_splitedExpresion.size() == 2;
}
