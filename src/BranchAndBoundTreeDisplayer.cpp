#include "BranchAndBoundTreeDisplayer.hpp"
#include "ui_branchandboundtreedisplayer.h"

BranchAndBoundTreeDisplayer::BranchAndBoundTreeDisplayer(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::BranchAndBoundTreeDisplayer)
{
    ui->setupUi(this);
    ui->treeWidget->setColumnCount(3);
    auto asd = addTreeElement("a", "b");
    addTreeElement("2", "3", asd);
}

BranchAndBoundTreeDisplayer::~BranchAndBoundTreeDisplayer()
{
    delete ui;
}

QTreeWidgetItem* BranchAndBoundTreeDisplayer::createNewTreeItem(QTreeWidgetItem* parent)
{
    if (parent == nullptr)
        return new QTreeWidgetItem(ui->treeWidget);
    return new QTreeWidgetItem();
}

QTreeWidgetItem* BranchAndBoundTreeDisplayer::addTreeElement(QString name, QString description, QTreeWidgetItem* parent)
{
    QTreeWidgetItem* treeItem = createNewTreeItem(parent);

    treeItem->setText(0, name);
    treeItem->setText(1, description);
    treeItem->setIcon(0, QIcon(":/new/images/exit.png"));
    treeItem->setExpanded(true);

    parent->addChild(treeItem);
    return treeItem;
}

void BranchAndBoundTreeDisplayer::on_treeWidget_itemClicked(QTreeWidgetItem* item, int column)
{
    ui->textBrowser->setPlainText(item->text(column));
}
