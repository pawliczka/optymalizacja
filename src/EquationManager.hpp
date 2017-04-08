#pragma once
#include "EquationConventer.hpp"
#include "Equation.hpp"
#include <memory>

class EquationManager
{
public:
    EquationManager(std::shared_ptr<IEquationConventer> p_eqationConverter)
        : m_eqationConverter(p_eqationConverter)
    {
    }
    void convertToEquations(std::string equations);

private:
    std::shared_ptr<IEquationConventer> m_eqationConverter;
    std::vector<std::shared_ptr<IEquation>> m_equationVector;
};
