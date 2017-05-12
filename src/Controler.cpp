#include "Controler.hpp"
#include <LinearProblem.hpp>
#include <QDebug>
#include <QString>

std::shared_ptr<LinearProblem> Controler::createLinearProblem()
{
    std::shared_ptr<LinearProblem> asd = std::make_shared<LinearProblem>(OptimizeType::MAX);
    asd->SetObjFunc(m_eqManager->getObjectiveFunction());
    asd->setConstrains(m_eqManager->getConstraintFunctions());

    return asd;
}

void Controler::prepareEquations()
{
    auto objfun = m_view.getTextFromTextObjFun();
    auto constraints = m_view.getTextFromTextConFun();
    auto text = objfun + "=0\n" + constraints;
    m_eqManager->convertToEquations(text.toStdString());
}

void Controler::showOptimalResult(std::vector<std::shared_ptr<LinearProblemSolution>> optimalResult)
{
    QString toDisplay;
    for (const auto& result: optimalResult)
    {
        toDisplay += result->getAsString();
    }
    m_view.setTextToDispLogger(toDisplay);
}

void Controler::calculate()
{
    prepareEquations();
    std::shared_ptr<LinearProblem> linProblem = createLinearProblem();
    BranchAndBoundSolver solver(linProblem);
    auto optimalResult = solver.Solve();
    showOptimalResult(optimalResult);
    m_view.fillTreeView(solver.GetRoot());
}
