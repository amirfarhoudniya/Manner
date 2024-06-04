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

    ui->setting_pushButton->setIcon(QIcon(":/icons/icons/settings.png"));
    ui->setting_pushButton->setCursor(Qt::PointingHandCursor);

    ui->achivements_pushButton->setCursor(Qt::PointingHandCursor);

    copyHabitToTaskDB() ;
    refreshListWidget();
}

void MainWindow::refreshListWidget()
{
    ui->listWidget->clear();

    QSqlQuery query ;
    QSqlRecord record ;

    //query habits
    query.prepare("SELECT * FROM tasks WHERE date = :currentDate AND isHabit = '1' ") ;
    query.bindValue(":currentDate" , QDate::currentDate().toString("ddMMMMyyyy"));

    if(query.exec()) {
        while(query.next()) {
            record =query.record() ;
            QString habitText = record.value("task").toString() ;
            taskItem *_taskItem = new taskItem() ;
            _taskItem->AddTask(habitText , 1);
            connect(_taskItem , &taskItem::removeTaskItem , this , &MainWindow::removeTask) ;

            if(record.value("status").toInt() == 1) {
                _taskItem->checkTheCheckBox();
            }

            //make listWidget item
            QListWidgetItem *item = new QListWidgetItem() ;
            item->setSizeHint(QSize(0 , 40));

            //add our widget to item
            ui->listWidget->addItem(item);
            ui->listWidget->setItemWidget(item , _taskItem);
        }
    }

    //query regular tasks of today
    query.prepare("SELECT * FROM tasks WHERE date = :currentDate AND isHabit = '0' ") ;
    query.bindValue(":currentDate" ,  QDate::currentDate().toString("ddMMMMyyyy"));

    if(query.exec()) {
        while (query.next()) {
            record = query.record() ;
            QString taskText = record.value("task").toString();

            taskItem *_taskItem = new taskItem() ;
            _taskItem->AddTask(taskText , 0);
            connect(_taskItem , &taskItem::removeTaskItem , this , &MainWindow::removeTask) ;

            if(record.value("status").toInt() == 1) {
                _taskItem->checkTheCheckBox();
            }

            //make listWidget item
            QListWidgetItem *item = new QListWidgetItem() ;
            item->setSizeHint(QSize(0 , 40));

            //add our widget to item
            ui->listWidget->addItem(item);
            ui->listWidget->setItemWidget(item , _taskItem);
        }
    }

    //create new addText item in end of listWidget
    QListWidgetItem *item = new QListWidgetItem() ;
    item->setSizeHint(QSize(0 , 40));

    addTaskItem *task = new addTaskItem() ;
    connect(task , &addTaskItem::taskAdded , this , &MainWindow::refreshListWidget) ;
    connect(task , &addTaskItem::callPopUpNotifier , this , &MainWindow::notifier) ;

    ui->listWidget->addItem(item);
    ui->listWidget->setItemWidget(item , task);
}

void MainWindow::copyHabitToTaskDB()
{
    QSqlQuery query;
    QSqlQuery query3;

    query.prepare("SELECT * FROM habits WHERE habit NOT IN (SELECT task FROM tasks WHERE date = :date AND isHabit = '1')");
    query.bindValue(":date", QDate::currentDate().toString("ddMMMMyyyy"));

    if (query.exec()) {
        while (query.next()) {
            QString habitText = query.value("habit").toString();

            query3.prepare("INSERT INTO tasks (task, date, status, isHabit) VALUES (?, ?, ?, ?)");
            query3.addBindValue(habitText);
            query3.addBindValue(QDate::currentDate().toString("ddMMMMyyyy"));
            query3.addBindValue(0);
            query3.addBindValue(1);

            if (!query3.exec()) {
                qDebug() << "Failed to insert habit into tasks.";
            }
        }
    } else {
        qDebug() << "Failed to execute query.";
    }
}

void MainWindow::removeTask(QString _taskText)
{
    QSqlQuery query ;
    query.prepare("DELETE FROM tasks WHERE task = :taskText AND date = :date") ;
    query.bindValue(":taskText" , _taskText);
    query.bindValue(":date" , QDate::currentDate().toString("ddMMMMyyyy"));
    query.exec() ;

    refreshListWidget();
    notifier("saved");
}

void MainWindow::notifier(QString _message)
{
    // 1000 ms to make the notification opacity full and 1000 seconds to call the fade out, so a total of 2000ms.
    label = new QLabel(this);
    timer = new QTimer(this);
    QGraphicsOpacityEffect* effect = new QGraphicsOpacityEffect();
    label->setGraphicsEffect(effect);
    label->setStyleSheet("border-radius:10px;background-color:green;color:black;font:Arial;");
    label->setAlignment(Qt::AlignCenter);
    label->setText(_message);
    ui->notifier_layout->addWidget(label);
    QPropertyAnimation* a = new QPropertyAnimation(effect, "opacity");
    a->setDuration(500);  // in milliseconds
    a->setStartValue(0);
    a->setEndValue(1);
    a->setEasingCurve(QEasingCurve::InBack);
    a->start(QPropertyAnimation::DeleteWhenStopped);
    label->show();

    connect(timer, &QTimer::timeout, this, &MainWindow::fadeOut);
    this->timer->start(1000);
}

void MainWindow::fadeOut(){
    QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect();
    this->label->setGraphicsEffect(effect);
    QPropertyAnimation *a = new QPropertyAnimation(effect,"opacity");
    a->setDuration(500); // it will took 1000ms to face out
    a->setStartValue(1);
    a->setEndValue(0);
    a->setEasingCurve(QEasingCurve::OutBack);
    a->start(QPropertyAnimation::DeleteWhenStopped);
    connect(a,SIGNAL(finished()),this->label,SLOT(hide()));
    disconnect(timer, &QTimer::timeout, this, &MainWindow::fadeOut);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_setting_pushButton_clicked()
{
    Settings *s = new Settings() ;
    s->show();
    this->close() ;
}


void MainWindow::on_achivements_pushButton_clicked()
{
    achievments *a = new achievments() ;
    a->show();
}

