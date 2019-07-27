#ifndef SPRITEDETAILPANEL_H
#define SPRITEDETAILPANEL_H

#include <QWidget>
#include <QString>

namespace Ui {
class SpriteDetailPanel;
}

class SpriteDetailPanel : public QWidget
{
    Q_OBJECT

public:
    explicit SpriteDetailPanel(QWidget *parent = 0);
    ~SpriteDetailPanel();
    void setSpriteInfo(int id, QString power_percent, QString identifier);

private:
    Ui::SpriteDetailPanel *ui;
};

#endif // SPRITEDETAILPANEL_H
