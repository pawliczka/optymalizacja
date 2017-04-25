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

private:
    int numberOfColumns = {0};
    int numberOfLines = {0};

    std::vector<std::vector<float>> simplexTable;
    std::vector<float> coefficientsOfObjectiveFunction;

    int howManyVariables(std::vector<Equation>); //do wyjebania na zewnatrz

};

