#pragma once
#include "Simplex.hpp"
#include "LinearProblem.hpp"
#include "NodeOfSolution.hpp"
#include "LinearProblemSolution.hpp"
#include "Equation.hpp"
#include <vector>
#include <list>
#include <limits>

class BranchAndBoundSolver
{
public:
    BranchAndBoundSolver(std::shared_ptr<LinearProblem>);
    std::vector<std::shared_ptr<LinearProblemSolution>> Solve();
    std::shared_ptr<NodeOfSolution> GetRoot();

private:
    bool IsSolutionIsInteger(const LinearProblemSolution &solution) const;
    void InsertSolutionIsBetter(std::shared_ptr<NodeOfSolution>);
    int getIndexOfFirstNonInteger(const LinearProblemSolution &solution) const;
    void Branch(std::shared_ptr<LinearProblem> tempProblem, std::shared_ptr<NodeOfSolution> tempNode);
    void SingleBranch(std::shared_ptr<NodeOfSolution>, std::shared_ptr<LinearProblem>, ComparisonOperator);


    std::vector<std::shared_ptr<LinearProblemSolution>> m_optimalSolutions;
    std::shared_ptr<LinearProblem> m_initialProblem;
    std::list<std::shared_ptr<NodeOfSolution>> m_nodesOfSolution;
    int m_numberOfVariables = 0;
    float m_precision = 0;
    float m_valueOfBestObjectiveFunction = 0;

    Equation m_newConstrain;
    OptimizeType m_optimizeType = OptimizeType::MAX;

    std::shared_ptr<NodeOfSolution> m_rootNode;
};

