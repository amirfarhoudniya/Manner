#include "mainwindow.h"
#include <QSqlDatabase>
#include <QApplication>
#include <QGraphicsOpacityEffect>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //init dateBase
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("dataBase.db");
    db.open();

    MainWindow w;
    w.show();


    return a.exec();
}
