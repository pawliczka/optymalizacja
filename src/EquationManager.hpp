#pragma once
#include "Equation.hpp"
#include "EquationConventer.hpp"
#include "IEquationManager.hpp"
#include <memory>

class EquationManager : public IEquationManager
{
public:
    EquationManager(std::shared_ptr<IEquationConventer> p_eqationConverter = std::make_shared<EquationConventer>())
        : m_eqationConverter(p_eqationConverter)
    {
    }
    void convertToEquations(std::string equations);
    std::string convertEquationsToString() const;
    const Equation& getObjectiveFunction() const;
    const std::vector<Equation> &getConstraintFunctions() const;

private:
    std::shared_ptr<IEquationConventer> m_eqationConverter;
    Equation m_objFun;
    std::vector<Equation> m_constraintsVector;
};
