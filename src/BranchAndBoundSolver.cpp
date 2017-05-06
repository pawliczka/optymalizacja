#include "BranchAndBoundSolver.hpp"

BranchAndBoundSolver::BranchAndBoundSolver(std::shared_ptr<LinearProblemSolution> solution)
{
    m_initialSolution = solution;
}

