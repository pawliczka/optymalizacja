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
    // QTreeWidgetItem(QTreeWidget * parent, int type = Type)
    QTreeWidgetItem* treeItem = new QTreeWidgetItem(ui->treeWidget);

    // QTreeWidgetItem::setText(int column, const QString & text)
    treeItem->setText(0, name);
    treeItem->setText(1, description);
    treeItem->setText(2, description);
    addTreeChild(treeItem, name + "A", "Child_first");
}

QTreeWidgetItem* BranchAndBoundTreeDisplayer::addTreeChild(QTreeWidgetItem* parent, QString name, QString description)
{
    // QTreeWidgetItem(QTreeWidget * parent, int type = Type)
    QTreeWidgetItem* treeItem = new QTreeWidgetItem();

    // QTreeWidgetItem::setText(int column, const QString & text)
    treeItem->setText(0, name);
    treeItem->setText(1, description);

    // QTreeWidgetItem::addChild(QTreeWidgetItem * child)
    parent->addChild(treeItem);
    return treeItem;
}

void BranchAndBoundTreeDisplayer::on_treeWidget_itemClicked(QTreeWidgetItem* item, int column)
{
    ui->textBrowser->setPlainText(item->text(column));
}
