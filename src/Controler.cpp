#include "Controler.hpp"
#include <QString>
#include <QDebug>

void Controler::calculate()
{
    auto objfun = m_view.getTextFromTextObjFun();
    auto constraints = m_view.getTextFromTextConFun();
    auto text = objfun + "=0\n" + constraints;
    m_eqManager->convertToEquations(text.toStdString());
    auto text1 = m_eqManager->convertEquationsToString();
    auto asd = QString::fromStdString(text1);
    m_view.setTextToDispLogger(asd);
}
