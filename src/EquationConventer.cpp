#include "EquationConventer.hpp"
#include "ComparisonOperator.hpp"
#include <boost/algorithm/string.hpp>
#include <boost/lambda/lambda.hpp>
#include <iostream>
#include <algorithm>

namespace
{
    ComparisonOperator convertStringToComparasionOperator(const std::string& expresion)
    {
        if(expresion == "=")
            return ComparisonOperator::Equal;
        if(expresion == ">=")
            return ComparisonOperator::GreaterEqual;
        if(expresion == "<=")
            return ComparisonOperator::LessEqual;
        if(expresion == "<")
            return ComparisonOperator::Less;
        if(expresion == ">")
            return ComparisonOperator::Greater;
        return ComparisonOperator::None;
    }
}

Equation EquationConventer::convert(const std::string expresion )
{
    std::vector<std::string> splitedExpresion {};
    boost::iter_split(splitedExpresion, expresion, boost::first_finder(">="));
    boost::replace_all(splitedExpresion[0],"-","+-");
    std::vector<std::string> splitedExpresion1 {};
    boost::split(splitedExpresion1,splitedExpresion[0],boost::is_any_of("+"));
    std::for_each(splitedExpresion1.begin(),splitedExpresion1.end(),[this](auto& expresion1)
    {
       m_termConverter->convert(expresion1);
    });
    return Equation();
}
