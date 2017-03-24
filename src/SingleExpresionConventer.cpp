#include "SingleExpresionConventer.hpp"
#include <boost/algorithm/string.hpp>
#include <algorithm>
#include <cctype>
#include <boost/lexical_cast.hpp>

SingleExpresionConventer::SingleExpresionConventer()
{
}

std::pair< int, int > SingleExpresionConventer::convert( std::string expresion )
{
    m_expresionWithoutWhiteCharacters = removeWhiteCharacters( expresion );
    if ( isEmptyExpresion() )
        return std::make_pair( 0, 0 );
    return splitExpresionToPair();
}

bool SingleExpresionConventer::isEmptyExpresion()
{
    return m_expresionWithoutWhiteCharacters == "";
}

std::string& SingleExpresionConventer::removeWhiteCharacters( std::string& expresion )
{
    expresion.erase( std::remove( expresion.begin(), expresion.end(), ' ' ), expresion.end() );
    return expresion;
}

void SingleExpresionConventer::splitExpresionByX()
{
    boost::split( m_splitedExpresion, m_expresionWithoutWhiteCharacters, boost::is_any_of( "x" ) );
}

std::pair< int, int > SingleExpresionConventer::splitExpresionToPair()
{
    splitExpresionByX();
    if ( m_splitedExpresion.size() == 2 )
        return convertFullyExpresion();
    else
        return std::make_pair( boost::lexical_cast< int >( m_splitedExpresion[ 0 ] ), 0 );
}

std::pair< int, int > SingleExpresionConventer::convertFullyExpresion()
{
    if ( isExpresionWithoutCoefficient() )
        return std::make_pair( 1, boost::lexical_cast< int >( m_splitedExpresion[ 1 ] ) );
    else
        return std::make_pair( boost::lexical_cast< int >( m_splitedExpresion[ 0 ] ),
            boost::lexical_cast< int >( m_splitedExpresion[ 1 ] ) );
}

bool SingleExpresionConventer::isExpresionWithoutCoefficient()
{
    return m_splitedExpresion[ 0 ] == "";
}
