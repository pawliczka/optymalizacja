#include "EquationConventer.hpp"
#include "ComparisonOperator.hpp"
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <boost/lambda/lambda.hpp>
#include <iostream>
#include <regex>

namespace
{
std::string returnFoundComparisonOperatorAsString(const std::string & expression)
{
    std::vector<std::string> key = {">=", "<=", ">", "<", "="};
    for (unsigned index = 0; index < key.size(); index++)
    {
        if (std::regex_search(expression, std::regex(key[index])))
            return key[index];
    }
    return "";
}
}

Equation EquationConventer::convert(const std::string expression)
{

    Equation equation;
    std::string foundOperator = returnFoundComparisonOperatorAsString(expression);
    equation.setComparisonOperator(foundOperator);

    std::vector<std::string> splitedExpresionByCompOperator{};

    boost::iter_split(splitedExpresionByCompOperator, expression, boost::first_finder(foundOperator));
    boost::replace_all(splitedExpresionByCompOperator[0], "-", "+-");
    boost::replace_all(splitedExpresionByCompOperator[1], "-", "+-");

    std::vector<std::string> splitedExpresionIntoTermsLeftSide{};
    std::vector<std::string> splitedExpresionIntoTermsRightSide{};

    boost::split(splitedExpresionIntoTermsLeftSide, splitedExpresionByCompOperator[0], boost::is_any_of("+"));
    boost::split(splitedExpresionIntoTermsRightSide, splitedExpresionByCompOperator[1], boost::is_any_of("+"));

    std::for_each(
        splitedExpresionIntoTermsLeftSide.begin(), splitedExpresionIntoTermsLeftSide.end(),
        [this, &equation](auto & expression) { equation.setCoefficient(m_termConverter->convert(expression)); });

    std::for_each(
        splitedExpresionIntoTermsRightSide.begin(), splitedExpresionIntoTermsRightSide.end(),
        [this, &equation](auto & expression) {
            if (expression == "")
                return;
            Term term = m_termConverter->convert(expression);
            term.first = term.first * (-1);
            equation.setCoefficient(term);
        });

    return equation;
}
