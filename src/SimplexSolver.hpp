#pragma once
#include "SimplexTable.hpp"
#include "Equation.hpp"
#include <vector>

class SimplexSolver
{
public:
    SimplexSolver(const std::vector<Equation> &);
    void SetCoefficientsOfObjectiveFunction(const Equation &);
    void ExecutePrimalSimplexMethod();
    void PrintSimplexTableWithCalculations();

private:
    void ExecutePrimalIteration();
    bool IsSimplexTableIsOptimal();
    void CountZj();
    void CountDeltaJ();
    void CountValueOfObjectiveFunction();
    void RecountAdditionalParameter();
    void SetNumberVariablesInBase(int);
    void PrintVariablesInBase();
    std::pair<int, int> ReturnPositionOfKeyElement();
    void SetVariableInBase(const std::pair<int, int> &);
    void SetSolution();
    void PrintSolution();

    int numberOfIteration = 0;
    float valueOfObjectiveFunction = 0;
    std::vector<float> coefficientsOfObjectiveFunction;
    std::vector<int> numberVariablesInBase;
    std::vector<float> multiplicationZj;
    std::vector<float> deltaJ;
    std::vector<float> solution;
    SimplexTable simplexTable;
};
