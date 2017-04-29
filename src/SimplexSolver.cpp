#include "SimplexSolver.hpp"

SimplexSolver::SimplexSolver(std::vector<Equation> p_equations)
{
    simplexTable = SimplexTable(p_equations);
}

void SimplexSolver::ExecutePrimalSimplexMethod()
{
    simplexTable.ExecuteSimplexMethod();
}

