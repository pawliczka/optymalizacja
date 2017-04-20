#include <QApplication>
#include <QWidget>
#include <iostream>
#include "Controler.hpp"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    View view;
    Controler contr(view);
    return a.exec();
}
