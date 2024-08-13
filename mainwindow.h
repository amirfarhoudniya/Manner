#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDate>
#include <QLabel>
#include <QTimer>
#include <QSqlQuery>
#include <QKeyEvent>

#include "addTaskItem.h"
#include "taskItem.h"
#include "dataBase.h"
#include "achievments.h"
#include "Settings.h"
#include "LineChart.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_setting_pushButton_clicked();

    void on_achivements_pushButton_clicked();


    void on_lineChart_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QDate date ;

    QLabel *label ;
    QTimer *timer ;

    void notifier(QString _message) ;
    void fadeOut() ;
    void refreshListWidget() ;
    void removeTask(QString _taskText);
    void copyHabitToTaskDB() ;
};
#endif // MAINWINDOW_H
