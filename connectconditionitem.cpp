#include "connectconditionitem.h"
#include "ui_connectconditionitem.h"

ConnectConditionItem::ConnectConditionItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConnectConditionItem)
{
    ui->setupUi(this);
    QString onFile = QString::fromUtf8(":/images/green_circle.png");
    onImage.load(onFile, "PNG");
    onScene.addPixmap(QPixmap::fromImage(onImage));
    ui->graphicsView->setScene(&onScene);
}

ConnectConditionItem::~ConnectConditionItem()
{
    delete ui;
}

void ConnectConditionItem::setCondition(bool onOrOff)
{
    if (onOrOff)
    {
    }
    else
    {
    }
}
