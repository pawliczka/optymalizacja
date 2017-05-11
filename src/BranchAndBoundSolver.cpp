#include "BranchAndBoundSolver.hpp"
#include <cmath>
#include <iostream>

BranchAndBoundSolver::BranchAndBoundSolver(std::shared_ptr<LinearProblem> linearProblem)
{
    m_initialProblem = linearProblem;
    m_numberOfVariables = linearProblem->getn();
    m_nodesOfSolution.push_front(std::make_shared<NodeOfSolution>(linearProblem, 1));
    if(linearProblem->gettype() == OptimizeType::MIN)
        m_valueOfBestObjectiveFunction = std::numeric_limits<float>::max();

    m_valueOfBestObjectiveFunction = std::numeric_limits<float>::lowest();
    m_optimizeType = linearProblem->gettype();

}

std::vector<std::shared_ptr<LinearProblemSolution>> BranchAndBoundSolver::Solve()
{
    Simplex simplex;

    while(!m_nodesOfSolution.empty())
    {
        std::shared_ptr<NodeOfSolution> tempNode = m_nodesOfSolution.front();
        m_nodesOfSolution.pop_front();

        tempNode->m_solution = simplex.Solve(*(tempNode->m_linearProblem.get()));
        tempNode->m_solution->print();

        if(IsSolutionIsInteger(*(tempNode->m_solution.get())))
        {
            std::cout << "Rozwiazanie całkowitoliczbowe > Branch Not needed"<<std::endl;
            InsertSolutionIsBetter(tempNode);
        }
    }
    return m_optimalSolutions;
}

bool BranchAndBoundSolver::IsSolutionIsInteger(const LinearProblemSolution &solution) const
{
    double FractionalPart;
    double IntegerPart;

    for (auto const &elem : solution.VariableValues)
    {
        FractionalPart = std::modf(elem,&IntegerPart);
        if( FractionalPart > m_precision && FractionalPart < (1-m_precision) ) return false;
    }

    return true;
}

void BranchAndBoundSolver::InsertSolutionIsBetter(std::shared_ptr<NodeOfSolution> node)
{
    if(((m_optimizeType == OptimizeType::MAX) && (m_valueOfBestObjectiveFunction < node->m_solution->ObjFuncValue)) ||
       ((m_optimizeType == OptimizeType::MIN) && (m_valueOfBestObjectiveFunction > node->m_solution->ObjFuncValue)))
    {
        m_optimalSolutions.clear();
        m_valueOfBestObjectiveFunction = node->m_solution->ObjFuncValue;
        m_optimalSolutions.push_back(node->m_solution);
    }

    if(m_valueOfBestObjectiveFunction == node->m_solution->ObjFuncValue)
        m_optimalSolutions.push_back(node->m_solution);
}

