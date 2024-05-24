#ifndef WORKITEM_H
#define WORKITEM_H

#include <QWidget>

namespace Ui {
class workItem;
}

class workItem : public QWidget
{
    Q_OBJECT

public:
    explicit workItem(QWidget *parent = nullptr);
    ~workItem();

private:
    Ui::workItem *ui;
};

#endif // WORKITEM_H
