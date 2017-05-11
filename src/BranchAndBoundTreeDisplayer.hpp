#pragma once
#include <QDialog>
#include <QTreeWidget>
#include "NodeOfSolution.hpp"

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
    QTreeWidgetItem *addTreeElement(QString name, QString description, QTreeWidgetItem* parent = nullptr);

    Ui::BranchAndBoundTreeDisplayer* ui;
    QTreeWidgetItem *createNewTreeItem(QTreeWidgetItem* parent);
};
