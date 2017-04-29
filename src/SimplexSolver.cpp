#include "SimplexSolver.hpp"
#include <iostream>
#include <iomanip>

SimplexSolver::SimplexSolver(std::vector<Equation> p_equations)
{
    simplexTable = SimplexTable(p_equations);
    deltaJ.resize(simplexTable.ReturnNumberOfColumns() - 1);
    multiplicationZj.resize(simplexTable.ReturnNumberOfColumns() - 1);
    numberVariablesInBase.resize(simplexTable.ReturnNumberOfLines());
    solution.resize(simplexTable.ReturnNumberOfVariables());
    SetNumberVariablesInBase(simplexTable.ReturnNumberOfVariables());
}

void SimplexSolver::SetCoefficientsOfObjectiveFunction(Equation p_objectiveFunction)
{
    coefficientsOfObjectiveFunction.resize(simplexTable.ReturnNumberOfColumns() - 1, 0);
    for (int i = 0; i < simplexTable.ReturnNumberOfColumns() - simplexTable.ReturnNumberOfLines() - 1; i++)
    {
        coefficientsOfObjectiveFunction[i] = p_objectiveFunction.getCoefficient(i + 1);
        std::cout << coefficientsOfObjectiveFunction[i] << " ";
    }
    std::cout << std::endl;
}

void SimplexSolver::ExecutePrimalSimplexMethod()
{
    RecountAdditionalParameter();
    std::cout << "Is simplex table is optimal: " << std::boolalpha << IsSimplexTableIsOptimal() << std::endl;
    while (!IsSimplexTableIsOptimal())
        ExecutePrimalIteration();

    SetSolution();
    PrintSolution();
}

void SimplexSolver::PrintSimplexTableWithCalculations()
{
    int setw_param = 15;

    std::cout << "Columns: " << simplexTable.ReturnNumberOfColumns() << std::endl << "Lines: " << simplexTable.ReturnNumberOfLines() << std::endl;

    for (auto& elem : coefficientsOfObjectiveFunction)
        std::cout << std::setw(setw_param) << elem;

    std::cout << std::endl;

    for (int i = 1; i < simplexTable.ReturnNumberOfColumns(); i++)
        std::cout << std::setw(setw_param - 1) << "x" << i;

    std::cout << std::setw(setw_param) << "Bj" << std::endl;

    simplexTable.PrintSimplexTable(setw_param);

}

void SimplexSolver::ExecutePrimalIteration()
{
    numberOfIteration++;
    std::cout << "Executing iteration number:  " << numberOfIteration << std::endl;

    std::pair<int, int> positionOfKeyElement = ReturnPositionOfKeyElement();
    SetVariableInBase(positionOfKeyElement);
    PrintVariablesInBase();
    // Recount simplexTable

    SimplexTable simplexTable_new(simplexTable);
    for (int line = 0; line < simplexTable.ReturnNumberOfLines(); line++)
    {
        for (int column = 0; column < simplexTable.ReturnNumberOfColumns(); column++)
        {
            if (!(line == positionOfKeyElement.first))
                simplexTable_new.SetElement(line,column,
                    simplexTable.ReturnElement(line,column) -
                    ((simplexTable.ReturnElement(positionOfKeyElement.first, column) *
                         simplexTable.ReturnElement(line, positionOfKeyElement.second)) /
                        simplexTable.ReturnElement(positionOfKeyElement.first, positionOfKeyElement.second)));
            else // key line
                simplexTable_new.SetElement(line,column, simplexTable.ReturnElement(line,column) / simplexTable.ReturnElement(positionOfKeyElement.first, positionOfKeyElement.second));
        }
    }

    simplexTable = simplexTable_new;
    PrintSimplexTableWithCalculations();
    RecountAdditionalParameter();
}

bool SimplexSolver::IsSimplexTableIsOptimal()
{
    for (auto const& elem : deltaJ)
    {
        if (elem > 0)
            return false;
    }
    return true;
}

