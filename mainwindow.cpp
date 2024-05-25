#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //lable's text
    ui->dayInWeek_label->setText(QDate::currentDate().toString("dddd"));// in text
    ui->date_label->setText(QDate::currentDate().toString("dd  MMM  yyyy"));//in number and text

    refreshListWidget();
}


void MainWindow::addTaskFunc()
{
    QListWidgetItem *item = new QListWidgetItem() ;
    item->setSizeHint(QSize(0 , 40));

    addTaskItem *task = new addTaskItem() ;
    connect(task , &addTaskItem::taskAdded , this , &MainWindow::refreshListWidget) ;

    ui->listWidget->addItem(item);
    ui->listWidget->setItemWidget(item , task);
}

void MainWindow::notifier(QString _message)
{
    // 1000 ms to make the notification opacity full and 1000 seconds to call the fade out so total of 2000ms.
    label = new QLabel(this);
    timer = new QTimer(this);
    QGraphicsOpacityEffect* effect=new QGraphicsOpacityEffect();
    label->setGraphicsEffect(effect);
    label->setStyleSheet("border-radius:10px;background-color:green;color:brack;font:Times New Roman");
    label->setAlignment(Qt::AlignCenter);
    label->setText(_message);
    ui->notifier_layout->addWidget(label);
    QPropertyAnimation* a=new QPropertyAnimation(effect,"opacity");
    a->setDuration(1000);  // in miliseconds
    a->setStartValue(0);
    a->setEndValue(1);
    a->setEasingCurve(QEasingCurve::InBack);
    a->start(QPropertyAnimation::DeleteWhenStopped);
    label->show();
    connect(timer,&QTimer::timeout,this,&MainWindow::fadeOut);
    this->timer->start(2000);
}

void MainWindow::fadeOut(){
    QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect();
    this->label->setGraphicsEffect(effect);
    QPropertyAnimation *a = new QPropertyAnimation(effect,"opacity");
    a->setDuration(1000); // it will took 1000ms to face out
    a->setStartValue(1);
    a->setEndValue(0);
    a->setEasingCurve(QEasingCurve::OutBack);
    a->start(QPropertyAnimation::DeleteWhenStopped);
    connect(a,SIGNAL(finished()),this->label,SLOT(hide()));
}

void MainWindow::refreshListWidget()
{
    ui->listWidget->clear();

    //query all tasks of today
    QSqlQuery query ;
    query.prepare("SELECT * FROM tasks WHERE date = :currentDate") ;
    query.bindValue(":currentDate" ,  QDate::currentDate().toString("ddMMMyyyy"));

    if(query.exec()) {
        while (query.next()) {
            QSqlRecord record = query.record() ;
            QString taskText = record.value("task").toString();

            taskItem *_taskItem = new taskItem() ;
            _taskItem->AddTask(taskText);
            connect(_taskItem , &taskItem::removeTaskItem , this , &MainWindow::removeTask) ;

            QListWidgetItem *item = new QListWidgetItem() ;
            item->setSizeHint(QSize(0 , 40));

            ui->listWidget->addItem(item);
            ui->listWidget->setItemWidget(item , _taskItem);
        }
    }

    //create new addText item in end of listWidget
    QListWidgetItem *item = new QListWidgetItem() ;
    item->setSizeHint(QSize(0 , 40));

    addTaskItem *task = new addTaskItem() ;
    connect(task , &addTaskItem::taskAdded , this , &MainWindow::refreshListWidget) ;

    ui->listWidget->addItem(item);
    ui->listWidget->setItemWidget(item , task);
}

void MainWindow::removeTask(QString _taskText)
{
    QSqlQuery query ;
    query.prepare("DELETE FROM tasks WHERE task = :taskText") ;
    query.bindValue(":taskText" , _taskText);
    query.exec() ;
    refreshListWidget();
}

MainWindow::~MainWindow()
{
    delete ui;
}
