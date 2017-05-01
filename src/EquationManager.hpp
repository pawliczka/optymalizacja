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
    const Equation& getConstraintFunction(const int number) const;

private:
    std::shared_ptr<IEquationConventer> m_eqationConverter;
    std::vector<std::shared_ptr<Equation>> m_equationVector;
};
