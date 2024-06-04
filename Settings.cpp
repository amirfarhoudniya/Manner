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

void Settings::copyHabitToTaskDB()
{
    QSqlQuery query;
    QSqlQuery query2;

    query.prepare("SELECT * FROM habits WHERE habit NOT IN (SELECT task FROM tasks WHERE date = :date AND isHabit = '1')");
    query.bindValue(":date", QDate::currentDate().toString("ddMMMMyyyy"));

    if (query.exec()) {
        while (query.next()) {
            QString habitText = query.value("habit").toString();

            query2.prepare("INSERT INTO tasks (task, date, status, isHabit) VALUES (?, ?, ?, ?)");
            query2.addBindValue(habitText);
            query2.addBindValue(QDate::currentDate().toString("ddMMMMyyyy"));
            query2.addBindValue(0);
            query2.addBindValue(1);

            if (!query2.exec()) {
                qDebug() << "Failed to insert habit into tasks.";
            }
        }
    } else {
        qDebug() << "Failed to execute query.";
    }

}

void Settings::on_add_pushButton_clicked()
{
    QString txt ;

    if(ui->lineEdit->text().isEmpty()) {
        ui->lineEdit->setStyleSheet("color : red");
        ui->lineEdit->setPlaceholderText("can't be empty");
    } else {
        txt = ui->lineEdit->text() ;
        QSqlQuery query ;
        query.prepare("INSERT INTO habits (habit , date , status) VALUES (? , ? , ?)") ;
        query.addBindValue(txt);
        query.addBindValue(QDate::currentDate().toString("ddMMMMyyyy"));
        query.addBindValue(0);
        if(query.exec()) {
            ui->lineEdit->clear();
        }
    }

    copyHabitToTaskDB() ;
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

