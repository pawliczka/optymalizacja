#include "Controler.hpp"
#include <QString>

void Controler::foo()
{
    auto objfun = m_view.getTextFromTextObjFun();
    auto constraints = m_view.getTextFromTextConFun();
    auto text = objfun + "=0\n" + constraints;
    m_eqManager->convertToEquations(text.toStdString());
    auto text1 = m_eqManager->convertEquationsToString();
    m_view.setTextToDispLogger(QString::fromStdString(text1));
}
