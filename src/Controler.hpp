#pragma once
#include "MainWindow.hpp"
#include "BranchAndBoundTreeViewer.hpp"
#include <QObject>
#include <QPushButton>
#include <memory>
#include "EquationManager.hpp"
#include <BranchAndBoundSolver.hpp>

class Controler : public QObject
{
public:
    Controler(MainWindow& view)
        : m_view(view)
    {
        connect(m_view.getCalcBtn(), &QPushButton::clicked, this, &Controler::calculate);
    }

private slots:
    void calculate();

private:
    void showOptimalResult(std::vector<std::shared_ptr<LinearProblemSolution>> optimalResult);
    std::shared_ptr<LinearProblem> createLinearProblem();

    MainWindow& m_view;
    std::shared_ptr<EquationManager> m_eqManager = std::make_shared<EquationManager>();
};
