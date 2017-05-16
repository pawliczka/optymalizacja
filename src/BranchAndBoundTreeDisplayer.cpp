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
    setWindowTitle(QString("Drzewo binarne rozwiazan"));
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
    int i;
    for (i = 1; i <= static_cast<int>(node->m_solution->VariableValues.size()); i++)
    {
        if (node->m_solution->Case == LinearProblemCase::INCONSISTENT ||
            node->m_solution->Case == LinearProblemCase::NO_SOLUTIONS)
        {
            treeItem->setText(i + 1, "-");
        }
        else
        {
            treeItem->setText(i + 1, QString::number(node->m_solution->VariableValues[i - 1]));
        }
    }
    if (node->m_solution->Case == LinearProblemCase::INCONSISTENT ||
        node->m_solution->Case == LinearProblemCase::NO_SOLUTIONS)
    {
        treeItem->setText(i + 1, "-");
    }
    else
    {
        treeItem->setText(i + 1, QString::number(node->m_solution->ObjFuncValue));
    }
    treeItem->setText(1, QString::fromStdString(node->m_additionalConstrain.toString()));
    treeItem->setIcon(0, getIconBasedOnSolutionType(node));
    setRowColor(treeItem, node);
    setDataToTreeItem(treeItem, node);
}

void BranchAndBoundTreeDisplayer::setRowColor(QTreeWidgetItem* treeItem, const std::shared_ptr<NodeOfSolution>& node)
{
    if (node->m_state == StateOfNode::OptimalSolution)
    {
        for (int i = 0; i < treeItem->columnCount(); i++)
            treeItem->setBackground(i, QBrush(Qt::green));
    }
}

QIcon BranchAndBoundTreeDisplayer::getIconBasedOnSolutionType(const std::shared_ptr<NodeOfSolution>& node)
{
    if (node->m_state == StateOfNode::CutOff)
        return QIcon(":/new/images/cut.png");
    if (node->m_state == StateOfNode::OptimalSolution)
        return QIcon(":/new/images/green_tick.png");
    if ((node->m_solution->Case == LinearProblemCase::NO_SOLUTIONS) ||
        (node->m_solution->Case == LinearProblemCase::INCONSISTENT))
        return QIcon(":/new/images/red_cross.png");
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
    ui->treeWidget->setColumnCount(static_cast<int>(node->m_solution->VariableValues.size()) + 2);
    list << "Status"
         << "Ograniczenie";
    ui->treeWidget->setHeaderLabels(list);
    for (int i = 1; i <= static_cast<int>(node->m_solution->VariableValues.size()); i++)
    {
        list << ("x" + QString::number(i));
    }
    list << "Fun celu";
    ui->treeWidget->setHeaderLabels(list);
}
