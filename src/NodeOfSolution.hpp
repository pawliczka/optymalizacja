#pragma once
#include "LinearProblemSolution.hpp"
#include <memory>

class NodeOfSolution {
public:
private:
    int m_Id = {0};
    bool isOptimal = {false};
    std::shared_ptr<LinearProblemSolution> m_solution;
    std::shared_ptr<int> m_idLowerBound;
    std::shared_ptr<int> m_idUpperBound;
};

