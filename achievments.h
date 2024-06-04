#ifndef ACHIEVMENTS_H
#define ACHIEVMENTS_H

#include <QWidget>
#include <QCalendarWidget>
#include <QSqlQuery>



#include "achievmentItem.h"
#include "dataBase.h"
#include "mainwindow.h"

namespace Ui {
class achievments;
}

class achievments : public QWidget
{
    Q_OBJECT

public:
    explicit achievments(QWidget *parent = nullptr);
    ~achievments();

private slots:
    void on_month_comboBox_currentIndexChanged();

private:
    Ui::achievments *ui;
    QCalendarWidget calendar ;
    int currentYear ;
    int currentMonth ;

    void updateToDoWidgets() ;
    void getTaskStatusFromDB(int _year , QString _month , int _day , achievmentItem *_item) ;
    void updateStatics() ;
};

#endif // ACHIEVMENTS_H
