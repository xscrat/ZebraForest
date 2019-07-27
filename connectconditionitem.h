#ifndef CONNECTCONDITIONITEM_H
#define CONNECTCONDITIONITEM_H

#include <QWidget>
#include <QGraphicsScene>

namespace Ui {
class ConnectConditionItem;
}

class ConnectConditionItem : public QWidget
{
    Q_OBJECT

public:
    explicit ConnectConditionItem(QWidget *parent = 0);
    ~ConnectConditionItem();
    void setCondition(bool onOrOff);

private:
    Ui::ConnectConditionItem *ui;
    QImage onImage;
    QGraphicsScene onScene;
};

#endif // CONNECTCONDITIONITEM_H
