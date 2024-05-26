#ifndef TASKITEM_H
#define TASKITEM_H

#include <QWidget>
#include <QSqlQuery>
#include <QDate>

#include "dataBase.h"

namespace Ui {
class taskItem;
}

class taskItem : public QWidget
{
    Q_OBJECT

public:
    explicit taskItem(QWidget *parent = nullptr );
    void AddTask(QString _taskText) ;
    void checkTheCheckBox();
    ~taskItem();

signals:
    void removeTaskItem(QString _taskText) ;


private slots:
    void on_remove_pushButton_clicked();

    void on_checkBox_stateChanged(int arg1);

private:
    Ui::taskItem *ui;
    QString taskText ;
};

#endif // taskItem
