#include "Simplex.hpp"
#include <assert.h>
#include <iostream>
#include <QDebug>

Simplex::Simplex(const LinProblem& Problem)
    : Table(Problem)
{
    Type = Problem.gettype();
    Solution = std::make_shared<LinProblemSolution>(Problem.getn());
}

void Simplex::CheckNoSolutions()
{
    int NoSolutions = 0;

    for (int i = 0; i < Table.getnumCols(); i++)
        if (Table.getTabElem(0, i) < 0)
        {
            NoSolutions = 1;
            // kolejne elementy nie moga byc tylko niedodatnie
            for (int j = 1; j < Table.getnumRows(); j++)
                if (Table.getTabElem(j, i) > 0)
                {
                    NoSolutions = 0;
                    break;
                }
            if (NoSolutions)
            {
                State.Case = LinProblemCase::NO_SOLUTIONS;
                return;
            }
        }
}
void Simplex::CheckInconsistent()
{
    int Inconsistent = 0;

    for (int i = 1; i < Table.getnumRows(); i++)
        if (Table.getTabElem(i, 0) <= 0)
        {
            Inconsistent = 1;
            // kolejne elementy nie moga byc tylko nieujemne
            for (int j = 1; j < Table.getnumCols(); j++)
                if (Table.getTabElem(i, j) <= 0)
                {
                    Inconsistent = 0;
                    break;
                }

            if (Inconsistent)
            {
                State.Case = LinProblemCase::INCONSISTENT;
                return;
            }
        }
}
void Simplex::CheckInfSolutionsBounded()
{
    for (int j = 1; j < Table.getnumCols(); j++)
        if (Table.getTabElem(0, j) == 0)
        {
            // wyraz w pierwszej kolumnie oraz element centr. musza byc <= 0
            for (int i = 1; i < Table.getnumRows(); i++)
                if (Table.getTabElem(i, 0) > 0 && Table.getTabElem(i, j) > 0)
                {
                    State.Case = LinProblemCase::INF_SOLUTIONS_BOUND;
                    return;
                }
        }
}
void Simplex::CheckInfSolutionsUnbounded()
{
    int InfSolutionsUnbound = 1;

    for (int i = 1; i < Table.getnumCols(); i++)
        if (Table.getTabElem(0, i) == 0)
        {
            InfSolutionsUnbound = 1;
            // kolejne elementy nie moga byc tylko ujemne
            for (int j = 1; j < Table.getnumRows(); j++)
                if (Table.getTabElem(j, i) >= 0)
                {
                    InfSolutionsUnbound = 0;
                    break;
                }

            if (InfSolutionsUnbound)
            {
                State.Case = LinProblemCase::INF_SOLUTIONS_UNBOUND;
                return;
            }
        }
}

bool Simplex::IsPermissible() const
{
    for (int i = 1; i < Table.getnumRows(); i++)
        if (Table.getTabElem(i, 0) < 0)
            return false;

    return true;
}

bool Simplex::IsOptimal() const
{
    for (int i = 1; i < Table.getnumCols(); i++)
        if (Table.getTabElem(0, i) < 0)
            return false;

    return true;
}

void Simplex::UpdateSolution()
{
    Solution->ObjFuncValue = Table.getTabElem(0, 0);

    int n = Table.getnumBaseVars();
    for (int i = 1; i < Table.getnumRows(); i++)
        if (Table.getRowIndex(i) <= n)
            Solution->VariableValues[Table.getRowIndex(i) - 1] = Table.getTabElem(i, 0);
    for (int j = 1; j < Table.getnumCols(); j++)
        if (Table.getColIndex(j) <= n)
            Solution->VariableValues[Table.getColIndex(j) - 1] = 0;
}

int Simplex::ChooseNewBaseVar() const
{
    return Table.rowMinIndex(0);
}

int Simplex::ChooseNewBaseVar(int numRow) const
{
    return Table.rowMinIndex(numRow);
}

int Simplex::ChooseFromBase2Delete(int BaseVarIndex) const
{
    int Index = -1;
    double MinOfPositive = 1000000;
    double TempElem;

    for (int i = 1; i < Table.getnumRows(); i++)
    {
        if (Table.getTabElem(i, BaseVarIndex))
        {
            TempElem = Table.getTabElem(i, 0) / Table.getTabElem(i, BaseVarIndex);
            if (TempElem < MinOfPositive && Table.getTabElem(i, BaseVarIndex) > 0)
            {
                Index = i;
                MinOfPositive = TempElem;
            }
        }
    }

    return Index;
}

int Simplex::ChooseFromBase2Delete1Phase(int BaseVarIndex) const
{
    int Index = -1;
    double MinOfPositive = 1000000;
    double TempElem;

    for (int i = 1; i < Table.getnumRows(); i++)
    {
        if (Table.getTabElem(i, BaseVarIndex))
        {
            TempElem = Table.getTabElem(i, 0) / Table.getTabElem(i, BaseVarIndex);
            if (TempElem < MinOfPositive && TempElem > 0)
            {
                Index = i;
                MinOfPositive = TempElem;
            }
        }
    }
    return Index;
}

