#pragma once
#include "EquationConventer.hpp"
#include <memory>

class EquationManager
{
public:
    EquationManager(std::shared_ptr<IEquationConventer> p_eqationConverter)
        : m_eqationConverter(p_eqationConverter)
    {
    }
    void convertToEquations();

private:
    std::shared_ptr<IEquationConventer> m_eqationConverter;
};
