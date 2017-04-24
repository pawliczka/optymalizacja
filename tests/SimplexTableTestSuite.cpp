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
        {{-2, 1,}, ComparisonOperator::GreaterEqual},
        {{-3, 0, 1}, ComparisonOperator::GreaterEqual},
        {{-2, 1, 1}, ComparisonOperator::GreaterEqual}};
    //sstd::cout << equations[0] << std::endl << equations[1] << std::endl << equations[2] << std::endl;
    SimplexTable sut(equations);
}
