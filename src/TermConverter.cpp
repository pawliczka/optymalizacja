#include "TermConverter.hpp"
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

namespace
{
std::string& removeWhiteCharacters(std::string& expresion)
{
    expresion.erase(std::remove(expresion.begin(), expresion.end(), ' '), expresion.end());
    return expresion;
}
bool isExpresionWithoutCoefficient(const std::vector<std::string>& splitedExpresion)
{
    return splitedExpresion.front().empty();
}

bool isTermWithVariable(const std::vector<std::string>& splitedExpresion)
{
    return splitedExpresion.size() == 2;
}
}

Term TermConverter::convert(std::string expresion)
{
    m_expresionWithoutWhiteCharacters = removeWhiteCharacters(expresion);
    if (m_expresionWithoutWhiteCharacters.empty())
        return {};
    splitTermByX();
    return m_splitedExpresion;
}

void TermConverter::splitTermByX()
{
    std::vector<std::string> splitedExpresion{};
    boost::split(splitedExpresion, m_expresionWithoutWhiteCharacters, boost::is_any_of("x"));
    if (isTermWithVariable(splitedExpresion)) /* handle "3x1" */
    {
        if (isExpresionWithoutCoefficient(splitedExpresion)) /* handle "x1" */
        {
            m_splitedExpresion = {1, boost::lexical_cast<int>(splitedExpresion[1])};
            return;
        }
        if (splitedExpresion[0] == "-")
        {
            m_splitedExpresion = {-1, boost::lexical_cast<int>(splitedExpresion[1])};
            return;
        }
        if (splitedExpresion[0] == "+")
        {
            m_splitedExpresion = {1, boost::lexical_cast<int>(splitedExpresion[1])};
            return;
        }
        m_splitedExpresion = {
            boost::lexical_cast<float>(splitedExpresion[0]), boost::lexical_cast<int>(splitedExpresion[1])};
        return;
    }
    m_splitedExpresion = {boost::lexical_cast<float>(splitedExpresion[0]), 0};
}
