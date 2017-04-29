#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionZamknij, &QAction::triggered, this, &MainWindow::closeAplication);
    connect(ui->actionWczytaj, &QAction::triggered, this, &MainWindow::openFile);
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

void MainWindow::closeAplication()
{
    QApplication::exit();
}

void MainWindow::openFile()
{
    fileName = QFileDialog::getOpenFileName(this, "Wczytaj plik", "", "Pliki danych (*.data)");
    qDebug() << fileName;
}
