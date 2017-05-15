#pragma once
#include "LinearProblemSolution.hpp"
#include "LinearProblem.hpp"
#include "Equation.hpp"
#include <memory>

enum class StateOfNode
{
    None,
    OptimalSolution,
    CutOff,
};

class NodeOfSolution
{
public:
    NodeOfSolution(std::shared_ptr<LinearProblem> problem, long long int id, Equation constrain)
        : m_linearProblem(problem)
        , m_Id(id)
    {
        m_additionalConstrain = constrain;
    }

    void setEquation(std::vector<Coefficient> coefficients, ComparisonOperator compOperator); // chyba do wyjebania
    void print() const;

    std::shared_ptr<LinearProblem> m_linearProblem;
    long long int m_Id = 0;
    StateOfNode m_state = StateOfNode::None;
    std::shared_ptr<LinearProblemSolution> m_solution;
    std::shared_ptr<NodeOfSolution> m_lowerBoundNode = nullptr;
    std::shared_ptr<NodeOfSolution> m_upperBoundNode = nullptr;
    Equation m_additionalConstrain;
};
