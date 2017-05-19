#include "Controler.hpp"
#include <LinearProblem.hpp>
#include <QDebug>
#include <QString>
#include "EquationValidator.hpp"

namespace
{
OptimizeType convertQStringToOptimizeType(QString type)
{
    if (type == "MAX")
        return OptimizeType::MAX;
    return OptimizeType::MIN;
}

bool isEquationsValid(QString objfun, QString constraints)
{
    return EquationValidator::isObjFunValid(objfun.toStdString()) &&
           EquationValidator::isConstraintsValid(constraints.toStdString());
}
}
std::shared_ptr<LinearProblem> Controler::createLinearProblem()
{
    std::shared_ptr<LinearProblem> asd =
        std::make_shared<LinearProblem>(convertQStringToOptimizeType(m_view.getOptymalizationType()));
    asd->SetObjFunc(m_eqManager->getObjectiveFunction());
    asd->setConstrains(m_eqManager->getConstraintFunctions());

    return asd;
}

void Controler::showOptimalResult(std::vector<std::shared_ptr<LinearProblemSolution>> optimalResult)
{
    QString toDisplay;
    for (const auto& result : optimalResult)
    {
        toDisplay += result->getAsString();
    }
    m_view.setTextToDispLogger(toDisplay);
}

void Controler::calculate()
{
    auto objfun = m_view.getTextFromTextObjFun();
    auto constraints = m_view.getTextFromTextConFun();
    if (!isEquationsValid(objfun, constraints))
    {
        m_view.badData();
        return;
    }
    auto text = objfun + "=0\n" + constraints;
    try
    {
        m_eqManager->convertToEquations(text.toStdString());
    }
    catch (std::exception ex)
    {
        m_view.badData();
        return;
    }
    std::shared_ptr<LinearProblem> linProblem = createLinearProblem();
    BranchAndBoundSolver solver(linProblem);
    solver.setPrecision(m_view.getPrecision());
    auto optimalResult = solver.Solve();
    showOptimalResult(optimalResult);
    m_view.fillTreeView(solver.GetRoot());
}
