#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDate>
#include <QLabel>
#include <QTimer>
#include <QSqlQuery>

#include "addTaskItem.h"
#include "taskItem.h"
#include "dataBase.h"


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
    void notifier(QString _message) ;
    void fadeOut() ;
    void refreshListWidget() ;
    void removeTask(QString _taskText);

    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QDate date ;

    QLabel *label ;
    QTimer *timer ;
};
#endif // MAINWINDOW_H
