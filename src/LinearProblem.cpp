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

void LinearProblem::SetObjFunc(const Equation& ObjFuncOrig)
{
    n = ObjFuncOrig.getIndexOfLastCofficient();
    if(type == OptimizeType::MIN)
    {
        ObjFunc = ObjFuncOrig.getWithNegativeSign();
        return;
    }
    ObjFunc = ObjFuncOrig;
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
    int lessEqualCounter = 0;
    for (int i = 0; i < this->m; i++)
        if (ConstrSet[i].getComparisonOperator() == ComparisonOperator::LessEqual)
            lessEqualCounter++;

    return lessEqualCounter;
}

int LinearProblem::numGreaterEqualConstr() const
{
    int greaterEqualCounter = 0;
    for (int i = 0; i < this->m; i++)
        if (ConstrSet[i].getComparisonOperator() == ComparisonOperator::GreaterEqual)
            greaterEqualCounter++;

    return greaterEqualCounter;
}

Equation LinearProblem::getConstr(int constrNum) const
{
    if (constrNum >= m)
        constrNum = m - 1;
    return ConstrSet[constrNum];
}
