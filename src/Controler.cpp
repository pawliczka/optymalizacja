#include "Controler.hpp"
#include "EquationManager.hpp"
#include "EquationConventer.hpp"
#include "TermConverter.hpp"
#include <QString>

void Controler::foo()
{
    auto eq = std::make_shared<EquationManager>();
    auto objfun = m_view.getTextFromTextObjFun();
    auto constraints = m_view.getTextFromTextConFun();
    auto text = objfun + "=0\n" + constraints;
    eq->convertToEquations(text.toStdString());
    auto text1 = eq->convertEquationsToString();
    m_view.setTextToDispLogger(QString::fromStdString(text1));
}
