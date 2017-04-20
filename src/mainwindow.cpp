#include "mainwindow.h"
#include "ui_mainwindow.h"

mainWindow::mainWindow(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::mainWindow)
{
    ui->setupUi(this);
    connect(ui->btn_go, &QPushButton::clicked, this, &mainWindow::foo);
}

mainWindow::~mainWindow()
{
    delete ui;
}

void mainWindow::foo()
{
    auto entered_text = ui->text_edit->toPlainText();
    ui->text_display->setText(entered_text);
}
