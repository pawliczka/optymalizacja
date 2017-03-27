#include "EquationConventer.hpp"

int EquationConventer::convert(const std::string expresion )
{
    return m_termConverter->convert(expresion).first;
}
