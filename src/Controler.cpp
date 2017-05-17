#include "Controler.hpp"
#include <QString>
#include <QDebug>
#include "LinearProblem.hpp"
#include "BranchAndBoundSolver.hpp"
#include <sstream>

OptimizeType convertQStringToOptimizeType(QString type)
{
    if (type == "MAX")
        return OptimizeType::MAX;
   return OptimizeType::MIN;
}




void Controler::calculate()
{
    auto problemType = m_view.getOptymalizationType();

    LinearProblem linproblem(convertQStringToOptimizeType(problemType));

    auto objfun = m_view.getTextFromTextObjFun();
    auto constraints = m_view.getTextFromTextConFun();
    auto text = objfun + "=0\n" + constraints;
    m_eqManager->convertToEquations(text.toStdString());


    linproblem.SetObjFunc(m_eqManager->getObjectiveFunction());
    linproblem.setConstrains(m_eqManager->getConstraintFunctions());

    BranchAndBoundSolver sut(std::make_shared<LinearProblem>(linproblem));
    auto solutions = sut.Solve();


    std::stringstream stream;
    stream<< "Wszystkie rozwiązania: " << std::endl;
    for(int i = 0; i < solutions.size(); i++)
    {
        for(int j = 0; j < solutions[i]->VariableValues.size(); j++)
        {
            stream << "x_" << j << "=" << solutions[i]->VariableValues[j] << "      ";
        }
        stream << "objFunc=" << solutions[i]->ObjFuncValue;
        stream << std::endl;
    }

    m_view.setTextToDispLogger(QString::fromStdString(stream.str()));
}
