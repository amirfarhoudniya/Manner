#include "achievmentItem.h"
#include "ui_achievmentItem.h"

achievmentItem::achievmentItem(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::achievmentItem)
{
    ui->setupUi(this);

    this->setLayout(ui->verticalLayout);

    ui->dayOfWeek_label->setAlignment(Qt::AlignCenter);
    ui->dayOfMonth_label->setAlignment(Qt::AlignCenter);

    QPixmap habitPixmap (":/icons/icons/star.png");
    QPixmap regularPixmap (":/icons/icons/star2.png") ;


    ui->habitPixmap_label->setPixmap(habitPixmap);

    ui->habit_label->setText("Habit tasks");

    ui->regularTaskPixmap_label->setPixmap(regularPixmap);

    ui->regularTask_label->setText("regular tasks");

}

achievmentItem::~achievmentItem()
{
    delete ui;
}


void achievmentItem::setDayOfWeek(int _number)
{

    switch (_number) {
    case 1:
        ui->dayOfWeek_label->setText("Monday");
        break;
    case 2:
        ui->dayOfWeek_label->setText("Tuesday");
        break;
    case 3:
        ui->dayOfWeek_label->setText("Wednesday");
        break;
    case 4:
        ui->dayOfWeek_label->setText("Thursday");
        break;
    case 5:
        ui->dayOfWeek_label->setText("Friday");
        break;
    case 6:
        ui->dayOfWeek_label->setText("Saturday");
        break;
    case 7:
        ui->dayOfWeek_label->setText("Sunday");
        break;
    default:
        break;
    }
}

void achievmentItem::setDayOfMonth(int _number)
{
    ui->dayOfMonth_label->setText(QString::number(_number));
}

void achievmentItem::setStar(int _habit, int _regularTask)
{

    QPixmap habitPixmap (":/icons/icons/star.png");
    QPixmap regularPixmap (":/icons/icons/star2.png") ;


    ui->habitPixmap_label->setPixmap(habitPixmap);
    ui->habit_label->setText(QString::number(_habit));

    ui->regularTaskPixmap_label->setPixmap(regularPixmap);
    ui->regularTask_label->setText(QString::number(_regularTask));

    qDebug() << "(ok): " << QString::number(_habit) << " , " << QString::number(_regularTask) ;
}




