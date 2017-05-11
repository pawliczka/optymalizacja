#include "LinearProblemSolution.hpp"

LinearProblemSolution::LinearProblemSolution(int _n)
{
    Case = LinearProblemCase::UNKNOWN;
    VariableValues.resize(_n, 0);
}

QString LinearProblemSolution::getAsString() const
{
    QString str;
    str += QString("Rozwiazanie:\n");
    for (int i = 0; i < static_cast<int>(VariableValues.size()); i++)
    {
        str += QString("\tx") + QString::number(i + 1) + QString(" = ") + QString::number(VariableValues[i]) +
               QString("\n");
    }

    str += "\nWartosc funkcji celu:";
    str += ("\t" + QString::number(ObjFuncValue));
    return str;
}
