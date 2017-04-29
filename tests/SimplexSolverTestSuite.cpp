#include "SimplexSolver.hpp"
#include "SimplexTable.hpp"
#include <gmock/gmock.h>
#include <vector>
#include <iostream>



class SimplexSolverTestSuite : public testing::Test
{
};


TEST_F(SimplexSolverTestSuite, ExampleFromYouTube)
{
    std::vector<Equation> equations = {
        {{-5480, 420, 760}, ComparisonOperator::GreaterEqual},
        {{-61, 9, 5}, ComparisonOperator::GreaterEqual}};

    Equation objectiveFunction = {{0, 340, 404}, ComparisonOperator::Equal};
    //sstd::cout << equations[0] << std::endl << equations[1] << std::endl << equations[2] << std::endl;
    SimplexSolver sut(equations);
    sut.simplexTable.SetCoefficientsOfObjectiveFunction(objectiveFunction);
    sut.simplexTable.PrintSimplexTable();
    sut.simplexTable.ExecuteSimplexMethod();

}


TEST_F(SimplexSolverTestSuite, ExampleFromSzlachcicLecture)
{
    std::vector<Equation> equations = {
        {{-5, 1, 1}, ComparisonOperator::GreaterEqual},
        {{0, -1, 1}, ComparisonOperator::GreaterEqual},
        {{-21, 6, 2}, ComparisonOperator::GreaterEqual}};

    Equation objectiveFunction = {{0, 2, 1}, ComparisonOperator::Equal};
    //sstd::cout << equations[0] << std::endl << equations[1] << std::endl << equations[2] << std::endl;
    SimplexSolver sut(equations);
    sut.simplexTable.SetCoefficientsOfObjectiveFunction(objectiveFunction);
    sut.simplexTable.PrintSimplexTable();
    sut.simplexTable.ExecuteSimplexMethod();

}
