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
    EXPECT_FLOAT_EQ(4,result->VariableValues[0]);
    EXPECT_FLOAT_EQ(5,result->VariableValues[1]);
    EXPECT_FLOAT_EQ(3380, result->ObjFuncValue);
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
    EXPECT_FLOAT_EQ(32./7.,result->VariableValues[0]);
    EXPECT_FLOAT_EQ(18./7.,result->VariableValues[1]);
    EXPECT_FLOAT_EQ(118./7., result->ObjFuncValue);
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
    EXPECT_FLOAT_EQ(11./4.,result->VariableValues[0]);
    EXPECT_FLOAT_EQ(9./4.,result->VariableValues[1]);
    EXPECT_FLOAT_EQ(31./4., result->ObjFuncValue);
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
    EXPECT_FLOAT_EQ(1.5, result->VariableValues[0]);
    EXPECT_FLOAT_EQ(4.5, result->VariableValues[1]);
    EXPECT_FLOAT_EQ(28.5, result->ObjFuncValue);
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
    EXPECT_FLOAT_EQ(3, result->VariableValues[0]);
    EXPECT_FLOAT_EQ(0, result->VariableValues[1]);
    EXPECT_FLOAT_EQ(12, result->ObjFuncValue);
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
    EXPECT_FLOAT_EQ(2./3., result->VariableValues[0]);
    EXPECT_FLOAT_EQ(7./3., result->VariableValues[1]);
    EXPECT_FLOAT_EQ(8, result->ObjFuncValue);
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
    EXPECT_FLOAT_EQ(0, result->VariableValues[0]);
    EXPECT_FLOAT_EQ(4, result->VariableValues[1]);
    EXPECT_FLOAT_EQ(16, result->ObjFuncValue);
}

TEST_F(SimplexTestSuite, ExampleFromSzlachcicLecture7)
{
    LinearProblem  linproblem(OptimizeType::MIN);

    std::vector<Equation> constrains = {
        {{8, 1, 2}, ComparisonOperator::GreaterEqual},
        {{6, 2, 1}, ComparisonOperator::GreaterEqual},
        {{5, 1, 1}, ComparisonOperator::GreaterEqual}};

    Equation objectiveFunction = {{0, 1, 1}, ComparisonOperator::Equal};

    linproblem.SetObjFunc(objectiveFunction);
    linproblem.setConstrains(constrains);

    Simplex simplex(linproblem);
    std::shared_ptr<LinearProblemSolution> result = simplex.Solve();
    EXPECT_EQ(SimplexStatus::STATUS_SOLVED, simplex.State.Status);
    EXPECT_EQ(LinProblemCase::INF_SOLUTIONS_BOUND, simplex.State.Case);
    EXPECT_FLOAT_EQ(1, result->VariableValues[0]);
    EXPECT_FLOAT_EQ(4, result->VariableValues[1]);
    EXPECT_FLOAT_EQ(5, result->ObjFuncValue);
}

TEST_F(SimplexTestSuite, ExampleFromSzlachcicLecture8)
{
    LinearProblem  linproblem(OptimizeType::MIN);

    std::vector<Equation> constrains = {
        {{2, -1, -1}, ComparisonOperator::GreaterEqual},
        {{1, -1, 1}, ComparisonOperator::GreaterEqual}};

    Equation objectiveFunction = {{0, -1, -1}, ComparisonOperator::Equal};

    linproblem.SetObjFunc(objectiveFunction);
    linproblem.setConstrains(constrains);

    Simplex simplex(linproblem);
    std::shared_ptr<LinearProblemSolution> result = simplex.Solve();
    EXPECT_EQ(SimplexStatus::STATUS_WRONG_TABLE, simplex.State.Status);
    EXPECT_EQ(LinProblemCase::INCONSISTENT, simplex.State.Case);
}

//http://staff.iiar.pwr.wroc.pl/ewa.szlachcic/materialy%20dydaktyczne/air_studia_2_stopnia/liniowe_zadania_testowe.pdf
TEST_F(SimplexTestSuite, ExampleFromSzlachcicExamples1)
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
    EXPECT_FLOAT_EQ(4, result->VariableValues[0]);
    EXPECT_FLOAT_EQ(0, result->VariableValues[1]);
    EXPECT_FLOAT_EQ(4, result->ObjFuncValue);
}

TEST_F(SimplexTestSuite, ExampleFromSzlachcicExamples2)
{
    LinearProblem  linproblem(OptimizeType::MAX);

    std::vector<Equation> constrains = {
        {{3, -2, 1}, ComparisonOperator::LessEqual},
        {{6, 1, 1}, ComparisonOperator::LessEqual},
        {{20, 5, 2}, ComparisonOperator::LessEqual}};

    Equation objectiveFunction = {{0, 1, 1}, ComparisonOperator::Equal};

    linproblem.SetObjFunc(objectiveFunction);
    linproblem.setConstrains(constrains);

    Simplex simplex(linproblem);
    std::shared_ptr<LinearProblemSolution> result = simplex.Solve();

    EXPECT_EQ(SimplexStatus::STATUS_SOLVED, simplex.State.Status);
    EXPECT_EQ(LinProblemCase::INF_SOLUTIONS_BOUND, simplex.State.Case);
    EXPECT_FLOAT_EQ(8./3., result->VariableValues[0]);
    EXPECT_FLOAT_EQ(10./3., result->VariableValues[1]);
    EXPECT_FLOAT_EQ(6, result->ObjFuncValue);
}

