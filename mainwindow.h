#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDate>

#include "addWorkItem.h"
#include "workItem.h"


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
    void addWorkFunc() ;
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QDate date ;
};
#endif // MAINWINDOW_H
