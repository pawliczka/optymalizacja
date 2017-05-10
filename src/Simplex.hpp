#pragma once
#include "SimplexTable.hpp"
#include "LinearProblem.hpp"
#include "SimplexStatus.hpp"
#include "LinearProblemSolution.hpp"
#include <memory>

class Simplex
{
public:
    Simplex();
    std::shared_ptr<LinearProblemSolution> Solve(const LinearProblem &problem);
    SimplexStatus getStatus() const;
    int getLoopCnt1Phase() const;
    int getLoopCnt2Phase() const;

private:
    std::shared_ptr<LinearProblemSolution> Solve1Phase();
    std::shared_ptr<LinearProblemSolution> Solve2Phase();
    void CheckNoSolutions();
    void CheckInconsistent();
    void CheckInfSolutionsBounded();
    void CheckInfSolutionsUnbounded();
    bool IsPermissible() const;
    bool IsOptimal() const;
    void UpdateSolution();
    int ChooseNewBaseVar() const;
    int ChooseNewBaseVar(int numRow) const;
    int ChooseFromBase2Delete(int BaseVarIndex) const;
    int ChooseFromBase2Delete1Phase(int BaseVarIndex) const;
    int ChooseTempObjFunc() const;
    void UpdateTable(int k, int r);
    void DisturbTable();

    int LoopCnt1Phase = 0;
    int LoopCnt2Phase = 0;
    SimplexTable Table;
    SimplexStatus Status;
    std::shared_ptr<LinearProblemSolution> Solution;
    OptimizeType Type;
};
