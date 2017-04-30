#pragma once
#include "mainwindow.h"
#include <QObject>
#include <QPushButton>
#include <memory>
#include "EquationManager.hpp"

class Controler : public QObject
{
public:
    Controler(MainWindow& view)
        : m_view(view)
    {
        connect(m_view.getCalcBtn(), &QPushButton::clicked, this, &Controler::foo);
    }

    slots public:
    void foo();

private:
    MainWindow& m_view;
    std::shared_ptr<EquationManager> m_eqManager = std::make_shared<EquationManager>();
};
