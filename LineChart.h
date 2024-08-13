#ifndef LINECHART_H
#define LINECHART_H

#include <QWidget>
#include <QChart>
#include <QLineSeries>
#include <QChartView>
#include <QGridLayout>

#include "dataBase.h"

namespace Ui {
class LineChart;
}

class LineChart : public QWidget
{
    Q_OBJECT

public:
    explicit LineChart(QWidget *parent = nullptr);
    ~LineChart();

private:

    //variabeles
    Ui::LineChart *ui;
    QChart *chart = new QChart();
    QLineSeries *series = new QLineSeries();
    QChartView *chartView = new QChartView(chart);
    QGridLayout *gLayout = new QGridLayout() ;


    //funcs

    void updateChart(QLineSeries *_series) ;
    void countWeekTasks() ;

};

#endif // LINECHART_H
