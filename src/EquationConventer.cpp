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
    boost::replace_all(splitedExpresionByCompOperator[1], "-", "+-");


    std::vector<std::string> splitedExpresionIntoTermsLeftSide{};
    std::vector<std::string> splitedExpresionIntoTermsRightSide{};

    boost::split(splitedExpresionIntoTermsLeftSide, splitedExpresionByCompOperator[0], boost::is_any_of("+"));
    boost::split(splitedExpresionIntoTermsRightSide, splitedExpresionByCompOperator[1], boost::is_any_of("+"));

    if(splitedExpresionIntoTermsRightSide.size()==2)
    std::cout<<splitedExpresionIntoTermsRightSide[1]<<std::endl;

    std::for_each(splitedExpresionIntoTermsLeftSide.begin(), splitedExpresionIntoTermsLeftSide.end(),
        [this, &equation](auto& expresion1) {
        equation.setCoefficient(m_termConverter->convert(expresion1)); });

    std::for_each(splitedExpresionIntoTermsRightSide.begin(), splitedExpresionIntoTermsRightSide.end(),
        [this, &equation](auto& expresion1) {
        Term term=m_termConverter->convert(expresion1);
        term.first=term.first*(-1);
        equation.setCoefficient(term);});

    return std::move(equation);
}
