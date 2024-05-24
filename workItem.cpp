#include "workItem.h"
#include "ui_workItem.h"

workItem::workItem(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::workItem)
{
    ui->setupUi(this);

    ui->remove_pushButton->setFixedSize(30 , 30);
    ui->remove_pushButton->setCursor(Qt::PointingHandCursor);
}

workItem::~workItem()
{
    delete ui;
}
