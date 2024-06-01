#include "achievments.h"
#include "ui_achievments.h"

achievments::achievments(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::achievments)
{
    ui->setupUi(this);

    this->setLayout(ui->verticalLayout);

    //ui of tabel widget
    ui->tableWidget->setRowCount(6);
    ui->tableWidget->setColumnCount(7);
    ui->tableWidget->verticalHeader()->hide();
    ui->tableWidget->horizontalHeader()->hide();

    //
    currentYear = calendar.yearShown();
    currentMonth =calendar.monthShown();

    // Set items of year comboBox
    ui->year_comboBox->clear();
    for (int i = currentYear - 5; i <= currentYear + 5; ++i) {
        ui->year_comboBox->addItem(QString::number(i));
    }
    ui->year_comboBox->setCurrentIndex(5);

    // Set items of month comboBox
    ui->month_comboBox->clear();
    ui->month_comboBox->addItem("January");
    ui->month_comboBox->addItem("February");
    ui->month_comboBox->addItem("March");
    ui->month_comboBox->addItem("April");
    ui->month_comboBox->addItem("May");
    ui->month_comboBox->addItem("June");
    ui->month_comboBox->addItem("July");
    ui->month_comboBox->addItem("August");
    ui->month_comboBox->addItem("September");
    ui->month_comboBox->addItem("October");
    ui->month_comboBox->addItem("November");
    ui->month_comboBox->addItem("December");

    ui->month_comboBox->setCurrentIndex(currentMonth - 1); // Subtract 1 from currentMonth to match the index

    updateToDoWidgets() ;
}

achievments::~achievments()
{
    delete ui;
}


void achievments::updateToDoWidgets()
{
    ui->tableWidget->clear();

    //
    int columnCounter = 0;
    int rowCounter = 0;

    int monthDays ;

    if(ui->month_comboBox->currentText() == "January" ||
                                            "March"   ||
                                            "May"     ||
                                            "July"    ||
                                            "August"  ||
                                            "October" ||
                                            "December") {
        monthDays = 31 ;
    } else if(ui->month_comboBox->currentText() == "April" ||
                                                   "June"  ||
                                                   "September" ||
                                                   "November") {
        monthDays = 30 ;
    } else {
        //February 28 days in a common year and 29 days in leap years
        if(ui->year_comboBox->currentText().toInt() % 4 == 0 ) {
            //is leap year
            monthDays = 29 ;
        } else{
            monthDays = 28 ;
        }
    }

    for (int i = 1 ; i <= monthDays ; i++) {

        if(i  > monthDays ) {
            break ;
        }

        int _dayOfWeek = calendar.calendar().dateFromParts( ui->year_comboBox->currentText().toInt(),
                                                           ui->month_comboBox->currentIndex() + 1 ,
                                                           i).dayOfWeek();
        achievmentItem *item = new achievmentItem() ;
        item->setDayOfWeek(_dayOfWeek);
        item->setDayOfMonth(i);
        getTaskStatusFromDB(ui->year_comboBox->currentText().toInt() ,
                            ui->month_comboBox->currentText() ,
                            i , item);
        columnCounter = _dayOfWeek - 1;
        ui->tableWidget->setCellWidget(rowCounter , columnCounter ,item) ;
        ui->tableWidget->setRowHeight(rowCounter , 118);
        ui->tableWidget->setColumnWidth(columnCounter , 165);
        if(columnCounter == 6) {
            rowCounter ++ ;
        }
    }

}

void achievments::getTaskStatusFromDB(int _year, QString _month, int _day , achievmentItem *_item)
{
    QString _date = QString::number(_day) + _month + QString::number(_year) ;
    int habitTasksDone = 0 ;
    int regularTasksDone = 0 ;
    QSqlQuery query ;

    //habit tasks
    query.prepare("SELECT COUNT(*) FROM habits WHERE date = :date AND status = '1' ") ;
    query.bindValue(":date" , _date);

    if(query.exec() && query.next()) {
        habitTasksDone = query.value(0).toInt() ;
    }

    //regular tasks
    query.prepare("SELECT COUNT(*) FROM tasks WHERE date = :date AND status = '1' ") ;
    query.bindValue(":date" , _date);

    if(query.exec() && query.next()) {
        regularTasksDone = query.value(0).toInt() ;
    }

    _item->setStar(habitTasksDone,regularTasksDone);
}

void achievments::on_month_comboBox_currentIndexChanged()
{
    updateToDoWidgets();
}

void achievments::changeEvent(QEvent *event)
{
    // if page maximized show achievments
    if(event->type() == QEvent::WindowStateChange) {
        if(windowState() == Qt::WindowMaximized) {
            MainWindow *m = new MainWindow() ;
            m->show();
            this->close();
        }
    }
}



