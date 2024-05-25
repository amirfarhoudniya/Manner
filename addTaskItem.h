#ifndef ADDTASKITEM_H
#define ADDTASKITEM_H

#include <QWidget>
#include <QSqlQuery>
#include <QDate>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QLabel>

#include "dataBase.h"

namespace Ui {
class addTaskItem;
}

class addTaskItem : public QWidget
{
    Q_OBJECT

public:
    explicit addTaskItem(QWidget *parent = nullptr);
    QString taskText ;
    ~addTaskItem();

signals :
    void taskAdded() ;

private slots:
    void on_add_pushButton_clicked();

private:
    Ui::addTaskItem *ui;

};

#endif // addTaskItem
