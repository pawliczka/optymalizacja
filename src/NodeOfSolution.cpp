#include "NodeOfSolution.hpp"
#include <iostream>

void NodeOfSolution::setEquation(std::vector<Coefficient> coefficients, ComparisonOperator compOperator)
{
    m_additionalConstrain = Equation(coefficients, compOperator);
}

void NodeOfSolution::print() const
{
    std::cout << "Node ID:  " << m_Id << std::endl;
    std::cout << "Solution in Node:  " << std::endl;
    int i = 1;
    for (auto elem : m_solution->VariableValues)
    {
        std::cout << "x" << i << " = " << elem << "     ";
        i++;
    }
    std::cout << std::endl;
    std::cout << "Node ObjFunValue:  " << m_solution->ObjFuncValue << std::endl;

}
