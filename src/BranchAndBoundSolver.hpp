#pragma once
#include "Simplex.hpp"
#include "LinearProblem.hpp"
#include "NodeOfSolution.hpp"
#include "LinearProblemSolution.hpp"
#include <vector>
#include <list>
#include <limits>

class BranchAndBoundSolver
{
public:
    BranchAndBoundSolver(std::shared_ptr<LinearProblem>);
    std::vector<std::shared_ptr<LinearProblemSolution>> Solve();


private:
    bool IsSolutionIsInteger(const LinearProblemSolution &solution) const;
    void InsertSolutionIsBetter(std::shared_ptr<NodeOfSolution>);

    std::vector<std::shared_ptr<LinearProblemSolution>> m_optimalSolutions;
    std::shared_ptr<LinearProblem> m_initialProblem;
    std::list<std::shared_ptr<NodeOfSolution>> m_nodesOfSolution;
    int m_numberOfVariables = 0;
    float m_precision = 0;
    float m_valueOfBestObjectiveFunction = 0;

    OptimizeType m_optimizeType = OptimizeType::MAX;
};

