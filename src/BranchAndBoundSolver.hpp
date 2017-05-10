#pragma once
#include "Simplex.hpp"
#include "LinearProblem.hpp"
#include "NodeOfSolution.hpp"

class BranchAndBoundSolver
{
public:
    BranchAndBoundSolver(std::shared_ptr<LinearProblemSolution>);


private:
    std::shared_ptr<LinearProblemSolution> m_initialSolution;
};

