#pragma once
#include "SimplexTable.hpp";
#include "Equation.hpp"
#include <vector>

class SimplexSolver
{
public:
    SimplexSolver(std::vector<Equation>);
    void ExecutePrimalSimplexMethod();

    SimplexTable simplexTable;
private:

};
