#include "BranchAndBoundTreeDisplayer.hpp"
#include "ui_branchandboundtreedisplayer.h"

BranchAndBoundTreeDisplayer::BranchAndBoundTreeDisplayer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BranchAndBoundTreeDisplayer)
{
    ui->setupUi(this);
}

BranchAndBoundTreeDisplayer::~BranchAndBoundTreeDisplayer()
{
    delete ui;
}
