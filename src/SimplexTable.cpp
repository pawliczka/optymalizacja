#include "SimplexTable.hpp"
#include <iostream>
#include <iomanip>

SimplexTable::SimplexTable()
{
}

void SimplexTable::PrintSimplexTable()
{
    int setw_param = 5;
    std::cout << std::setw(setw_param) << "Bj";
    for(int i = 1; i < numberOfColumns; i++)
        std::cout << std::setw(setw_param) << "x" << i;

    std::cout << std::endl;

    for (int i = 0; i < numberOfLines; i++)
    {
        for (int j = 0; j < numberOfColumns; j++)
        {
            std::cout << std::setw(setw_param) << simplexTable[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "Columns: " << numberOfColumns << std::endl
              << "Lines: " << numberOfLines << std::endl;
}

SimplexTable::SimplexTable(std::vector<Equation> p_equations)
{
    int numberOfVariables = howManyVariables(p_equations);
    std::cout << numberOfVariables << std::endl;
    numberOfLines = p_equations.size();
    numberOfColumns = (numberOfVariables + 1) + numberOfLines;

    simplexTable.resize(numberOfLines, std::vector<float>(numberOfColumns,0));

    for (int i = 0; i < numberOfLines; i++)
    {
        for (int j = 0; j <= p_equations[i].getIndexOfLastCofficient(); j++)
        {
            simplexTable[i][j] = p_equations[i].getCoefficient(j);
            simplexTable[i][numberOfVariables+1+i] = 1;
        }
    }

    PrintSimplexTable();

}

int SimplexTable::howManyVariables(std::vector<Equation> p_equations)
{
    int numberOfVariables = 0;
    std::for_each(p_equations.begin(), p_equations.end(), [&numberOfVariables](Equation& equation) {
        numberOfVariables = std::max(numberOfVariables, equation.getIndexOfLastCofficient());
    });
    return numberOfVariables;
}
