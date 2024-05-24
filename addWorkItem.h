#ifndef ADDWORKITEM_H
#define ADDWORKITEM_H

#include <QWidget>
#include <QSqlQuery>

namespace Ui {
class addWorkItem;
}

class addWorkItem : public QWidget
{
    Q_OBJECT

public:
    explicit addWorkItem(QWidget *parent = nullptr);
    ~addWorkItem();

private slots:
    void on_add_pushButton_clicked();

private:
    Ui::addWorkItem *ui;
};

#endif // ADDWORKITEM_H
