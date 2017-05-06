#include <QApplication>
#include <QWidget>
#include <iostream>
#include "Controler.hpp"
#include "BranchAndBoundTreeDisplayer.hpp"


int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    MainWindow view;
    BranchAndBoundTreeDisplayer asd;
    asd.show();
    Controler contr(view);
    view.show();
    return a.exec();
}
