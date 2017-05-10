#include "BranchAndBoundTreeDisplayer.hpp"
#include "ui_branchandboundtreedisplayer.h"

BranchAndBoundTreeDisplayer::BranchAndBoundTreeDisplayer(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::BranchAndBoundTreeDisplayer)
{
    ui->setupUi(this);
    ui->treeWidget->setColumnCount(3);
    addTreeRoot("a", "b");
}

BranchAndBoundTreeDisplayer::~BranchAndBoundTreeDisplayer()
{
    delete ui;
}

void BranchAndBoundTreeDisplayer::addTreeRoot(QString name, QString description)
{
    QTreeWidgetItem* treeItem = new QTreeWidgetItem(ui->treeWidget);

    treeItem->setText(0, name);
    treeItem->setIcon(0, QIcon(":/new/images/exit.png"));
    treeItem->setText(1, description);
    treeItem->setText(2, description);
    treeItem->setExpanded( true );
    addTreeChild(treeItem, name + "A", "Child_first");
}

QTreeWidgetItem* BranchAndBoundTreeDisplayer::addTreeChild(QTreeWidgetItem* parent, QString name, QString description)
{
    QTreeWidgetItem* treeItem = new QTreeWidgetItem();

    treeItem->setText(0, name);
    treeItem->setText(1, description);
    treeItem->setIcon(0, QIcon(":/new/images/exit.png"));
    treeItem->setExpanded( true );

    parent->addChild(treeItem);
    return treeItem;
}

void BranchAndBoundTreeDisplayer::on_treeWidget_itemClicked(QTreeWidgetItem* item, int column)
{
    ui->textBrowser->setPlainText(item->text(column));
}
