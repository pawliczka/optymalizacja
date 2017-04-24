#pragma once
#include "mainwindow.h"
#include <QObject>
#include <QPushButton>

class Controler : public QObject
{
public:
    Controler(mainWindow& view)
        : m_view(view)
    {
        connect(m_view.getPushBtn(), &QPushButton::clicked, this, &Controler::foo);
    }

    slots public:
    void foo();

private:
    mainWindow& m_view;
};
