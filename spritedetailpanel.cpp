#include "spritedetailpanel.h"
#include "ui_spritedetailpanel.h"

SpriteDetailPanel::SpriteDetailPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SpriteDetailPanel)
{
    ui->setupUi(this);
}

SpriteDetailPanel::~SpriteDetailPanel()
{
    delete ui;
}

void SpriteDetailPanel::setSpriteInfo(int id, QString power_percent, QString identifier)
{
    ui->label->setText(QString::number(id));
    ui->label_2->setText(power_percent);
    ui->label_3->setText(identifier);
}
