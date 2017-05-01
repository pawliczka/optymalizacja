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

    EXPECT_EQ(SimplexStatus::STATUS_SOLVED, simplex.State.Status);
    EXPECT_EQ(LinProblemCase::ONE_SOLUTION, simplex.State.Case);
    EXPECT_DOUBLE_EQ(4,result->VariableValues[0]);
    EXPECT_DOUBLE_EQ(5,result->VariableValues[1]);
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
    std::shared_ptr<LinearProblemSolution> result = simplex.Solve();

    EXPECT_EQ(SimplexStatus::STATUS_SOLVED, simplex.State.Status);
    EXPECT_EQ(LinProblemCase::ONE_SOLUTION, simplex.State.Case);
    EXPECT_DOUBLE_EQ(32./7.,result->VariableValues[0]);
    EXPECT_DOUBLE_EQ(18./7.,result->VariableValues[1]);
    EXPECT_DOUBLE_EQ(118./7., result->ObjFuncValue);
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
    std::shared_ptr<LinearProblemSolution> result = simplex.Solve();

    EXPECT_EQ(SimplexStatus::STATUS_SOLVED, simplex.State.Status);
    EXPECT_EQ(LinProblemCase::ONE_SOLUTION, simplex.State.Case);
    EXPECT_DOUBLE_EQ(11./4.,result->VariableValues[0]);
    EXPECT_DOUBLE_EQ(9./4.,result->VariableValues[1]);
    EXPECT_DOUBLE_EQ(31./4., result->ObjFuncValue);
}

TEST_F(SimplexTestSuite, ExampleFromSzlachcicLecture1)
{
    LinearProblem  linproblem(OptimizeType::MAX);

    std::vector<Equation> constrains = {
        {{2, 2, 1}, ComparisonOperator::GreaterEqual},
        {{3, -1, 1}, ComparisonOperator::LessEqual},
        {{6, 1, 1}, ComparisonOperator::LessEqual}};

    Equation objectiveFunction = {{0, 1, 6}, ComparisonOperator::Equal};

    linproblem.SetObjFunc(objectiveFunction);
    linproblem.setConstrains(constrains);

    Simplex simplex(linproblem);
    std::shared_ptr<LinearProblemSolution> result = simplex.Solve();

    EXPECT_EQ(SimplexStatus::STATUS_SOLVED, simplex.State.Status);
    EXPECT_EQ(LinProblemCase::ONE_SOLUTION, simplex.State.Case);
    EXPECT_DOUBLE_EQ(1.5, result->VariableValues[0]);
    EXPECT_DOUBLE_EQ(4.5, result->VariableValues[1]);
    EXPECT_DOUBLE_EQ(28.5, result->ObjFuncValue);
}

TEST_F(SimplexTestSuite, ExampleFromSzlachcicLecture2)
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
    std::shared_ptr<LinearProblemSolution> result = simplex.Solve();

    EXPECT_EQ(SimplexStatus::STATUS_SOLVED, simplex.State.Status);
    EXPECT_EQ(LinProblemCase::ONE_SOLUTION, simplex.State.Case);
    EXPECT_DOUBLE_EQ(4, result->VariableValues[0]);
    EXPECT_DOUBLE_EQ(0, result->VariableValues[1]);
    EXPECT_DOUBLE_EQ(4, result->ObjFuncValue);
}

TEST_F(SimplexTestSuite, ExampleFromSzlachcicLecture3)
{
    LinearProblem  linproblem(OptimizeType::MAX);

    std::vector<Equation> constrains = {
        {{2, -0.5, 2, 1}, ComparisonOperator::LessEqual},
        {{3, -0.5, 2, -1}, ComparisonOperator::GreaterEqual},
        {{2, 0, 1, -1}, ComparisonOperator::LessEqual}};

    Equation objectiveFunction = {{0, 0.5, -1, -1}, ComparisonOperator::Equal};

    linproblem.SetObjFunc(objectiveFunction);
    linproblem.setConstrains(constrains);

    Simplex simplex(linproblem);
    simplex.Solve();
    EXPECT_EQ(SimplexStatus::STATUS_WRONG_TABLE, simplex.State.Status);
    EXPECT_EQ(LinProblemCase::INCONSISTENT, simplex.State.Case);
}


TEST_F(SimplexTestSuite, ExampleFromSzlachcicLecture4)
{
    LinearProblem  linproblem(OptimizeType::MAX);

    std::vector<Equation> constrains = {
        {{4, -1, 1}, ComparisonOperator::LessEqual},
        {{6, 2, 1}, ComparisonOperator::LessEqual}};

    Equation objectiveFunction = {{0, 4, 2}, ComparisonOperator::Equal};

    linproblem.SetObjFunc(objectiveFunction);
    linproblem.setConstrains(constrains);

    Simplex simplex(linproblem);
    std::shared_ptr<LinearProblemSolution> result = simplex.Solve();
    EXPECT_EQ(SimplexStatus::STATUS_SOLVED, simplex.State.Status);
    EXPECT_EQ(LinProblemCase::INF_SOLUTIONS_BOUND, simplex.State.Case);
    EXPECT_DOUBLE_EQ(3, result->VariableValues[0]);
    EXPECT_DOUBLE_EQ(0, result->VariableValues[1]);
    EXPECT_DOUBLE_EQ(12, result->ObjFuncValue);
}

TEST_F(SimplexTestSuite, ExampleFromSzlachcicLecture5)
{
    LinearProblem  linproblem(OptimizeType::MAX);

    std::vector<Equation> constrains = {
        {{1, -2, 1}, ComparisonOperator::LessEqual},
        {{4, -1, 2}, ComparisonOperator::LessEqual}};

    Equation objectiveFunction = {{0, -2, 4}, ComparisonOperator::Equal};

    linproblem.SetObjFunc(objectiveFunction);
    linproblem.setConstrains(constrains);

    Simplex simplex(linproblem);
    std::shared_ptr<LinearProblemSolution> result = simplex.Solve();
    EXPECT_EQ(SimplexStatus::STATUS_SOLVED, simplex.State.Status);
    EXPECT_EQ(LinProblemCase::INF_SOLUTIONS_UNBOUND, simplex.State.Case);
    EXPECT_DOUBLE_EQ(2./3., result->VariableValues[0]);
    EXPECT_DOUBLE_EQ(7./3., result->VariableValues[1]);
    EXPECT_DOUBLE_EQ(8, result->ObjFuncValue);
}

TEST_F(SimplexTestSuite, ExampleFromSzlachcicLecture6)
{
    LinearProblem  linproblem(OptimizeType::MAX);

    std::vector<Equation> constrains = {
        {{4, 1, 1}, ComparisonOperator::LessEqual},
        {{-2, 1, -1}, ComparisonOperator::LessEqual}};

    Equation objectiveFunction = {{0, 1, 4}, ComparisonOperator::Equal};

    linproblem.SetObjFunc(objectiveFunction);
    linproblem.setConstrains(constrains);

    Simplex simplex(linproblem);
    std::shared_ptr<LinearProblemSolution> result = simplex.Solve();
    EXPECT_EQ(SimplexStatus::STATUS_SOLVED, simplex.State.Status);
    EXPECT_EQ(LinProblemCase::ONE_SOLUTION, simplex.State.Case);
    EXPECT_DOUBLE_EQ(0, result->VariableValues[0]);
    EXPECT_DOUBLE_EQ(4, result->VariableValues[1]);
    EXPECT_DOUBLE_EQ(16, result->ObjFuncValue);
}
