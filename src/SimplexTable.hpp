#pragma once
#include "LinearProblem.hpp"
#include <string>
#include <vector>

class SimplexTable
{
public:
    SimplexTable() {}
    SimplexTable(const LinearProblem& problem);

    void print() const;
    double rowMax(int Row) const;
    double rowMin(int Row) const;
    double colMax(int Col) const;
    double colMin(int Col) const;
    int colNegative(int Col) const;
    int rowMinIndex(int Col) const;
    int colMinIndex(int Col) const;
    int getnumBaseVars() const;
    int getnumAdditionalVars() const;
    int getnumCols() const;
    int getnumRows() const;
    double getTabElem(int row, int col) const;
    int getColIndex(int num) const;
    int getRowIndex(int num) const;
    void swapRowColIndexes(int col, int row);
    void setTabElem(int row, int col, double val);

private:
    int numBaseVars;
    int numAdditionalVars;
    int numCols;
    int numRows;
    std::vector<std::vector<double>> Tab;
    std::vector<int> ColIndex;
    std::vector<int> RowIndex;
    void AllocTable();
    void ObjFuncTo1stRow(const Equation& ObjFunc);
    void ConstrToRow(Equation Constr, int Row);
    void SetupColIndexes();
    void SetupRowIndexes();
};
