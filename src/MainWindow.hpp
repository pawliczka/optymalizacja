#pragma once
#include <QMainWindow>
#include <QPushButton>
#include <QString>
#include <BranchAndBoundTreeDisplayer.hpp>

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
    void fillTreeView(const std::shared_ptr<NodeOfSolution> &node);
    void badData();

private:
    Ui::MainWindow* ui;
    BranchAndBoundTreeDisplayer m_bAndBDisp;
    QString m_fileName;

private slots:
    void aboutApplication();
    void closeAplication();
    void openFile();
    void saveFileAs();
    void saveFile();
    void newFile();
    void on_btn_show_clicked();
};
