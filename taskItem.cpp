#include "taskItem.h"
#include "ui_taskItem.h"

taskItem::taskItem(QWidget *parent )
    : QWidget(parent)
    , ui(new Ui::taskItem)
{
    ui->setupUi(this);

    ui->remove_pushButton->setFixedSize(30 , 30);
    ui->remove_pushButton->setCursor(Qt::PointingHandCursor);
    ui->remove_pushButton->setStyleSheet("border-radius:10px ; background-color: red ; color:black");
}

void taskItem::AddTask(QString _taskText)
{
    ui->checkBox->setText(_taskText);
    taskText = _taskText ;
}

void taskItem::checkTheCheckBox()
{
    ui->checkBox->setChecked(true);
}

taskItem::~taskItem()
{
    delete ui;
}

void taskItem::on_remove_pushButton_clicked()
{
    emit removeTaskItem(taskText);
}


void taskItem::on_checkBox_stateChanged(int arg1)
{
    //change the background color of item
    if(arg1) {
        this->setStyleSheet("background-color:#123524");
    } else {
        this->setStyleSheet("");
    }

    QSqlQuery query ;
    query.prepare("UPDATE tasks SET status ='1' WHERE task = :taskText AND date = :date") ;
    query.bindValue(":taskText" , taskText);
    query.bindValue(":date" , QDate::currentDate().toString("ddMMMMyyyy"));
    query.exec() ;
}

