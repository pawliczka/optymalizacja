#include "SimplexTable.hpp"
#include <iostream>
#include <iomanip>
#include <limits>

SimplexTable::SimplexTable()
{
}

SimplexTable::SimplexTable(std::vector<Equation> p_equations)
{
    int numberOfVariables = howManyVariables(p_equations);
    std::cout << numberOfVariables << std::endl;
    numberOfLines = static_cast<int>(p_equations.size());
    numberOfColumns = (numberOfVariables + 1) + numberOfLines;

    simplexTable.resize(numberOfLines, std::vector<float>(numberOfColumns,0));

    for (int i = 0; i < numberOfLines; i++)
    {
        for (int j = 0; j < p_equations[i].getIndexOfLastCofficient(); j++)
        {
            simplexTable[i][j] = p_equations[i].getCoefficient(j+1);
            simplexTable[i][numberOfVariables+i] = 1;
            simplexTable[i][numberOfColumns-1] = -p_equations[i].getCoefficient(0); //Bj z minusem
        }
    }
    numberVariablesInBase.resize(numberOfLines);
    multiplicationZj.resize(numberOfColumns-1);
    deltaJ.resize(numberOfColumns-1);

    SetNumberVariablesInBase(numberOfVariables);
}

void SimplexTable::SetCoefficientsOfObjectiveFunction(Equation p_objectiveFunction)
{
    coefficientsOfObjectiveFunction.resize(numberOfColumns-1,0);
    for(int i = 0; i < numberOfColumns-numberOfLines-1; i++)
        coefficientsOfObjectiveFunction[i]=p_objectiveFunction.getCoefficient(i+1);
}

void SimplexTable::PrintVariablesInBase()
{
    std::cout << "In base actually: ";
    for(auto &elem : numberVariablesInBase)
        std::cout << "x" << elem << " ";
    std::cout << std::endl;
}

void SimplexTable::SetNumberVariablesInBase(int numberOfVariables)
{
    for(int i = 0; i < numberOfLines; i++)
        numberVariablesInBase[i] = numberOfVariables + i + 1;

    PrintVariablesInBase();
}

void SimplexTable::RecountAdditionalParameter()
{
    CountZj();
    CountDeltaJ();
    CountValueOfObjectiveFunction();
}


void SimplexTable::ExecuteSimplexMethod()
{
    RecountAdditionalParameter();
    std::cout << "Is simplex table is optimal: " << std::boolalpha << IsSimplexTableIsOptimal() << std::endl;
    if(!IsSimplexTableIsOptimal())
        ExecuteIteration();


}

void SimplexTable::PrintSimplexTable()
{
    int setw_param = 8;
    std::cout << "Columns: " << numberOfColumns << std::endl
              << "Lines: " << numberOfLines << std::endl;

    for (auto &elem : coefficientsOfObjectiveFunction)
        std::cout << std::setw(setw_param) << elem;

    std::cout << std::endl;

    for(int i = 1; i < numberOfColumns; i++)
        std::cout << std::setw(setw_param-1) << "x" << i;

    std::cout << std::setw(setw_param) << "Bj" << std::endl;

    for (int i = 0; i < numberOfLines; i++)
    {
        for (int j = 0; j < numberOfColumns; j++)
        {
            std::cout << std::setw(setw_param) << simplexTable[i][j];
        }
        std::cout << std::endl;
    }
}


int SimplexTable::howManyVariables(std::vector<Equation> p_equations)
{
    int numberOfVariables = 0;
    std::for_each(p_equations.begin(), p_equations.end(), [&numberOfVariables](Equation& equation) {
        numberOfVariables = std::max(numberOfVariables, equation.getIndexOfLastCofficient());
    });
    return numberOfVariables;
}

void SimplexTable::ExecuteIteration()
{
    numberOfIteration++;
    std::cout << "Executing iteration number:  " << numberOfIteration << std::endl;

    int indexColumnIntoBase = std::distance(deltaJ.begin(),std::max_element(deltaJ.begin(), deltaJ.end()));
    std::cout <<"Distance: "<< indexColumnIntoBase << std::endl;

    std::vector<float> quotientByColumn;
    quotientByColumn.resize(numberOfLines);
    for(int i = 0; i < numberOfLines; i++)
    {
        quotientByColumn[i] = simplexTable[i][numberOfColumns-1] / simplexTable[i][indexColumnIntoBase];
        std::cout << quotientByColumn[i] << " ";
    }
    std::cout<<std::endl;

    float minimumToFind = std::numeric_limits<float>::max();
    for (auto const &elem : quotientByColumn)
    {
        if(elem > 0)
            minimumToFind = std::min(elem,minimumToFind);
    }
    std::cout<< "inimum: "<<minimumToFind << std::endl;

    int indexLineOutOfBase = std::distance(quotientByColumn.begin(),std::find(quotientByColumn.begin(),quotientByColumn.end(),minimumToFind));
    std::cout<< "Out of base: "<<indexLineOutOfBase << std::endl;

    numberVariablesInBase[indexLineOutOfBase] = indexColumnIntoBase;
    PrintVariablesInBase();
}

void SimplexTable::CountZj()
{
    for(int i = 0; i < static_cast<int>(multiplicationZj.size()); i++)
    {
        for(int j = 0; j < numberOfLines; j++)
            multiplicationZj[i] += coefficientsOfObjectiveFunction[numberVariablesInBase[j]-1] * simplexTable[j][i];
    }

    std::cout << "Zj: ";
    for(auto &elem : multiplicationZj)
        std::cout << elem << " ";
    std::cout << std::endl;
}

void SimplexTable::CountDeltaJ()
{
    for(int i = 0; i < static_cast<int>(deltaJ.size()); i++)
        deltaJ[i] = coefficientsOfObjectiveFunction[i] - multiplicationZj[i];

    std::cout << "delta J: ";
    for(auto &elem : deltaJ)
        std::cout << elem << " ";
    std::cout << std::endl;
}

void SimplexTable::CountValueOfObjectiveFunction()
{
    for(int j = 0; j < numberOfLines; j++)
        valueOfObjectiveFunction = coefficientsOfObjectiveFunction[numberVariablesInBase[j]-1] * simplexTable[j][numberOfColumns-1];

    std::cout << "Funkcja celu: " << valueOfObjectiveFunction << std::endl;
}

bool SimplexTable::IsSimplexTableIsOptimal()
{
   for (auto const &elem : deltaJ)
   {
        if(elem > 0)
            return false;
   }
   return true;
}
