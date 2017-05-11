#pragma once
#include "LinearProblemSolution.hpp"
#include "LinearProblem.hpp"
#include <memory>

struct NodeOfSolution {
    NodeOfSolution(std::shared_ptr<LinearProblem> problem, int id)
        : m_Id(id), m_linearProblem(problem){}
    int m_Id = 0;
    bool isOptimal = false;
    std::shared_ptr<LinearProblemSolution> m_solution;
    std::shared_ptr<NodeOfSolution> m_idLowerBound;
    std::shared_ptr<NodeOfSolution> m_idUpperBound;
    std::shared_ptr<LinearProblem> m_linearProblem;
};

