#include <QApplication>
#include <QWidget>
#include <iostream>
#include "mainwindow.h"
#include <Eigen/Dense>
#include <boost/math/tools/polynomial.hpp>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    mainWindow w;
    w.show();
    boost::math::tools::polynomial<double> const b{{-2.0, 1.0}};
    std::cout << b;
   // return a.exec();
}