int Simplex::ChooseTempObjFunc() const
{
    double MinValue = 999999;
    double Elem = 0;
    int Index = -1;
    for (int i = 1; i < Table.getnumRows(); i++)
    {
        Elem = Table.getTabElem(i, 0);
        if (Elem < MinValue)
        {
            MinValue = Elem;
            Index = i;
        }
    }

    return Index;
}

void Simplex::UpdateTable(int k, int r)
{
    double centralElement = Table.getTabElem(r, k);

    for (int i = 0; i < Table.getnumRows(); i++)
        for (int j = 0; j < Table.getnumCols(); j++)
            if (i != r && j != k)
                Table.setTabElem(
                    i, j, Table.getTabElem(i, j) - Table.getTabElem(i, k) * Table.getTabElem(r, j) / centralElement);

    for (int i = 0; i < Table.getnumRows(); i++)
        Table.setTabElem(i, k, -Table.getTabElem(i, k) / centralElement);

    for (int j = 0; j < Table.getnumCols(); j++)
        Table.setTabElem(r, j, Table.getTabElem(r, j) / centralElement);

    Table.setTabElem(r, k, 1 / centralElement);
}

void Simplex::DisturbTable()
{
    static double Multiplicator = 1;

    /* indeks elementu o najmniejszej wartosci */
    int MinIndex = Table.colMinIndex(0);
    /* indeks elementu o drugiej najmniejszej */
    int SecondMinIndex = -1;
    double Min = 999999;

    for (int i = 1; i < Table.getnumRows(); i++)
    {
        if (i == MinIndex)
            continue;
        if (Table.getTabElem(i, 0) < Min)
        {
            Min = Table.getTabElem(i, 0);
            SecondMinIndex = i;
        }
    }

    /* do drugiego najmniejszego elementu wpisujemy troche mniejsza wartosc niz
       byla w najmniejszym */
    Table.setTabElem(SecondMinIndex, 0, Table.getTabElem(MinIndex, 0) - 0.0001 * Multiplicator);
    Multiplicator *= 2;
    if (Multiplicator > 1000)
        State.Case = LinProblemCase::INCONSISTENT;
}

std::shared_ptr<LinProblemSolution> Simplex::Solve()
{
  //  Table.print();
    State.Status = STATUS_BUSY;
    State.Case = LinProblemCase::ONE_SOLUTION;
    Solve1Phase();
    CheckNoSolutions();

    switch (State.Case)
    {
        case LinProblemCase::INCONSISTENT:
            State.Status = STATUS_WRONG_TABLE;
            break;
        case LinProblemCase::NO_SOLUTIONS:
            State.Status = STATUS_WRONG_TABLE;
            break;
        default:
            Solve2Phase();
            State.Status = STATUS_SOLVED;
    }

    Solution->Case = State.Case;
    if (Type == OptimizeType::MIN)
        Solution->ObjFuncValue *= -1;
    return Solution;
}

std::shared_ptr<LinProblemSolution> Simplex::Solve1Phase()
{
    int Step = 0;
    double Last2Values[2] = {0, 0}; // L2V[0] - wartość w poprzednim kroku
    // L2V[1] - wartość dwa kroki wcześniej

    while (!IsPermissible())
    {
        State.LoopCnt1Phase++;
        CheckInconsistent();
        if (State.Case == LinProblemCase::INCONSISTENT)
            break;

        int TempObjFuncIndex = ChooseTempObjFunc();
        int InputToBase = ChooseNewBaseVar(TempObjFuncIndex);
        int DeletedFromBase = ChooseFromBase2Delete1Phase(InputToBase);
        if (DeletedFromBase == -1)
        {
            State.Case = LinProblemCase::NO_SOLUTIONS;
            return NULL;
        }

        Table.swapRowColIndexes(InputToBase, DeletedFromBase);
        UpdateTable(InputToBase, DeletedFromBase);
      //  Table.print();

        if (Table.getTabElem(0, 0) == Last2Values[1])
            DisturbTable();

        qDebug() << "Krok " << Step++ << " I fazy | x0 =" << Table.getTabElem(0, 0) << endl;

        Last2Values[1] = Last2Values[0];
        Last2Values[0] = Table.getTabElem(0, 0);
    }

    return Solution;
}

std::shared_ptr<LinProblemSolution> Simplex::Solve2Phase()
{
    int Step = 0;
    while (!IsOptimal())
    {
        State.LoopCnt2Phase++;
        int InputToBase = ChooseNewBaseVar();
        int DeletedFromBase = ChooseFromBase2Delete(InputToBase);
        if (DeletedFromBase == -1)
        {
            State.Case = LinProblemCase::NO_SOLUTIONS;
            return NULL;
        }

        Table.swapRowColIndexes(InputToBase, DeletedFromBase);
        UpdateTable(InputToBase, DeletedFromBase);
      //  Table.print();
        qDebug() << "Krok " << Step++ << " II fazy | x0 =" << Table.getTabElem(0, 0) << endl;
    }

    CheckInfSolutionsBounded();
    CheckInfSolutionsUnbounded();
    UpdateSolution();

    return Solution;
}
