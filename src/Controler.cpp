#include "Controler.hpp"

void Controler::foo()
{
    auto text = m_view.getTextFromTextEdit();
    m_view.setTextInTextDisplay(text);
}
