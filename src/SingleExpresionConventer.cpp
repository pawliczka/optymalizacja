#include "SingleExpresionConventer.hpp"
#include <boost/algorithm/string.hpp>
#include <algorithm>
#include <cctype>
#include <boost/lexical_cast.hpp>

SingleExpresionConventer::SingleExpresionConventer()
{
}

std::pair< int, int > SingleExpresionConventer::convert( std::string& expresion )
{
    auto& expresionWithoutWhiteCharacters = removeWhiteCharacters( expresion );
    if ( expresionWithoutWhiteCharacters == "" )
        return std::make_pair( 0, 0 );
    return splitExpresionToPair( expresionWithoutWhiteCharacters );
}

std::string& SingleExpresionConventer::removeWhiteCharacters( std::string& expresion )
{
    expresion.erase( std::remove( expresion.begin(), expresion.end(), ' ' ), expresion.end() );
    return expresion;
}

std::pair< int, int > SingleExpresionConventer::splitExpresionToPair( std::string& expresion )
{
    std::vector< std::string > splitedExpresion;
    boost::split( splitedExpresion, expresion, boost::is_any_of( "x" ) );
    if ( splitedExpresion.size() == 2 )
    {
        return convertFullyExpansion( splitedExpresion );
    }
    else
        return std::make_pair( boost::lexical_cast< int >( splitedExpresion[ 0 ] ), 0 );
}


std::pair< int, int > SingleExpresionConventer::convertFullyExpansion( std::vector< std::string >& splitedExpresion )
{
    if ( splitedExpresion[ 0 ] == "" )
        return std::make_pair( 1, boost::lexical_cast< int >( splitedExpresion[ 1 ] ) );
    else
        return std::make_pair(
            boost::lexical_cast< int >( splitedExpresion[ 0 ] ), boost::lexical_cast< int >( splitedExpresion[ 1 ] ) );
}

std::pair< int, int > SingleExpresionConventer::convertWithoutVariable( std::vector< std::string >& splitedExpresion )
{
    return std::make_pair( boost::lexical_cast< int >( splitedExpresion[ 0 ] ), 0 );
}
