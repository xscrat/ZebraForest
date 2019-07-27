#include <QSerialPortInfo>
#include <QList>
#include <QtCore>
#include <QPushButton>
#include <QMessageBox>
#include "settingwindow.h"
#include "ui_settingwindow.h"

SettingWindow::SettingWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
    QFileInfo currentFileInfo(__FILE__);
    QString settingFileName = QDir(currentFileInfo.absolutePath()).filePath("setting.cfg");
    QFile file(settingFileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
    }

    QTextStream in(&file);
    QString settingContent(in.readAll());
    QList<QSerialPortInfo> portList = QSerialPortInfo::availablePorts();
    foreach (QSerialPortInfo info, portList)
    {
        ui->comboBox->addItem(info.portName());
    }
    connect(ui->buttonBox->button(QDialogButtonBox::Ok), SIGNAL(clicked()), this, SLOT(onOK()));

    ui->buttonBox->button(QDialogButtonBox::Ok)->setText("确定");
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("取消");
}

SettingWindow::~SettingWindow()
{
    delete ui;
}

void SettingWindow::onOK()
{
    QFileInfo currentFileInfo(__FILE__);
    QString settingFileName = QDir(currentFileInfo.absolutePath()).filePath("setting.cfg");
    QFile file(settingFileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(settingFileName)
                             .arg(file.errorString()));
        return;
    }

    QTextStream out(&file);
    out << ui->comboBox->currentText();;
}
