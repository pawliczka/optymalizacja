#ifndef BRANCHANDBOUNDTREEDISPLAYER_HPP
#define BRANCHANDBOUNDTREEDISPLAYER_HPP

#include <QDialog>

namespace Ui {
class BranchAndBoundTreeDisplayer;
}

class BranchAndBoundTreeDisplayer : public QDialog
{
    Q_OBJECT

public:
    explicit BranchAndBoundTreeDisplayer(QWidget *parent = 0);
    ~BranchAndBoundTreeDisplayer();

private:
    Ui::BranchAndBoundTreeDisplayer *ui;
};

#endif // BRANCHANDBOUNDTREEDISPLAYER_HPP
