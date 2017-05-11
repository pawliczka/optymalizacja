#include "BranchAndBoundTreeDisplayer.hpp"
#include "ui_branchandboundtreedisplayer.h"
#include <iostream>

BranchAndBoundTreeDisplayer::BranchAndBoundTreeDisplayer(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::BranchAndBoundTreeDisplayer)
{
    ui->setupUi(this);
}

BranchAndBoundTreeDisplayer::~BranchAndBoundTreeDisplayer()
{
    delete ui;
}

void BranchAndBoundTreeDisplayer::fillTreeView(const std::shared_ptr<NodeOfSolution>& node)
{
    if (node == nullptr)
        return;
    ui->treeWidget->clear();
    setColumnNames(node);
    fillTree(node);
}

QTreeWidgetItem* BranchAndBoundTreeDisplayer::createNewTreeItem(QTreeWidgetItem* parent)
{
    if (parent == nullptr)
        return new QTreeWidgetItem(ui->treeWidget);
    return new QTreeWidgetItem();
}

QTreeWidgetItem* BranchAndBoundTreeDisplayer::addTreeElement(
    QTreeWidgetItem* parent, const std::shared_ptr<NodeOfSolution>& node)
{
    QTreeWidgetItem* treeItem = createNewTreeItem(parent);

    for (int i = 1; i <= static_cast<int>(node->m_solution->VariableValues.size()); i++)
    {
        treeItem->setText(i + 1, QString::number(node->m_solution->VariableValues[i - 1]));
    }
    treeItem->setIcon(0, QIcon(":/new/images/exit.png"));

    if (parent != nullptr)
        parent->addChild(treeItem);
    treeItem->setExpanded(true);
    return treeItem;
}

void BranchAndBoundTreeDisplayer::fillTree(const std::shared_ptr<NodeOfSolution>& node, QTreeWidgetItem* parent)
{
    if (node == nullptr)
        return;
    auto child = addTreeElement(parent, node);
    fillTree(node->m_idLowerBound, child);
    fillTree(node->m_idUpperBound, child);
}

void BranchAndBoundTreeDisplayer::on_treeWidget_itemClicked(QTreeWidgetItem* item, int column)
{
    ui->textBrowser->setPlainText(item->text(column));
}

void BranchAndBoundTreeDisplayer::setColumnNames(const std::shared_ptr<NodeOfSolution>& node)
{
    QStringList list;
    list << "Status"
         << "Constr";
    for (int i = 1; i <= static_cast<int>(node->m_solution->VariableValues.size()); i++)
    {
        list << ("x" + QString::number(i));
    }
    ui->treeWidget->setHeaderLabels(list);
}
