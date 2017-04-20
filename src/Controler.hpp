#pragma once
#include "mainwindow.h"
#include "View.hpp"

class Controler
{
public:
    Controler(View& view)
        : m_view(view)
    {
        m_view.show();
    }

private:
    View& m_view;
};
