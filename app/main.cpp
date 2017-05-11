#include <QApplication>
#include <QWidget>
#include <iostream>
#include "Controler.hpp"
#include "BranchAndBoundTreeDisplayer.hpp"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    MainWindow view;
    BranchAndBoundTreeDisplayer asd;
    std::shared_ptr<NodeOfSolution> firstNode = std::make_shared<NodeOfSolution>(nullptr,1);
    firstNode->m_Id = 1;
    firstNode->isOptimal = false;
    firstNode->m_solution = std::make_shared<LinearProblemSolution>(3);
    firstNode->m_solution->ObjFuncValue = 10;
    firstNode->m_solution->VariableValues = {10.3,1,1};
    firstNode->m_solution->Case = LinearProblemCase::ONE_SOLUTION;

    std::shared_ptr<NodeOfSolution> secoundNode = std::make_shared<NodeOfSolution>(nullptr,2);
    secoundNode->m_Id = 2;
    secoundNode->isOptimal = false;
    secoundNode->m_solution = std::make_shared<LinearProblemSolution>(3);
    secoundNode->m_solution->ObjFuncValue = 9;
    secoundNode->m_solution->VariableValues = {10,1.3,1};
    secoundNode->m_solution->Case = LinearProblemCase::ONE_SOLUTION;

    std::shared_ptr<NodeOfSolution> thirdNode = std::make_shared<NodeOfSolution>(nullptr,3);
    thirdNode->isOptimal = true;
    thirdNode->m_solution = std::make_shared<LinearProblemSolution>(3);
    thirdNode->m_solution->ObjFuncValue = 11;
    thirdNode->m_solution->VariableValues = {4,5,1};
    thirdNode->m_solution->Case = LinearProblemCase::ONE_SOLUTION;

    std::shared_ptr<NodeOfSolution> fourthNode = std::make_shared<NodeOfSolution>(nullptr,4);
    fourthNode->isOptimal = false;
    fourthNode->m_solution = std::make_shared<LinearProblemSolution>(3);
    fourthNode->m_solution->ObjFuncValue = 12;
    fourthNode->m_solution->VariableValues = {5,10,1};
    fourthNode->m_solution->Case = LinearProblemCase::ONE_SOLUTION;

    firstNode->m_idLowerBound = secoundNode;
    firstNode->m_idUpperBound = thirdNode;
    thirdNode->m_idLowerBound = fourthNode;

    asd.fillTreeView(firstNode);
    asd.showMaximized();
    Controler contr(view);
    //view.show();
    return a.exec();
}
