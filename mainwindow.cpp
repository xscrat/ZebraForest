#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "highlighter.h"
#include "settingwindow.h"
#include "connectconditionitem.h"
#include "spritedetailpanel.h"
#include <QProcess>
#include <QDebug>
#include <QSysInfo>

extern QSysInfo gSysInfo;
QString header_code("import time\n"
                    "import sys\n"
                    "\n");

MainWindow::MainWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainWindow)
{
    pythonProcess = NULL;
    highlighter = NULL;
    settingWindow = NULL;

    ui->setupUi(this);
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
    codeEditor = ui->tabCodeEditor;
    QFileInfo currentFileInfo(__FILE__);
    QString blocklyFilePath = QDir(currentFileInfo.absolutePath()).filePath("blockly-master/zebra_forest/index.html");
    ui->tabGraphicEditor->load(QUrl(QString("file:///") + blocklyFilePath));
    connect(ui->buttonNew, SIGNAL(clicked()), this, SLOT(newFile()));
    connect(ui->buttonOpen, SIGNAL(clicked()), this, SLOT(open()));
    connect(ui->buttonSave, SIGNAL(clicked()), this, SLOT(save()));
    connect(ui->buttonSaveAs, SIGNAL(clicked()), this, SLOT(saveAs()));
    connect(ui->buttonRun, SIGNAL(clicked()), this, SLOT(run()));
    connect(ui->buttonSetting, SIGNAL(clicked()), this, SLOT(setting()));
    connect(ui->tabEditor, SIGNAL(currentChanged(int)), this, SLOT(tabSelected()));
    highlighter = new Highlighter(codeEditor->document());

    ConnectConditionItem *conditionItem = new ConnectConditionItem(this);
    QRect conditionItemSize = conditionItem->geometry();
    conditionItemSize.moveTo(810, 75);
    conditionItem->setGeometry(conditionItemSize);
    conditionItem->setCondition(true);
    conditionItem->raise();
    spriteConnectionConditions.append(conditionItem);

    SpriteDetailPanel *detailPanel = new SpriteDetailPanel(this);
    QRect detailPanelSize = detailPanel->geometry();
    detailPanelSize.moveTo(794, 155);
    detailPanel->setGeometry(detailPanelSize);
    detailPanel->raise();
    detailPanel->setSpriteInfo(1, "60%", "xxx");
    spriteDetailPanels.append(detailPanel);
}

MainWindow::~MainWindow()
{
    delete ui;
    if (pythonProcess)
    {
        delete pythonProcess;
        pythonProcess = NULL;
    }
    if (highlighter)
    {
        delete highlighter;
        highlighter = NULL;
    }
    if (settingWindow)
    {
        delete settingWindow;
        settingWindow = NULL;
    }
    foreach (ConnectConditionItem* spriteConnectionCondition, spriteConnectionConditions)
    {
        delete spriteConnectionCondition;
    }
    foreach (SpriteDetailPanel* spriteDetailPanel, spriteDetailPanels)
    {
        delete spriteDetailPanel;
    }
}

void MainWindow::newFile()
{
    if (maybeSave()) {
        codeEditor->clear();
        setCurrentFile("");
    }
}

void MainWindow::open()
{
    if (maybeSave()) {
        QString fileName = QFileDialog::getOpenFileName(this, "", "",
                                                        tr("All files (*.*);;blk (*.blk);;" ));

        if (!fileName.isEmpty())
            loadFile(fileName);
    }
}

bool MainWindow::save()
{
    if (curFile.isEmpty()) {
        return saveAs();
    } else {
        return saveFile(curFile);
    }
}

bool MainWindow::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, "保存模块框图", "",
                                                    "blk (*.blk);;");
    if (!fileName.endsWith(".blk"))
    {
        fileName += ".blk";
    }
    return saveFile(fileName);
}

bool MainWindow::maybeSave()
{
    if (codeEditor->document()->isModified()) {
        QMessageBox::StandardButton ret;
        ret = QMessageBox::warning(this, tr("Application"),
                     tr("The document has been modified.\n"
                        "Do you want to save your changes?"),
                     QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        if (ret == QMessageBox::Save)
            return save();
        else if (ret == QMessageBox::Cancel)
            return false;
    }
    return true;
}

void MainWindow::setCurrentFile(const QString &fileName)
{
    curFile = fileName;
    codeEditor->document()->setModified(false);
    setWindowModified(false);

    QString shownName = curFile;
    if (curFile.isEmpty())
        shownName = "untitled.txt";
    setWindowFilePath(shownName);
}

void MainWindow::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return;
    }

    QTextStream in(&file);
#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(Qt::WaitCursor);
#endif
    QString loadContent(in.readAll());
    QByteArray contentByteArray = loadContent.toLatin1();
    QString contentByteArrayBase64 = contentByteArray.toBase64();
    QString evaluateSource = "Code.loadBlockly(\'" + contentByteArrayBase64 + "\');";
    ui->tabGraphicEditor->page()->currentFrame()->evaluateJavaScript(evaluateSource);

#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif

    setCurrentFile(fileName);
}

bool MainWindow::saveFile(const QString &fileName)
{
    QVariant tmp =  ui->tabGraphicEditor->page()->currentFrame()->evaluateJavaScript("Code.saveBlockly();");
    QString saveContent = tmp.toString();
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return false;
    }

    QTextStream out(&file);
#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(Qt::WaitCursor);
#endif
    out << saveContent;
#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif

    setCurrentFile(fileName);
    return true;
}

bool MainWindow::run()
{
    transferGraphicCodeToEditorCode();
    if (pythonProcess)
    {
        delete pythonProcess;
        pythonProcess = NULL;
    }
    pythonProcess = new QProcess(this);
    QString program = "python";
    QString command = "-c";
    pythonProcess->setProcessChannelMode(QProcess::MergedChannels);
    connect(pythonProcess, SIGNAL(readyRead()), this, SLOT(readCommand()));
    connect(pythonProcess, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(stopCommand(int, QProcess::ExitStatus)));
    pythonProcess->start(program, QStringList() << command << header_code + ui->tabCodeEditor->toPlainText());
    return true;
}

bool MainWindow::setting()
{
    if (!settingWindow)
    {
        settingWindow = new SettingWindow();
    }
    settingWindow->exec();
    settingWindow->setModal(true);
    return true;
}

void MainWindow::readCommand()
{
    pythonProcess->readAll();
}

void MainWindow::stopCommand(int exitCode, QProcess::ExitStatus exitStatus)
{
    pythonProcess->readAll();
}

void MainWindow::transferGraphicCodeToEditorCode()
{
    QVariant tmp =  ui->tabGraphicEditor->page()->currentFrame()->evaluateJavaScript("Code.showCode();");
    QString code = tmp.toString();
    ui->tabCodeEditor->document()->setPlainText(header_code + code);
}

void MainWindow::tabSelected()
{
    if (ui->tabEditor->currentIndex() == 1)
    {
        transferGraphicCodeToEditorCode();
    }
}
