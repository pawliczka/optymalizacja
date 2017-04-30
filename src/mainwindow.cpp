#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(QString("Plc Kalkulator"));
    connect(ui->actionZamknij, &QAction::triggered, this, &MainWindow::closeAplication);
    connect(ui->actionWczytaj, &QAction::triggered, this, &MainWindow::openFile);
    connect(ui->actionTw_rcy, &QAction::triggered, this, &MainWindow::aboutApplication);
    connect(ui->actionZapisz_jako, &QAction::triggered, this, &MainWindow::saveFileAs);
    connect(ui->actionZapisz, &QAction::triggered, this, &MainWindow::saveFile);
    connect(ui->actionNowy, &QAction::triggered, this, &MainWindow::newFile);
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
    QString fileName = QFileDialog::getOpenFileName(this, "Wczytaj plik", "", "Pliki danych (*.data)");
    if (fileName.isEmpty())
        return;
    m_fileName = fileName;
    QFile file(m_fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text))
        return;
    QTextStream sFile(&file);

    if (!sFile.atEnd())
    {
        QString objFun = sFile.readLine();
        ui->text_objFun->setPlainText(objFun);
    }
    QString consFun;
    while (!sFile.atEnd())
    {
        consFun += (sFile.readLine() + "\n");
    }
    ui->text_conFun->setPlainText(consFun);
    setWindowTitle(QString("Plc Kalkulator - ") + m_fileName);
    file.close();
}

void MainWindow::saveFileAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Zapisz plik", "", "Pliki danych (*.data)");
    if (fileName.isEmpty())
        return;
    m_fileName = fileName;
    setWindowTitle(QString("Plc Kalkulator - ") + m_fileName);
    saveFile();
}

void MainWindow::newFile()
{
    ui->text_conFun->clear();
    ui->text_objFun->clear();
    m_fileName = QString("");
    setWindowTitle(QString("Plc Kalkulator"));
}

void MainWindow::saveFile()
{
    if (m_fileName.isEmpty())
        return;
    QFile file(m_fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        qDebug() << "Can not open file to write" << m_fileName;
        return;
    }
    QTextStream sFile(&file);
    sFile << getTextFromTextObjFun() << "\n";
    sFile << getTextFromTextConFun();
    file.close();
}

void MainWindow::aboutApplication()
{
    QMessageBox::information(this, QString("Jebać studia"), QString("i tak to ujebiemy\n"));
}
