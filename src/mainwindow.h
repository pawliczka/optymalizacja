#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>

namespace Ui
{
class mainWindow;
}

class mainWindow : public QDialog
{
    Q_OBJECT

public:
    explicit mainWindow(QWidget* parent = 0);
    ~mainWindow();

public slots:
    void foo();

private:
    Ui::mainWindow* ui;
};

#endif // MAINWINDOW_H
