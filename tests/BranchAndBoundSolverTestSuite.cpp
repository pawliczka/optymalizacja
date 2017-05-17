#include "BranchAndBoundSolver.hpp"
#include "Simplex.hpp"
#include "LinearProblem.hpp"
#include <gmock/gmock.h>
#include <vector>
#include <iostream>

class BranchAndBoundSolverTestSuite : public testing::Test
{
};

TEST_F(BranchAndBoundSolverTestSuite, BranchAndBoundNotNeeded)
{
    LinearProblem linproblem(OptimizeType::MAX);

    std::vector<Equation> constrains = {
        {{-5480, 420, 760}, ComparisonOperator::LessEqual},
        {{-61, 9, 5}, ComparisonOperator::LessEqual}};

    Equation objectiveFunction = {{0, 340, 404}, ComparisonOperator::Equal};

    linproblem.SetObjFunc(objectiveFunction);
    linproblem.setConstrains(constrains);

    BranchAndBoundSolver sut(std::make_shared<LinearProblem>(linproblem));
    auto solutions = sut.Solve();

    EXPECT_FLOAT_EQ(4,solutions[0]->VariableValues[0]);
    EXPECT_FLOAT_EQ(5,solutions[0]->VariableValues[1]);
    EXPECT_FLOAT_EQ(3380, solutions[0]->ObjFuncValue);
}

TEST_F(BranchAndBoundSolverTestSuite, asd)
{
    LinearProblem linproblem(OptimizeType::MAX);

    std::vector<Equation> constrains = {
        {{-10, 3, 3}, ComparisonOperator::LessEqual}};

    Equation objectiveFunction = {{0, 1, 1}, ComparisonOperator::Equal};

    linproblem.SetObjFunc(objectiveFunction);
    linproblem.setConstrains(constrains);

    BranchAndBoundSolver sut(std::make_shared<LinearProblem>(linproblem));
    auto solutions = sut.Solve();
    EXPECT_FLOAT_EQ(0,solutions[0]->VariableValues[0]);
    EXPECT_FLOAT_EQ(3,solutions[0]->VariableValues[1]);

    EXPECT_FLOAT_EQ(1,solutions[1]->VariableValues[0]);
    EXPECT_FLOAT_EQ(2,solutions[1]->VariableValues[1]);

    EXPECT_FLOAT_EQ(2,solutions[2]->VariableValues[0]);
    EXPECT_FLOAT_EQ(1,solutions[2]->VariableValues[1]);

    EXPECT_FLOAT_EQ(3,solutions[3]->VariableValues[0]);
    EXPECT_FLOAT_EQ(0,solutions[3]->VariableValues[1]);

}

TEST_F(BranchAndBoundSolverTestSuite, asd1)
{
    LinearProblem linproblem(OptimizeType::MAX);

    std::vector<Equation> constrains = {
        {{-10, 3, 3, 1}, ComparisonOperator::LessEqual}};

    Equation objectiveFunction = {{0, 1, 1, 1}, ComparisonOperator::Equal};

    linproblem.SetObjFunc(objectiveFunction);
    linproblem.setConstrains(constrains);

    BranchAndBoundSolver sut(std::make_shared<LinearProblem>(linproblem));
    auto solutions = sut.Solve();

    EXPECT_FLOAT_EQ(0,solutions[0]->VariableValues[0]);
    EXPECT_FLOAT_EQ(0,solutions[0]->VariableValues[1]);
    EXPECT_FLOAT_EQ(10,solutions[0]->VariableValues[2]);
}

//TEST_F(BranchAndBoundSolverTestSuite, asd2)
//{
//    LinearProblem linproblem(OptimizeType::MIN);

//    std::vector<Equation> constrains = {
//         {{-80, 2, 1, 1, 1, 0, 0, 0, 0}, ComparisonOperator::GreaterEqual},
//         {{-150, 0, 2, 1, 1, 3, 2, 1, 0}, ComparisonOperator::GreaterEqual},
//         {{-100, 1, 0, 1, 3, 0, 2, 3, 5}, ComparisonOperator::GreaterEqual}};

//    Equation objectiveFunction = {{0, 1, 1, 1, 1, 1, 1, 1, 1}, ComparisonOperator::Equal};

//    linproblem.SetObjFunc(objectiveFunction);
//    linproblem.setConstrains(constrains);

//    BranchAndBoundSolver sut(std::make_shared<LinearProblem>(linproblem));
//    auto solutions = sut.Solve();

//    std::cout << "Wszystkie rozwiązania: " << std::endl;
//    for(int i = 0; i < solutions.size(); i++)
//        {
//            for(int j = 0; j < solutions[i]->VariableValues.size(); j++)
//            {
//                std::cout << solutions[i]->VariableValues[j] << "      ";
//            }
//            std::cout << std::endl;
//        }
//}
