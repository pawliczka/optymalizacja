#include "NodeOfSolution.hpp"

void NodeOfSolution::setEquation(std::vector<Coefficient> coefficients, ComparisonOperator compOperator)
{
    m_additionalConstrain = Equation(coefficients, compOperator);
}
