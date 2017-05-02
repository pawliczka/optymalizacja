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
    QString getOptymalizationType() const;
    float getPrecision() const;
    void setTextToDispLogger(QString text);

private:
    Ui::MainWindow* ui;
    QString m_fileName;

private slots:
    void aboutApplication();
    void closeAplication();
    void openFile();
    void saveFileAs();
    void saveFile();
    void newFile();
};

#endif // MAINWINDOW_H
