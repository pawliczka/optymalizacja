//#include "SimplexSolver.hpp"
//#include "SimplexTable.hpp"
//#include <gmock/gmock.h>
//#include <vector>
//#include <iostream>



//class SimplexSolverTestSuite : public testing::Test
//{
//};

//TEST_F(SimplexSolverTestSuite, shouldReturnTwoVariablesWhenReceivingThreeEquationsWithTwoVariables)
//{
//    std::vector<Equation> equations = {
//        {{-2, 1}, ComparisonOperator::GreaterEqual},
//        {{-3, 0, 1}, ComparisonOperator::GreaterEqual},
//        {{-2, 1, 1}, ComparisonOperator::GreaterEqual}};

//    Equation objectiveFunction = {{0, 32, 21}, ComparisonOperator::Equal};
//    SimplexSolver sut(equations);
//    sut.setCoefficientsOfObjectiveFunction(objectiveFunction);
//    sut.printSimplexTableWithCalculations();
//    sut.executePrimalSimplexMethod();
//}

//TEST_F(SimplexSolverTestSuite, ExampleFromYouTube)
//{
//    std::vector<Equation> equations = {
//        {{-5480, 420, 760}, ComparisonOperator::GreaterEqual},
//        {{-61, 9, 5}, ComparisonOperator::GreaterEqual}};

//    Equation objectiveFunction = {{0, 340, 404}, ComparisonOperator::Equal};
//    SimplexSolver sut(equations);
//    sut.setCoefficientsOfObjectiveFunction(objectiveFunction);
//    sut.printSimplexTableWithCalculations();
//    sut.executePrimalSimplexMethod();
//}


//TEST_F(SimplexSolverTestSuite, ExampleFromSzlachcicLecture)
//{
//    std::vector<Equation> equations = {
//        {{-5, 1, 1}, ComparisonOperator::GreaterEqual},
//        {{0, -1, 1}, ComparisonOperator::GreaterEqual},
//        {{-21, 6, 2}, ComparisonOperator::GreaterEqual}};

//    Equation objectiveFunction = {{0, 2, 1}, ComparisonOperator::Equal};
//    SimplexSolver sut(equations);
//    sut.setCoefficientsOfObjectiveFunction(objectiveFunction);
//    sut.printSimplexTableWithCalculations();
//    sut.executePrimalSimplexMethod();

//}

//TEST_F(SimplexSolverTestSuite, ExampleFromYouTube2)
//{
//    std::vector<Equation> equations = {
//        {{-24, 3, 4}, ComparisonOperator::GreaterEqual},
//        {{-22, 2, 5}, ComparisonOperator::GreaterEqual}};

//    Equation objectiveFunction = {{0, 2, 3}, ComparisonOperator::Equal};
//    SimplexSolver sut(equations);
//    sut.setCoefficientsOfObjectiveFunction(objectiveFunction);
//    sut.printSimplexTableWithCalculations();
//    sut.executePrimalSimplexMethod();
//}

//TEST_F(SimplexSolverTestSuite, sz1)
//{
//    std::vector<Equation> equations = {
//        {{-3, -2, 1}, ComparisonOperator::GreaterEqual},
//        {{-6, 1, 1}, ComparisonOperator::GreaterEqual},
//        {{-20, 5, 2}, ComparisonOperator::GreaterEqual}};

//    Equation objectiveFunction = {{0, 1, -1}, ComparisonOperator::Equal};
//    SimplexSolver sut(equations);
//    sut.setCoefficientsOfObjectiveFunction(objectiveFunction);
//    sut.printSimplexTableWithCalculations();
//    sut.executePrimalSimplexMethod();
//}
