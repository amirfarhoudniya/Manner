#include "taskItem.h"
#include "ui_taskItem.h"

taskItem::taskItem(QWidget *parent )
    : QWidget(parent)
    , ui(new Ui::taskItem)
{
    ui->setupUi(this);

    ui->remove_pushButton->setFixedSize(30 , 30);
    ui->remove_pushButton->setCursor(Qt::PointingHandCursor);
}

void taskItem::AddTask(QString _taskText)
{
    ui->checkBox->setText(_taskText);
    taskText = _taskText ;
}

taskItem::~taskItem()
{
    delete ui;
}

void taskItem::on_remove_pushButton_clicked()
{
    emit removeTaskItem(taskText);
}