void SimplexSolver::CountZj()
{
    std::fill(multiplicationZj.begin(), multiplicationZj.end(), 0);
    for (int i = 0; i < static_cast<int>(multiplicationZj.size()); i++)
    {
        for (int j = 0; j < simplexTable.ReturnNumberOfLines(); j++)
            multiplicationZj[i] += coefficientsOfObjectiveFunction[numberVariablesInBase[j] - 1] * simplexTable.ReturnElement(j, i);
    }

    std::cout << "Zj: ";
    for (auto& elem : multiplicationZj)
        std::cout << elem << " ";
    std::cout << std::endl;
}

void SimplexSolver::CountDeltaJ()
{
    for (int i = 0; i < static_cast<int>(deltaJ.size()); i++)
        deltaJ[i] = coefficientsOfObjectiveFunction[i] - multiplicationZj[i];

    std::cout << "delta J: ";
    for (auto& elem : deltaJ)
        std::cout << elem << " ";
    std::cout << std::endl;
}

void SimplexSolver::CountValueOfObjectiveFunction()
{
    valueOfObjectiveFunction = 0;
    for (int j = 0; j < simplexTable.ReturnNumberOfLines(); j++)
        valueOfObjectiveFunction +=
            coefficientsOfObjectiveFunction[numberVariablesInBase[j] - 1] * simplexTable.ReturnElement(j, simplexTable.ReturnNumberOfColumns() - 1);

    std::cout << "Funkcja celu: " << valueOfObjectiveFunction << std::endl;
}

void SimplexSolver::RecountAdditionalParameter()
{
    CountZj();
    CountDeltaJ();
    CountValueOfObjectiveFunction();
}

void SimplexSolver::SetNumberVariablesInBase(int numberOfVariables)
{
    for (int i = 0; i < simplexTable.ReturnNumberOfLines(); i++)
        numberVariablesInBase[i] = numberOfVariables + i + 1;

    PrintVariablesInBase();
}

void SimplexSolver::PrintVariablesInBase()
{
    std::cout << "In base actually: ";
    for (auto& elem : numberVariablesInBase)
        std::cout << "x" << elem << " ";
    std::cout << std::endl;
}

std::pair<int, int> SimplexSolver::ReturnPositionOfKeyElement()
{
    int indexColumnIntoBase = std::distance(deltaJ.begin(), std::max_element(deltaJ.begin(), deltaJ.end()));
    std::cout << "Distance: " << indexColumnIntoBase << std::endl;

    std::vector<float> quotientByColumn;
    quotientByColumn.resize(simplexTable.ReturnNumberOfLines());
    for (int i = 0; i < simplexTable.ReturnNumberOfLines(); i++)
    {
        quotientByColumn[i] = simplexTable.ReturnElement(i, simplexTable.ReturnNumberOfColumns() - 1) / simplexTable.ReturnElement(i, indexColumnIntoBase);
    }

    float minimumToFind = std::numeric_limits<float>::max();
    for (auto const& elem : quotientByColumn)
    {
        if (elem > 0)
            minimumToFind = std::min(elem, minimumToFind);
    }

    int indexLineOutOfBase = std::distance(
        quotientByColumn.begin(), std::find(quotientByColumn.begin(), quotientByColumn.end(), minimumToFind));

    return std::pair<int, int>(indexLineOutOfBase, indexColumnIntoBase);
}

void SimplexSolver::SetVariableInBase(std::pair<int, int> position)
{
    numberVariablesInBase[position.first] = position.second + 1;
}

void SimplexSolver::SetSolution()
{
    int indexOfLine = 0;
    for (int i = 0; i < static_cast<int>(solution.size()); i++)
    {
        indexOfLine = std::distance(
            numberVariablesInBase.begin(), std::find(numberVariablesInBase.begin(), numberVariablesInBase.end(), i+1));
        std::cout << "Index do wziecia: " << indexOfLine << " ";
        solution[i] = simplexTable.ReturnElement(indexOfLine, simplexTable.ReturnNumberOfColumns() - 1);
    }
}

void SimplexSolver::PrintSolution()
{
    std::cout << "SOLUTION IS: ";
    for (auto const& elem : solution)
        std::cout << elem << " ";
    std::cout << std::endl;
}

