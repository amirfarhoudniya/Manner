#include "addTaskItem.h"
#include "ui_addTaskItem.h"

addTaskItem::addTaskItem(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::addTaskItem)
{
    ui->setupUi(this);

    //pushButton's style
    ui->add_pushButton->setFixedSize(30 , 30);
    ui->add_pushButton->setCursor(Qt::PointingHandCursor);

}

addTaskItem::~addTaskItem()
{
    delete ui;
}

void addTaskItem::on_add_pushButton_clicked()
{
    if(ui->lineEdit->text().isEmpty()) {
        ui->lineEdit->setStyleSheet("color:red");
        ui->lineEdit->setPlaceholderText(" can't be empty");
    } else {
        QString task = ui->lineEdit->text() ;
        QString date  = QDate::currentDate().toString("ddMMMMyyyy");
        int status = 0 ; // zero: task is undone , 1: task is done

        QSqlQuery query ;
        query.prepare("INSERT INTO tasks(task , date , status , isHabit) VALUES ( ? , ? , ? , ?)") ;
        query.addBindValue(task);
        query.addBindValue(date);
        query.addBindValue(status);
        query.addBindValue(0);
        query.exec();
        taskText = task ;
        emit taskAdded();
        emit callPopUpNotifier("saved");
        QTimer::singleShot(1, this, &addTaskItem::close);
    }
}

void addTaskItem::keyPressEvent(QKeyEvent *event)
{
    //add item "Enter" key pressed
    if(event->key() == Qt::Key_Return) {
        on_add_pushButton_clicked();
    }
}


void addTaskItem::on_lineEdit_textEdited(const QString &arg1)
{
    ui->lineEdit->setStyleSheet("color:white");
}

