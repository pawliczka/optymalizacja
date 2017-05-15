#include "LinearProblemSolution.hpp"

LinearProblemSolution::LinearProblemSolution(int _n)
{
    Case = LinearProblemCase::UNKNOWN;
    VariableValues.resize(_n, 0);
}

QString LinearProblemSolution::getNormalSolution() const
{
    QString str;
    str += QString("Rozwiazanie:\t");
    for (int i = 0; i < static_cast<int>(VariableValues.size()); i++)
    {
        str += QString("\tx") + QString::number(i + 1) + QString(" = ") + QString::number(VariableValues[i]);
    }

    str += "\nWartosc funkcji celu:";
    str += ("\t" + QString::number(ObjFuncValue) + "\n");
    return str;
}

QString LinearProblemSolution::getAsString() const
{
    QString str;
    switch (Case)
    {
        case LinearProblemCase::INF_SOLUTIONS_UNBOUND:
        {
            str = getNormalSolution();
            str += "INF_SOLUTIONS_UNBOUND\n";
            break;
        }
        case LinearProblemCase::INF_SOLUTIONS_BOUND:
        {
            str = getNormalSolution();
            str += "INF_SOLUTIONS_BOUND\n";
            break;
        }
        case LinearProblemCase::ONE_SOLUTION:
        {
            str = getNormalSolution();
            break;
        }
        case LinearProblemCase::NO_SOLUTIONS:
        case LinearProblemCase::INCONSISTENT:
        {
            str = "WRONG_TABLE\n";
            break;
        }
        default:
        {
            str = "UNKNOWN\n";
        }
    }
    return str;
}
