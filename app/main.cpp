#include <QApplication>
#include <QWidget>
#include <iostream>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    QWidget w;
    w.show();
    return a.exec();
}
