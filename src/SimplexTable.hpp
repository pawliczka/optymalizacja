#pragma once
#include <vector>
#include <algorithm>
#include "Equation.hpp"


class SimplexTable
{
public:
    SimplexTable();
    SimplexTable(std::vector<Equation>);
    void PrintSimplexTable(int);

    int ReturnNumberOfColumns();
    int ReturnNumberOfLines();
    int ReturnNumberOfVariables();

    float ReturnElement(int, int) const;
    float SetElement(int, int, float);

private:
    int numberOfColumns = {0};
    int numberOfLines = {0};
    int numberOfVariables = {0};
    std::vector<std::vector<float>> simplexTable;

    int howManyVariables(std::vector<Equation>); //do wyjebania na zewnatrz






};

