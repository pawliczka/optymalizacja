#pragma once
#include "SimplexTable.hpp"
#include "Equation.hpp"
#include <vector>

class SimplexSolver
{
public:
    SimplexSolver(const std::vector<Equation>&);
    void setCoefficientsOfObjectiveFunction(const Equation&);
    void executePrimalSimplexMethod();
    void printSimplexTableWithCalculations() const;

private:
    void executePrimalIteration();
    bool isSimplexTableIsOptimal() const;
    void countZj();
    void countDeltaJ();
    void countValueOfObjectiveFunction();
    void recountAdditionalParameter();
    void setNumberVariablesInBase(int);
    void printVariablesInBase() const;
    std::pair<int, int> getPositionOfKeyElement() const;
    void setVariableInBase(const std::pair<int, int>&);
    void setSolution();
    void printSolution() const;

    int numberOfIteration = 0;
    float valueOfObjectiveFunction = 0;
    std::vector<float> coefficientsOfObjectiveFunction;
    std::vector<int> numberVariablesInBase;
    std::vector<float> multiplicationZj;
    std::vector<float> deltaJ;
    std::vector<float> solution;
    SimplexTable simplexTable;
};
