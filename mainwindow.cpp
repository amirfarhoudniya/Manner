#include "mainwindow.h"
#include "ui_mainwindow.h"


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

MainWindow::~MainWindow()
{
    delete ui;
}
