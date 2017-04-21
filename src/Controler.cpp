#include "Controler.hpp"

void Controler::foo()
{
    auto text = m_view.getTextFromTextEdit().toStdString();
    m_view.setTextInTextDisplay(text);
}
