#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QMessageBox>

#include "dataBase.h"
#include "mainwindow.h"


namespace Ui {
class Settings;
}

class Settings : public QWidget
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = nullptr);
    ~Settings();

private slots:
    void on_add_pushButton_clicked();

    void on_remove_pushButton_clicked();

    void on_lineEdit_textEdited(const QString &arg1);

    void on_back_pushButton_clicked();

private:
    Ui::Settings *ui;

    void updateListView() ;
    void copyHabitToTaskDB() ;
};

#endif // SETTINGS_H
