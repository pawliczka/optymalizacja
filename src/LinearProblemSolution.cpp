#include "LinearProblemSolution.hpp"
#include <QString>
#include <QDebug>

LinearProblemSolution::LinearProblemSolution(int _n)
{
    Case = LinearProblemCase::UNKNOWN;
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
