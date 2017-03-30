#pragma once
#include "IEquationConventer.hpp"
#include "ITermConverter.hpp"
#include <memory>

class EquationConventer : public IEquationConventer
{
public:
    EquationConventer(std::shared_ptr<ITermConverter> _termConverter) :
        m_termConverter(_termConverter)
    {}
    Equation convert( const std::string expresion ) override;

private:
    std::shared_ptr<ITermConverter> m_termConverter;
};
