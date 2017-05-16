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
    void fillTreeView(const std::shared_ptr<NodeOfSolution> &node);

private slots:

    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

private:
    void setColumnNames(const std::shared_ptr<NodeOfSolution> &node);
    void fillTree(const std::shared_ptr<NodeOfSolution>& node, QTreeWidgetItem* parent = nullptr);
    QTreeWidgetItem *addTreeElement(QTreeWidgetItem *parent, const std::shared_ptr<NodeOfSolution> &node);

    Ui::BranchAndBoundTreeDisplayer* ui;
    QTreeWidgetItem *createNewTreeItem(QTreeWidgetItem* parent);
    void fillTreeItem(QTreeWidgetItem* treeItem, const std::shared_ptr<NodeOfSolution>& node);
    void resizeColumnsToContents();
    void setDataToTreeItem(QTreeWidgetItem* treeItem, const std::shared_ptr<NodeOfSolution>& node);
    QIcon getIconBasedOnSolutionType(const std::shared_ptr<NodeOfSolution> &node);
    void setRowColor(QTreeWidgetItem *treeItem, const std::shared_ptr<NodeOfSolution> &node);
    void setVariableValues(QTreeWidgetItem* treeItem, const std::shared_ptr<NodeOfSolution>& node);
};
