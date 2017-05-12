#include "Controler.hpp"
#include <QString>
#include <QDebug>
#include <LinearProblem.hpp>


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

void Controler::calculate()
{
    prepareEquations();
    std::shared_ptr<LinearProblem> linProblem = createLinearProblem();
    BranchAndBoundSolver solver(linProblem);
    auto optimalResult = solver.Solve();
    m_view.fillTreeView(solver.GetRoot());
}
