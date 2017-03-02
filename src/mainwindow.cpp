#include "mainwindow.h"
#include "ui_mainwindow.h"

mainWindow::mainWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mainWindow)
{
    ui->setupUi(this);
}

mainWindow::~mainWindow()
{
    delete ui;
}
