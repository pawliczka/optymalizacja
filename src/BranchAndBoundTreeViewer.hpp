#ifndef BRANCHANDBOUNDTREEVIEWER_HPP
#define BRANCHANDBOUNDTREEVIEWER_HPP

#include <QWidget>

namespace Ui {
class BranchAndBoundTreeViewer;
}

class BranchAndBoundTreeViewer : public QWidget
{
    Q_OBJECT

public:
    explicit BranchAndBoundTreeViewer(QWidget *parent = 0);
    ~BranchAndBoundTreeViewer();

private:
    Ui::BranchAndBoundTreeViewer *ui;
};

#endif // BRANCHANDBOUNDTREEVIEWER_HPP
