#pragma once
#include <vector>
#include <algorithm>
#include "Equation.hpp"


class SimplexTable
{
public:
    SimplexTable();
    SimplexTable(const std::vector<Equation>&);
    void PrintSimplexTable(int) const;
    int getNumberOfColumns() const;
    int getNumberOfLines() const;
    int getNumberOfVariables() const;
    float getElement(int, int) const;
    void setElement(int, int, float);

private:
    std::vector<std::vector<float>> simplexTable;
    int howManyVariables(const std::vector<Equation>&); // do wyjebania na zewnatrz
    void fillSimplexTable(const std::vector<Equation>& p_equations);

    int numberOfColumns = 0;
    int numberOfLines = 0;
    int numberOfVariables = 0;
};
