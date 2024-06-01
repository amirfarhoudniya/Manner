#ifndef ACHIEVMENTITEM_H
#define ACHIEVMENTITEM_H

#include <QWidget>

namespace Ui {
class achievmentItem;
}

class achievmentItem : public QWidget
{
    Q_OBJECT

public:
    explicit achievmentItem(QWidget *parent = nullptr);
    void setDayOfWeek(int _number) ;
    void setDayOfMonth(int _number) ;
    void setStar(int _habit , int _regularTask) ;
    ~achievmentItem();

private:
    Ui::achievmentItem *ui;
};

#endif // ACHIEVMENTITEM_H
