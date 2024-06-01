#include "Settings.h"
#include "ui_Settings.h"

Settings::Settings(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Settings)
{
    ui->setupUi(this);

    ui->add_pushButton->setCursor(Qt::PointingHandCursor);
    ui->remove_pushButton->setCursor(Qt::PointingHandCursor);
    ui->back_pushButton->setCursor(Qt::PointingHandCursor);

    updateListView() ;
}

Settings::~Settings()
{
    delete ui;
}

void Settings::on_add_pushButton_clicked()
{
    if(ui->lineEdit->text().isEmpty()) {
        ui->lineEdit->setStyleSheet("color : red");
        ui->lineEdit->setPlaceholderText("can't be empty");
    } else {
        QString txt = ui->lineEdit->text() ;
        QSqlQuery query ;
        query.prepare("INSERT INTO habits (habit , date , status) VALUES (? , ? , ?)") ;
        query.addBindValue(txt);
        query.addBindValue(QDate::currentDate().toString("ddMMMMyyyy"));
        query.addBindValue(0);
        if(query.exec()) {
            ui->lineEdit->clear();
        }
    }

    updateListView() ;
}

void Settings::updateListView()
{
    ui->listWidget->clear();

    QSqlQuery query ;
    query.prepare("SELECT * FROM habits") ;
    QSqlRecord record ;

    if(query.exec()) {
        while (query.next()) {
            record = query.record() ;
            ui->listWidget->addItem(record.value("habit").toString());
        }
    }
}

void Settings::on_remove_pushButton_clicked()
{
    QString currentSelectedText = ui->listWidget->currentItem()->text() ;

    QSqlQuery query ;
    query.prepare("DELETE FROM habits WHERE habit = :habit") ;
    query.bindValue(":habit" , currentSelectedText);
    query.exec() ;

    updateListView();
}


void Settings::on_lineEdit_textEdited(const QString &arg1)
{
    ui->lineEdit->setStyleSheet("");
}


void Settings::on_back_pushButton_clicked()
{
    MainWindow *m = new MainWindow() ;
    m->show();
    this->close() ;
}

