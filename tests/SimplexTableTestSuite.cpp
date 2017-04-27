#include "SimplexTable.hpp"
#include <gmock/gmock.h>
#include <vector>
#include <iostream>



class SimplexTableTestSuite : public testing::Test
{
};

TEST_F(SimplexTableTestSuite, shouldReturnTwoVariablesWhenReceivingThreeEquationsWithTwoVariables)
{
    //x1 < 2
    //x2 < 3
    //x1+x2 < 4

    std::vector<Equation> equations = {
        {{-2, 1}, ComparisonOperator::GreaterEqual},
        {{-3, 0, 1}, ComparisonOperator::GreaterEqual},
        {{-2, 1, 1}, ComparisonOperator::GreaterEqual}};

    Equation objectiveFunction = {{0, 32, 21}, ComparisonOperator::Equal};
    //sstd::cout << equations[0] << std::endl << equations[1] << std::endl << equations[2] << std::endl;
    SimplexTable sut(equations);
    sut.SetCoefficientsOfObjectiveFunction(objectiveFunction);
    sut.PrintSimplexTable();
    sut.ExecuteSimplexMethod();
}

TEST_F(SimplexTableTestSuite, ExampleFromYouTube)
{
    std::vector<Equation> equations = {
        {{-5480, 420, 760}, ComparisonOperator::GreaterEqual},
        {{-61, 9, 5}, ComparisonOperator::GreaterEqual}};

    Equation objectiveFunction = {{0, 340, 404}, ComparisonOperator::Equal};
    //sstd::cout << equations[0] << std::endl << equations[1] << std::endl << equations[2] << std::endl;
    SimplexTable sut(equations);
    sut.SetCoefficientsOfObjectiveFunction(objectiveFunction);
    sut.PrintSimplexTable();
    sut.ExecuteSimplexMethod();

}

TEST_F(SimplexTableTestSuite, ExampleFromYouTube1)
{
    std::vector<Equation> equations = {
        {{-5, 1, 1}, ComparisonOperator::GreaterEqual},
        {{0, -1, 1}, ComparisonOperator::GreaterEqual},
        {{-21, 6, 2}, ComparisonOperator::GreaterEqual}};

    Equation objectiveFunction = {{0, 2, 1}, ComparisonOperator::Equal};
    //sstd::cout << equations[0] << std::endl << equations[1] << std::endl << equations[2] << std::endl;
    SimplexTable sut(equations);
    sut.SetCoefficientsOfObjectiveFunction(objectiveFunction);
    sut.PrintSimplexTable();
    sut.ExecuteSimplexMethod();

}
