#pragma once
#include "LinearProblemSolution.hpp"
#include "LinearProblem.hpp"
#include "Equation.hpp"
#include <memory>

class NodeOfSolution {
public:
    NodeOfSolution(std::shared_ptr<LinearProblem> problem, long long int id, Equation constrain)
        : m_linearProblem(problem), m_Id(id){m_additionalConstrain = constrain;}

    void setEquation(std::vector<Coefficient> coefficients, ComparisonOperator compOperator); //chyba do wyjebania
    void print() const;

    std::shared_ptr<LinearProblem> m_linearProblem;
    long long int m_Id = 0;
    bool isOptimal = false;
    std::shared_ptr<LinearProblemSolution> m_solution;
    std::shared_ptr<NodeOfSolution> m_lowerBoundNode;
    std::shared_ptr<NodeOfSolution> m_upperBoundNode;
    Equation m_additionalConstrain;


};

