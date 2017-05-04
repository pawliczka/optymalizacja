#pragma once
#include <vector>
#include "LinearProblemCase.hpp"

struct LinearProblemSolution
{
    LinearProblemSolution(int _n);
    std::vector<double> VariableValues;
    double ObjFuncValue;
    void print() const;
    LinearProblemCase Case;
};
