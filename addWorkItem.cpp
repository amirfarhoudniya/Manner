#include "addWorkItem.h"
#include "ui_addWorkItem.h"

addWorkItem::addWorkItem(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::addWorkItem)
{
    ui->setupUi(this);

    //pushButton's style
    ui->add_pushButton->setFixedSize(30 , 30);
    ui->add_pushButton->setCursor(Qt::PointingHandCursor);
}

addWorkItem::~addWorkItem()
{
    delete ui;
}

void addWorkItem::on_add_pushButton_clicked()
{
    // QSqlQuery query ;
    // query.prepare("") ;
    // query.addBindValue();
    // query.exec();
}

