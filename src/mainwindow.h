#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QString>

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();
    QPushButton* getCalcBtn() const;
    QString getTextFromTextObjFun() const;
    QString getTextFromTextConFun() const;
    void setTextToDispLogger(QString text);

private:
    Ui::MainWindow* ui;
};

#endif // MAINWINDOW_H
