#include <QApplication>
#include <QWidget>
#include <iostream>
#include "Controler.hpp"


int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    MainWindow view;
    BranchAndBoundTreeViewer asd;
    asd.showMaximized();
    Controler contr(view);
    view.show();
    return a.exec();
}
