#ifndef ADDTASKITEM_H
#define ADDTASKITEM_H

#include <QWidget>
#include <QSqlQuery>
#include <QDate>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QLabel>
#include <QKeyEvent>

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
    void callPopUpNotifier(QString _message) ;

private slots:
    void on_add_pushButton_clicked();
    void keyPressEvent(QKeyEvent *event);

    void on_lineEdit_textEdited(const QString &arg1);

private:
    Ui::addTaskItem *ui;

};

#endif // addTaskItem
