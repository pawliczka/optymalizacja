#include "SimplexTable.hpp"
#include <QString>
#include <QDebug>

void SimplexTable::AllocTable()
{
    Tab.resize(numRows, std::vector<double>(numCols, 0.0));
}

void SimplexTable::ObjFuncTo1stRow(const Equation& ObjFunc)
{
    Tab[0][0] = 0;
    for (int i = 1; i < numCols; i++)
        Tab[0][i] = -ObjFunc.getCoefficient(i);
}

void SimplexTable::ConstrToRow(Equation Constr, int Row)
{
    switch (Constr.getComparisonOperator())
    {
        case ComparisonOperator::GreaterEqual:
            Tab[Row][0] = -Constr.getCoefficient(0);
            for (int j = 1; j < numCols; j++)
                Tab[Row][j] = -Constr.getCoefficient(j);
            break;
        case ComparisonOperator::LessEqual:
            Tab[Row][0] = Constr.getCoefficient(0);
            for (int j = 1; j < numCols; j++)
                Tab[Row][j] = Constr.getCoefficient(j);
            break;

        default:
        case ComparisonOperator::Equal:
            break;
    }
}

void SimplexTable::SetupColIndexes()
{
    ColIndex.resize(numBaseVars + 1, 0);
    ColIndex[0] = 0;
    for (int i = 1; i < numBaseVars + 1; i++)
        ColIndex[i] = i;
}

void SimplexTable::SetupRowIndexes()
{
    RowIndex.resize(numAdditionalVars + 1, 0);
    RowIndex[0] = 0;
    for (int i = 1; i < numAdditionalVars + 1; i++)
        RowIndex[i] = numBaseVars + i;
}

SimplexTable::SimplexTable(const LinearProblem& problem)
{
    numBaseVars = problem.getn();
    numAdditionalVars = problem.numLessEqualConstr() + problem.numGreaterEqualConstr();
    numCols = numBaseVars + 1;
    numRows = numAdditionalVars + 1;

    AllocTable();
    ObjFuncTo1stRow(problem.getObjFunc());
    for (int i = 1; i < numRows; i++)
        ConstrToRow(problem.getConstr(i - 1), i);

    SetupColIndexes();
    SetupRowIndexes();
}

void SimplexTable::print() const
{
    QString str;

    str += QString("\t");
    for (int i = 0; i < numBaseVars; i++)
        str += QString("\t-x") + QString::number(ColIndex[i + 1]);
    qDebug() << str;

    for (int i = 0; i < numRows; i++)
    {
        str.clear();
        str += QString("x") + ((RowIndex[i] < 10) ? QString("0") : QString("")) + QString::number(RowIndex[i]);
        for (int j = 0; j < numCols; j++)
            str += QString("\t") + QString::number(Tab[i][j]);
        qDebug() << str;
    }
    qDebug() << endl;
}

double SimplexTable::rowMax(int Row) const
{
    double Max = Tab[Row][1];
    for (int i = 2; i < numCols; i++)
        if (Tab[Row][i] > Max)
            Max = Tab[Row][i];
    return Max;
}

double SimplexTable::rowMin(int Row) const
{
    double Min = Tab[Row][1];
    for (int i = 2; i < numCols; i++)
        if (Tab[Row][i] < Min)
            Min = Tab[Row][i];
    return Min;
}

double SimplexTable::colMax(int Col) const
{
    double Max = Tab[0][Col];
    for (int i = 1; i < numRows; i++)
        if (Tab[i][Col] > Max)
            Max = Tab[i][Col];
    return Max;
}

double SimplexTable::colMin(int Col) const
{
    double Min = Tab[0][Col];
    for (int i = 1; i < numRows; i++)
        if (Tab[i][Col] < Min)
            Min = Tab[i][Col];
    return Min;
}

int SimplexTable::rowMinIndex(int Row) const
{
    double Min = Tab[Row][1];
    int Index = 1;
    for (int i = 2; i < numCols; i++)
        if (Tab[Row][i] < Min)
        {
            Min = Tab[Row][i];
            Index = i;
        }

    return Index;
}

int SimplexTable::colMinIndex(int Col) const
{
    double Min = Tab[1][Col];
    int Index = 1;
    for (int i = 2; i < numRows; i++)
        if (Tab[i][Col] < Min)
        {
            Min = Tab[i][Col];
            Index = i;
        }

    return Index;
}

int SimplexTable::getnumBaseVars() const
{
    return numBaseVars;
}

int SimplexTable::getnumAdditionalVars() const
{
    return numAdditionalVars;
}

int SimplexTable::getnumCols() const
{
    return numCols;
}

int SimplexTable::getnumRows() const
{
    return numRows;
}

double SimplexTable::getTabElem(int row, int col) const
{
    return Tab[row][col];
}

int SimplexTable::getColIndex(int num) const
{
    return ColIndex[num];
}

int SimplexTable::getRowIndex(int num) const
{
    return RowIndex[num];
}

void SimplexTable::swapRowColIndexes(int col, int row)
{
    int tmp = ColIndex[col];
    ColIndex[col] = RowIndex[row];
    RowIndex[row] = tmp;
}

void SimplexTable::setTabElem(int row, int col, double val)
{
    Tab[row][col] = val;
}

int SimplexTable::colNegative(int Col) const
{
    for (int i = 0; i < numRows; i++)
        if (Tab[i][Col] >= 0)
            return 0;
    return 1;
}
