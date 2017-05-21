#include "MainWindow.hpp"
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
    return ui->text_objFun->text();
}

QString MainWindow::getTextFromTextConFun() const
{
    return ui->text_conFun->toPlainText();
}

QString MainWindow::getOptymalizationType() const
{
    return ui->comb_type->currentText();
}

void MainWindow::setTextToDispLogger(QString text)
{
    ui->disp_logger->append(text);
    ui->disp_logger->append("-----------------------------------------------------------");
}

void MainWindow::fillTreeView(const std::shared_ptr<NodeOfSolution>& node)
{
    m_bAndBDisp.fillTreeView(node);
}

float MainWindow::getPrecision() const
{
    return ui->text_precision->text().toFloat();
}

void MainWindow::closeAplication()
{
    QApplication::exit();
}

void MainWindow::loadOptymalizationType(QTextStream& sFile)
{
    if (!sFile.atEnd())
    {
        QString objFun = sFile.readLine();
        int index = ui->comb_type->findText(objFun);
        ui->comb_type->setCurrentIndex(index);
    }
}

void MainWindow::loadPrecison(QTextStream& sFile)
{
    if (!sFile.atEnd())
    {
        QString precision = sFile.readLine();
        ui->text_precision->setText(precision);
    }
}

void MainWindow::loadObjFun(QTextStream &sFile)
{
    if (!sFile.atEnd())
    {
        QString objFun = sFile.readLine();
        ui->text_objFun->setText(objFun);
    }
}

void MainWindow::loadConstraints(QTextStream &sFile)
{
    QString consFun;
    while (!sFile.atEnd())
    {
        consFun += (sFile.readLine() + "\n");
    }
    ui->text_conFun->setPlainText(consFun);
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

    loadOptymalizationType(sFile);
    loadPrecison(sFile);
    loadObjFun(sFile);
    loadConstraints(sFile);
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
    sFile << getOptymalizationType() << "\n";
    sFile << getPrecision() << "\n";
    sFile << getTextFromTextObjFun() << "\n";
    sFile << getTextFromTextConFun();
    file.close();
}

void MainWindow::aboutApplication()
{
    QMessageBox::information(this, QString("Twórcy"), QString("Paweł Barań\nMateusz Malon"));
}

void MainWindow::badData()
{
    QMessageBox::information(this, QString("Blad"), QString("Wprowadź poprawne dane"));
}

void MainWindow::on_btn_show_clicked()
{
    m_bAndBDisp.showMaximized();
}
