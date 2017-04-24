#pragma once
#include <vector>

class SimplexTable
{
public:
    SimplexTable();
    SimplexTable(int numberOfEquations);
private:
    std:vector<std::vector<float>> simplexTable;
    std::vector<float> coefficientsOfObjectiveFunction;

};

