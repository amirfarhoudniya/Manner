#ifndef TASKITEM_H
#define TASKITEM_H

#include <QWidget>

namespace Ui {
class taskItem;
}

class taskItem : public QWidget
{
    Q_OBJECT

public:
    explicit taskItem(QWidget *parent = nullptr );
    void AddTask(QString _taskText) ;
    ~taskItem();

signals:
    void removeTaskItem(QString _taskText) ;

private slots:
    void on_remove_pushButton_clicked();

private:
    Ui::taskItem *ui;
    QString taskText ;
};

#endif // taskItem