TEST_F(SimplexTestSuite, ExampleFromSzlachcicExamples3)
{
    LinearProblem  linproblem(OptimizeType::MAX);

    std::vector<Equation> constrains = {
        {{3, -2, 1}, ComparisonOperator::LessEqual},
        {{6, 1, 1}, ComparisonOperator::LessEqual},
        {{20, 5, 2}, ComparisonOperator::LessEqual}};

    Equation objectiveFunction = {{0, 1, 2}, ComparisonOperator::Equal};

    linproblem.SetObjFunc(objectiveFunction);
    linproblem.setConstrains(constrains);

    Simplex simplex(linproblem);
    std::shared_ptr<LinearProblemSolution> result = simplex.Solve();

    EXPECT_EQ(SimplexStatus::STATUS_SOLVED, simplex.State.Status);
    EXPECT_EQ(LinProblemCase::ONE_SOLUTION, simplex.State.Case);
    EXPECT_FLOAT_EQ(1, result->VariableValues[0]);
    EXPECT_FLOAT_EQ(5, result->VariableValues[1]);
    EXPECT_FLOAT_EQ(11, result->ObjFuncValue);
}

TEST_F(SimplexTestSuite, ExampleFromSzlachcicExamples4)
{
    LinearProblem  linproblem(OptimizeType::MIN);

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
    EXPECT_FLOAT_EQ(1, result->VariableValues[0]);
    EXPECT_FLOAT_EQ(5, result->VariableValues[1]);
    EXPECT_FLOAT_EQ(-4, result->ObjFuncValue);
}

TEST_F(SimplexTestSuite, ExampleFromSzlachcicExamples5)
{
    LinearProblem  linproblem(OptimizeType::MAX);

    std::vector<Equation> constrains = {
        {{2, -2, 1}, ComparisonOperator::GreaterEqual},
        {{2, 1, -2}, ComparisonOperator::GreaterEqual}};

    Equation objectiveFunction = {{0, 1, 2}, ComparisonOperator::Equal};

    linproblem.SetObjFunc(objectiveFunction);
    linproblem.setConstrains(constrains);

    Simplex simplex(linproblem);
    std::shared_ptr<LinearProblemSolution> result = simplex.Solve();
    EXPECT_EQ(SimplexStatus::STATUS_WRONG_TABLE, simplex.State.Status);
    EXPECT_EQ(LinProblemCase::INCONSISTENT, simplex.State.Case);
}

TEST_F(SimplexTestSuite, ExampleFromSzlachcicExamples6)
{
    LinearProblem  linproblem(OptimizeType::MAX);

    std::vector<Equation> constrains = {
        {{2, 1, -1}, ComparisonOperator::LessEqual},
        {{2, -1, -1}, ComparisonOperator::GreaterEqual}};

    Equation objectiveFunction = {{0, 1, 2}, ComparisonOperator::Equal};

    linproblem.SetObjFunc(objectiveFunction);
    linproblem.setConstrains(constrains);

    Simplex simplex(linproblem);
    std::shared_ptr<LinearProblemSolution> result = simplex.Solve();
    EXPECT_EQ(SimplexStatus::STATUS_WRONG_TABLE, simplex.State.Status);
    EXPECT_EQ(LinProblemCase::INCONSISTENT, simplex.State.Case);
}

TEST_F(SimplexTestSuite, ExampleFromSzlachcicExamples7)
{
    LinearProblem  linproblem(OptimizeType::MIN);

    std::vector<Equation> constrains = {
        {{2100, 7, 3, 0}, ComparisonOperator::GreaterEqual},
        {{1200, 0, 1, 2}, ComparisonOperator::GreaterEqual}};

    Equation objectiveFunction = {{0, 0.3, 0.6, 0.2}, ComparisonOperator::Equal};

    linproblem.SetObjFunc(objectiveFunction);
    linproblem.setConstrains(constrains);

    Simplex simplex(linproblem);
    std::shared_ptr<LinearProblemSolution> result = simplex.Solve();

    EXPECT_EQ(SimplexStatus::STATUS_SOLVED, simplex.State.Status);
    EXPECT_EQ(LinProblemCase::ONE_SOLUTION, simplex.State.Case);
    EXPECT_FLOAT_EQ(300, result->VariableValues[0]);
    EXPECT_FLOAT_EQ(0, result->VariableValues[1]);
    EXPECT_FLOAT_EQ(600, result->VariableValues[2]);
    EXPECT_FLOAT_EQ(210, result->ObjFuncValue);
}
