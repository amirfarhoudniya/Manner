#ifndef ADDWORKITEM_H
#define ADDWORKITEM_H

#include <QWidget>

namespace Ui {
class addWorkItem;
}

class addWorkItem : public QWidget
{
    Q_OBJECT

public:
    explicit addWorkItem(QWidget *parent = nullptr);
    ~addWorkItem();

private:
    Ui::addWorkItem *ui;
};

#endif // ADDWORKITEM_H
