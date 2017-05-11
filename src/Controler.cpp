#include "Controler.hpp"
#include <QString>
#include <QDebug>
#include <LinearProblem.hpp>


void Controler::calculate()
{
    auto objfun = m_view.getTextFromTextObjFun();
    auto constraints = m_view.getTextFromTextConFun();
    auto text = objfun + "=0\n" + constraints;
    m_eqManager->convertToEquations(text.toStdString());
    std::shared_ptr<LinearProblem> asd = std::make_shared<LinearProblem>(OptimizeType::MAX);
    asd->SetObjFunc(m_eqManager->getObjectiveFunction());
    asd->setConstrains(m_eqManager->getConstraintFunctions());
    BranchAndBoundSolver asd1(asd);
    auto asdasdasd = asd1.Solve();
    m_view.fillTreeView(asd1.GetRoot());
}
