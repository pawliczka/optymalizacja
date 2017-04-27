#include "Controler.hpp"
#include "EquationManager.hpp"
#include "EquationConventer.hpp"
#include "TermConverter.hpp"
#include <QString>

void Controler::foo()
{
    auto eq = std::make_shared<EquationManager>();
    auto text = m_view.getTextFromTextEdit();
    eq->convertToEquations(text.toStdString());
    auto text1 = eq->convertEquationsToString();
    m_view.setTextInTextDisplay(QString::fromStdString(text1));
}
