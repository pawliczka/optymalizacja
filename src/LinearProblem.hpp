#pragma once
#include <vector>
#include <string>
#include "Equation.hpp"
#include "LinearProblemCase.hpp"

enum class OptimizeType
{
    MAX,
    MIN
};

class LinearProblem
{
public:
    LinearProblem(OptimizeType _type);
    void SetObjFunc(const Equation &ObjFuncOrig);
    void setConstrains(const std::vector<Equation>& constrains);
    void addConstrain(const Equation& constrain);
    double RemoveLastConstr();
    void print() const;
    int getn() const { return n; }
    int getm() const { return m; }
    OptimizeType gettype() const { return type; }
    OptimizeType setType(OptimizeType newType) { return type = newType; }
    int numLessEqualConstr() const;
    int numGreaterEqualConstr() const;
    const Equation& getObjFunc() const { return ObjFunc; }
    Equation getConstr(int _constrNum) const;

private:
    int n = 0;
    int m = 0;
    Equation ObjFunc;
    std::vector<Equation> ConstrSet;
    OptimizeType type = OptimizeType::MAX;
};
