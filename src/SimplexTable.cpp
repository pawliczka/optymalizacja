#include "SimplexTable.hpp"
#include <iostream>

SimplexTable::SimplexTable()
{

}

SimplexTable::SimplexTable(std::vector<Equation> p_equations)
{
    int numberOfVariables=howManyVariables(p_equations);
    numberOfLines = p_equations.size();
    numberOfColumns = numberOfVariables + numberOfLines;

    std::vector<std::vector<float>> simplexTable2(numberOfLines, std::vector<float>(numberOfColumns));
    simplexTable = simplexTable2;

    for (int i = 0; i < numberOfLines; i++)
    {
        for(int j = 0; j < numberOfColumns; j++)
        {
            simplexTable[i][j] = p_equations[i].getCoefficient(j);
            std::cout << simplexTable[i][j] << " ";
        }
        std::cout << std::endl;
    }



    std::cout << "Kolumn: " << numberOfColumns << std::endl << "Lines: " << numberOfLines << std::endl;
}

int SimplexTable::howManyVariables(std::vector<Equation> p_equations)
{
    int numberOfVariables=0;
    std::for_each(
        p_equations.begin(),p_equations.end(), [this, &numberOfVariables](Equation & equation){
            if(equation.getIndexOfLastCofficient() > numberOfVariables)
                numberOfVariables = equation.getIndexOfLastCofficient();
        });
    return numberOfVariables;
}

