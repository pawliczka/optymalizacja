#pragma once
#include <vector>
#include <algorithm>
#include "Equation.hpp"

class SimplexTable
{
public:
    SimplexTable();
    SimplexTable(std::vector<Equation>);
    void PrintSimplexTable();
    void SetCoefficientsOfObjectiveFunction(Equation);
    void SetNumberVariablesInBase(int numberOfVariables);
    void ExecuteSimplexMethod();

private:
    int numberOfColumns = {0};
    int numberOfLines = {0};

    int valueOfObjectiveFunction = {0};
    int numberOfIteration = {0};

    std::vector<std::vector<float>> simplexTable;
    std::vector<float> coefficientsOfObjectiveFunction;
    std::vector<int> numberVariablesInBase;
    std::vector<float> multiplicationZj;
    std::vector<float> deltaJ;

    int howManyVariables(std::vector<Equation>); //do wyjebania na zewnatrz
    void ExecuteIteration();
    void CountZj();
    void CountDeltaJ();
    void CountValueOfObjectiveFunction();
    bool IsSimplexTableIsOptimal();
    void RecountAdditionalParameter();

    void PrintVariablesInBase();
};

