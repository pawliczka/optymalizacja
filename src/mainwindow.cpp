#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QPushButton* MainWindow::getCalcBtn() const
{
    return ui->btn_calc;
}

QString MainWindow::getTextFromTextObjFun() const
{
    return ui->text_objFun->toPlainText();
}

QString MainWindow::getTextFromTextConFun() const
{
    return ui->text_conFun->toPlainText();
}
void MainWindow::setTextToDispLogger(QString text)
{
    ui->disp_logger->setPlainText(text);
}
