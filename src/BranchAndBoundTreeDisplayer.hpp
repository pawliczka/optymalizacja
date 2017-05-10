#pragma once
#include <QDialog>
#include <QTreeWidget>

namespace Ui
{
class BranchAndBoundTreeDisplayer;
}

class BranchAndBoundTreeDisplayer : public QDialog
{
    Q_OBJECT

public:
    explicit BranchAndBoundTreeDisplayer(QWidget* parent = 0);
    ~BranchAndBoundTreeDisplayer();

private slots:

    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

private:
    void addTreeRoot(QString name, QString description);
    QTreeWidgetItem *addTreeChild(QTreeWidgetItem* parent, QString name, QString description);

    Ui::BranchAndBoundTreeDisplayer* ui;
};
