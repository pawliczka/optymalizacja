#include "BranchAndBoundTreeViewer.hpp"
#include "ui_branchandboundtreeviewer.h"

BranchAndBoundTreeViewer::BranchAndBoundTreeViewer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BranchAndBoundTreeViewer)
{
    ui->setupUi(this);
}

BranchAndBoundTreeViewer::~BranchAndBoundTreeViewer()
{
    delete ui;
}
