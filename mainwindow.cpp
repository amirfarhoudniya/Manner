#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //labels style
    // ui->dayInWeek_label->setAlignment(Qt::AlignVCenter);
    // ui->dayInMonth_label->setAlignment(Qt::AlignHCenter);
    // ui->monthName_label->setAlignment(Qt::AlignLeft);

    //lable's text
    ui->dayInWeek_label->setText(date.currentDate().toString("dddd"));// in text
    ui->date_label->setText(date.currentDate().toString("dd  MMM  yyyy"));//in number and text


    addWorkFunc();
}

void MainWindow::addWorkFunc()
{
    QListWidgetItem *item = new QListWidgetItem() ;
    item->setSizeHint(QSize(0 , 40));

    addWorkItem *work = new addWorkItem() ;
    // workItem *workItem1 = new workItem() ;

    ui->listWidget->addItem(item);
    ui->listWidget->setItemWidget(item , work);
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

MainWindow::~MainWindow()
{
    delete ui;
}
