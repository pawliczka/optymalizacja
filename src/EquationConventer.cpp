#include "EquationConventer.hpp"
#include "ComparisonOperator.hpp"
#include <boost/algorithm/string.hpp>
#include <boost/lambda/lambda.hpp>
#include <iostream>
#include <algorithm>
#include <regex>

namespace
{
ComparisonOperator convertStringToComparasionOperator(const std::string& expression)
{
    if (expression == "=")
        return ComparisonOperator::Equal;
    if (expression == ">=")
        return ComparisonOperator::GreaterEqual;
    if (expression == "<=")
        return ComparisonOperator::LessEqual;
    if (expression == "<")
        return ComparisonOperator::Less;
    if (expression == ">")
        return ComparisonOperator::Greater;
    return ComparisonOperator::None;
}

std::string returnFoundComparisonOperatorAsString(const std::string& expression)
{
    std::vector<std::string> key={">=","<=",">","<","="};
    for(unsigned index=0;index<key.size();index++)
    {
        if(std::regex_search(expression,std::regex(key[index])))
            return key[index];
    }
    return "";
}
}

Equation EquationConventer::convert(const std::string expression)
{
    Equation equation;
    std::string foundOperator=returnFoundComparisonOperatorAsString(expression);

    equation.setComparisonOperator(convertStringToComparasionOperator(foundOperator));

    std::vector<std::string> splitedExpresionByCompOperator{};

    boost::iter_split(splitedExpresionByCompOperator, expression, boost::first_finder(foundOperator));
    boost::replace_all(splitedExpresionByCompOperator[0], "-", "+-");
    std::vector<std::string> splitedExpresionIntoTerms{};
    boost::split(splitedExpresionIntoTerms, splitedExpresionByCompOperator[0], boost::is_any_of("+"));
    std::for_each(splitedExpresionIntoTerms.begin(), splitedExpresionIntoTerms.end(),
        [this, &equation](auto& expresion1) { equation.setCoefficient(m_termConverter->convert(expresion1)); });
    return std::move(equation);
}
