#pragma once
#include <vector>
#include "LinearProblemCase.hpp"
#include <QDebug>

struct LinearProblemSolution
{
    LinearProblemSolution(int _n);
    std::vector<double> VariableValues;
    double ObjFuncValue;
    LinearProblemCase Case;
    QString getAsString() const;
};
