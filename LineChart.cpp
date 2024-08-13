#include "LineChart.h"
#include "ui_LineChart.h"

LineChart::LineChart(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LineChart)
{
    ui->setupUi(this);

    chartView->setRenderHint(QPainter::Antialiasing);
    gLayout->addWidget(chartView);
    this->setLayout(gLayout);

    countWeekTasks();

}

LineChart::~LineChart()
{
    delete ui;
}

void LineChart::updateChart(QLineSeries *_series )
{
    chart->legend()->hide();
    chart->addSeries(_series);
    chart->createDefaultAxes();
    chart->setTitle("tasks done in week");
}

void LineChart::countWeekTasks()
{
    int currentWeek = QDate::currentDate().weekNumber();

    QDate date = QDate(QDate::currentDate().year() , 1 , 1);
    QDate startDate = date ;

    int week ;
    int day ;
    int counter = 0 ;

    for (week = 1 ; week < currentWeek + 1 ; ++week) {

        counter = 0 ;
        qDebug() << "**************************************************" ;
        qDebug() << "From " << startDate.toString("ddMMMMyyyy") ;

        for(day = 0 ; day < 7 ; day++) {

            QSqlQuery query;
            //count number of tasks have done in week
            query.prepare("SELECT COUNT(*) FROM tasks WHERE date =:date AND status = 1");
            query.bindValue(":date", startDate.addDays(day).toString("ddMMMMyyyy"));

            if (query.exec()) {
                if(query.next()) {
                    counter += query.value(0).toInt() ;
                }
            }
        }

        qDebug() << " to " << startDate.addDays(7).toString("ddMMMMyyyy") ;
        qDebug() << "number of tasks done for week " << week << " : " << counter;

        // add counted task to chart
        series->append(week , counter);

        //set the startDate to next first day of week
        startDate = date.addDays(week * 7) ;
    }

    updateChart(series);
}
