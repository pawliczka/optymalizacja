#include "mainwindow.h"
#include "ui_mainwindow.h"

mainWindow::mainWindow(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::mainWindow)
{
    ui->setupUi(this);
    show();
}

mainWindow::~mainWindow()
{
    delete ui;
}

QPushButton *mainWindow::getPushBtn()
{
    return ui->btn_go;
}

QString mainWindow::getTextFromTextEdit()
{
    return ui->text_edit->toPlainText();
}

void mainWindow::setTextInTextDisplay(std::string text)
{
    ui->text_display->setPlainText(QString::fromStdString(text));
}
