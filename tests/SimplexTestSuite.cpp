#include "Simplex.hpp"
#include "LinearProblem.hpp"
#include <gmock/gmock.h>
#include <vector>
#include <iostream>

class SimplexTestSuite : public testing::Test
{
};

TEST_F(SimplexTestSuite, ExampleFromYouTube)
{
    LinearProblem linproblem(OptimizeType::MAX);

    std::vector<Equation> constrains = {
        {{5480, 420, 760}, ComparisonOperator::LessEqual},
        {{61, 9, 5}, ComparisonOperator::LessEqual}};

    Equation objectiveFunction = {{0, 340, 404}, ComparisonOperator::Equal};

    linproblem.SetObjFunc(objectiveFunction);
    linproblem.setConstrains(constrains);

    Simplex simplex(linproblem);

    auto result = simplex.Solve();

    EXPECT_DOUBLE_EQ(3380, result->ObjFuncValue);
}

TEST_F(SimplexTestSuite, ExampleFromYouTube2)
{
    LinearProblem linproblem(OptimizeType::MAX);

    std::vector<Equation> constrains = {
        {{24, 3, 4}, ComparisonOperator::LessEqual},
        {{22, 2, 5}, ComparisonOperator::LessEqual}};

    Equation objectiveFunction = {{0, 2, 3}, ComparisonOperator::Equal};

    linproblem.SetObjFunc(objectiveFunction);
    linproblem.setConstrains(constrains);

    Simplex simplex(linproblem);

    auto result = simplex.Solve();
    EXPECT_DOUBLE_EQ(16.85, result->ObjFuncValue);
}

TEST_F(SimplexTestSuite, ExampleFromSzlachcicLecture)
{
    LinearProblem  linproblem(OptimizeType::MAX);

    std::vector<Equation> constrains = {
        {{5, 1, 1}, ComparisonOperator::LessEqual},
        {{0, -1, 1}, ComparisonOperator::LessEqual},
        {{21, 6, 2}, ComparisonOperator::LessEqual}};

    Equation objectiveFunction = {{0, 2, 1}, ComparisonOperator::Equal};

    linproblem.SetObjFunc(objectiveFunction);
    linproblem.setConstrains(constrains);

    Simplex simplex(linproblem);

    auto result = simplex.Solve();

    EXPECT_DOUBLE_EQ(31./4., result->ObjFuncValue);
}

TEST_F(SimplexTestSuite, ExampleFromSzlachcicLecture2)
{
    LinearProblem  linproblem(OptimizeType::MAX);

    std::vector<Equation> constrains = {
        {{-2, 2, 1}, ComparisonOperator::GreaterEqual},
        {{-3, -1, 1}, ComparisonOperator::LessEqual},
        {{-6, 1, 1}, ComparisonOperator::LessEqual}};

    Equation objectiveFunction = {{0, 1, 6}, ComparisonOperator::Equal};

    linproblem.SetObjFunc(objectiveFunction);
    linproblem.setConstrains(constrains);

    Simplex simplex(linproblem);

    auto result = simplex.Solve();

    EXPECT_DOUBLE_EQ(28.5, result->ObjFuncValue);
}

TEST_F(SimplexTestSuite, sz1)
{
    LinearProblem  linproblem(OptimizeType::MAX);

    std::vector<Equation> constrains = {
        {{3, -2, 1}, ComparisonOperator::LessEqual},
        {{6, 1, 1}, ComparisonOperator::LessEqual},
        {{20, 5, 2}, ComparisonOperator::LessEqual}};

    Equation objectiveFunction = {{0, 1, -1}, ComparisonOperator::Equal};

    linproblem.SetObjFunc(objectiveFunction);
    linproblem.setConstrains(constrains);

    Simplex simplex(linproblem);

    auto result = simplex.Solve();
}

//For original "RAK" implementation:
//TEST_F(SimplexTestSuite, ExampleFromYouTube)
//{
//    LinProblem  linproblem(2, OptimizeType::MAX);

//    Equation objectiveFunction = {{0, 340, 404}, ComparisonOperator::Equal};
//    double constr1[2] = {420, 760};
//    double constr2[2] = {9, 5};


//    linproblem.SetObjFunc(objectiveFunction);
//    linproblem.AddConstr(2, constr1, 5480, ConstrType::LE);
//    linproblem.AddConstr(2, constr2, 61, ConstrType::LE);

//    Simplex simplex(linproblem);

//    auto result = simplex.Solve();

//    EXPECT_DOUBLE_EQ(3380, result->ObjFuncValue);

//}
