#include "SimplexTable.hpp"
#include <iostream>
#include <iomanip>
#include <limits>

SimplexTable::SimplexTable()
{
}

void SimplexTable::fillSimplexTable(const std::vector<Equation>& p_equations)
{
    simplexTable.resize(numberOfLines, std::vector<float>(numberOfColumns, 0));

    for (int i = 0; i < numberOfLines; i++)
    {
        for (int j = 0; j < p_equations[i].getIndexOfLastCofficient(); j++)
        {
            simplexTable[i][j] = p_equations[i].getCoefficient(j + 1);
            simplexTable[i][numberOfVariables + i] = 1;
            simplexTable[i][numberOfColumns - 1] = -p_equations[i].getCoefficient(0); // Bj z minusem
        }
    }
}

SimplexTable::SimplexTable(const std::vector<Equation>& p_equations)
{
    numberOfVariables = howManyVariables(p_equations);
    std::cout << numberOfVariables << std::endl;
    numberOfLines = static_cast<int>(p_equations.size());
    numberOfColumns = (numberOfVariables + 1) + numberOfLines;
    fillSimplexTable(p_equations);
}

void SimplexTable::PrintSimplexTable(int setw_param) const
{
    for (int i = 0; i < numberOfLines; i++)
    {
        for (int j = 0; j < numberOfColumns; j++)
        {
            std::cout << std::setw(setw_param) << simplexTable[i][j];
        }
        std::cout << std::endl;
    }
}

int SimplexTable::howManyVariables(const std::vector<Equation>& p_equations)
{
    int numberOfVariables = 0;
    std::for_each(p_equations.begin(), p_equations.end(), [&numberOfVariables](const Equation& equation) {
        numberOfVariables = std::max(numberOfVariables, equation.getIndexOfLastCofficient());
    });
    return numberOfVariables;
}

int SimplexTable::getNumberOfColumns() const
{
    return numberOfColumns;
}

int SimplexTable::getNumberOfLines() const
{
    return numberOfLines;
}

int SimplexTable::getNumberOfVariables() const
{
    return numberOfVariables;
}

float SimplexTable::getElement(int line, int column) const
{
    return simplexTable[line][column];
}

void SimplexTable::setElement(int line, int column, float value)
{
    simplexTable[line][column] = value;
}
