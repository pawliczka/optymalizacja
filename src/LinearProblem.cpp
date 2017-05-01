#include "LinearProblem.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <QDebug>

using namespace std;

LinearProblem::LinearProblem(OptimizeType _type)
{
    n = 0;
    type = _type;
    m = 0;
}

void LinearProblem::SetObjFunc(Equation& ObjFuncOrig)
{
    ObjFunc = ObjFuncOrig;
    n = ObjFunc.getIndexOfLastCofficient();
}

void LinearProblem::setConstrains(const std::vector<Equation>& constrains)
{
    ConstrSet = constrains;
    m = constrains.size();
}

double LinearProblem::RemoveLastConstr()
{
    double LastConstrb = ConstrSet[m].getCoefficient(0);
    ConstrSet.pop_back();
    m--;
    return LastConstrb;
}

void LinearProblem::print() const
{
    int i;

    qDebug() << "Zadanie ";
    switch (type)
    {
        case OptimizeType::MAX:
            qDebug() << "maksymalizacji";
            break;
        case OptimizeType::MIN:
            qDebug() << "minimalizacji";
            break;
    }
    qDebug() << " funkcji celu postaci:" << endl;
    // qDebug() << ObjFunc << endl;
    qDebug() << endl << "Przy ograniczeniach:" << endl;
    for (i = 0; i < this->m; i++)
    {
        // ConstrSet[i]->print();
    }
    qDebug() << endl;
}

int LinearProblem::numLessEqualConstr() const
{
    int lessEqualCnt = 0;
    for (int i = 0; i < this->m; i++)
        if (ConstrSet[i].getComparisonOperator() == ComparisonOperator::LessEqual)
            lessEqualCnt++;

    return lessEqualCnt;
}

int LinearProblem::numGreaterEqualConstr() const
{
    int greaterEqualCnt = 0;
    for (int i = 0; i < this->m; i++)
        if (ConstrSet[i].getComparisonOperator() == ComparisonOperator::GreaterEqual)
            greaterEqualCnt++;

    return greaterEqualCnt;
}

Equation LinearProblem::getConstr(int constrNum) const
{
    if (constrNum >= m)
        constrNum = m - 1;
    return ConstrSet[constrNum];
}

LinearProblemSolution::LinearProblemSolution(int _n)
{
    Case = LinProblemCase::UNKNOWN;
    VariableValues.resize(_n, 0);
}

void LinearProblemSolution::print() const
{
    QString str;
    str += QString("\nRozwiazanie:\n");
    for (int i = 0; i < static_cast<int>(VariableValues.size()); i++)
    {
        str += QString("\tx") + QString::number(i + 1) + QString(" = ") + QString::number(VariableValues[i]) +
               QString("\n");
    }

    qDebug() << str;
    qDebug() << "Wartosc funkcji celu:";
    qDebug() << "\t" << ObjFuncValue << endl;
}
