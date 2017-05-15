#include "BranchAndBoundTreeDisplayer.hpp"
#include "ui_branchandboundtreedisplayer.h"
#include <iostream>
#include <QVariant>

Q_DECLARE_SMART_POINTER_METATYPE(std::shared_ptr)
Q_DECLARE_METATYPE(std::shared_ptr<NodeOfSolution>)

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

void BranchAndBoundTreeDisplayer::resizeColumnsToContents()
{
    for (int i = 0; i < ui->treeWidget->columnCount(); i++)
    {
        ui->treeWidget->resizeColumnToContents(i);
    }
}

void BranchAndBoundTreeDisplayer::fillTreeView(const std::shared_ptr<NodeOfSolution>& node)
{
    if (node == nullptr)
        return;
    ui->treeWidget->clear();
    ui->textBrowser->clear();
    setColumnNames(node);
    fillTree(node);
    resizeColumnsToContents();
}

QTreeWidgetItem* BranchAndBoundTreeDisplayer::createNewTreeItem(QTreeWidgetItem* parent)
{
    if (parent == nullptr)
        return new QTreeWidgetItem(ui->treeWidget);
    return new QTreeWidgetItem();
}

void BranchAndBoundTreeDisplayer::setDataToTreeItem(
    QTreeWidgetItem* treeItem, const std::shared_ptr<NodeOfSolution>& node)
{
    QVariant var = QVariant::fromValue(node);
    treeItem->setData(0, Qt::UserRole, var);
}

void BranchAndBoundTreeDisplayer::fillTreeItem(QTreeWidgetItem* treeItem, const std::shared_ptr<NodeOfSolution>& node)
{
    for (int i = 1; i <= static_cast<int>(node->m_solution->VariableValues.size()); i++)
    {
        treeItem->setText(i + 1, QString::number(node->m_solution->VariableValues[i - 1]));
    }
    treeItem->setText(1, QString::fromStdString(node->m_additionalConstrain.toString()));
    treeItem->setIcon(0, getIconBasedOnSolutionType(node));
    setDataToTreeItem(treeItem, node);
}

QIcon BranchAndBoundTreeDisplayer::getIconBasedOnSolutionType(const std::shared_ptr<NodeOfSolution>& node)
{
    if (node->isOptimal)
        return QIcon(":/new/images/green_tick.png");
    return QIcon(":/new/images/exit.png");
}

QTreeWidgetItem* BranchAndBoundTreeDisplayer::addTreeElement(
    QTreeWidgetItem* parent, const std::shared_ptr<NodeOfSolution>& node)
{
    QTreeWidgetItem* treeItem = createNewTreeItem(parent);

    fillTreeItem(treeItem, node);

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
    fillTree(node->m_lowerBoundNode, child);
    fillTree(node->m_upperBoundNode, child);
}

void BranchAndBoundTreeDisplayer::on_treeWidget_itemClicked(QTreeWidgetItem* item, int column)
{
    auto spint2 = item->data(0, Qt::UserRole).value<std::shared_ptr<NodeOfSolution>>();

    ui->textBrowser->setPlainText(spint2->m_solution->getAsString());
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
