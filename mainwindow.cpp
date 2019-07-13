#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "highlighter.h"
#include <QProcess>
#include <QtWebChannel/QWebChannel>
#include "QtWebSockets/qwebsocketserver.h"
#include "QtWebSockets/qwebsocket.h"
#include "QUdpSocket"
#include <QDebug>
#include <QSysInfo>

extern QSysInfo gSysInfo;

MainWindow::MainWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainWindow)
{
    pythonProcess = NULL;
    highlighter = NULL;

    ui->setupUi(this);
    codeEditor = ui->tabCodeEditor;
    QFileInfo currentFileInfo(__FILE__);
    QString blocklyFilePath = QDir(currentFileInfo.absolutePath()).filePath("blockly-master/demos/generator/index.html");
    if (gSysInfo.kernelType().indexOf("win") != -1)
    {
        ui->tabGraphicEditor->load(QUrl(QString("file:///") + blocklyFilePath));
    }
    else
    {
        ui->tabGraphicEditor->load(QUrl(QString("file:///") + blocklyFilePath));
    }
    connect(ui->buttonNew, SIGNAL(clicked()), this, SLOT(newFile()));
    connect(ui->buttonOpen, SIGNAL(clicked()), this, SLOT(open()));
    connect(ui->buttonSave, SIGNAL(clicked()), this, SLOT(save()));
    connect(ui->buttonSaveAs, SIGNAL(clicked()), this, SLOT(saveAs()));
    connect(ui->buttonRun, SIGNAL(clicked()), this, SLOT(run()));
    connect(ui->tabEditor, SIGNAL(currentChanged(int)), this, SLOT(tabSelected()));
    highlighter = new Highlighter(codeEditor->document());
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
        QString fileName = QFileDialog::getOpenFileName(this);
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
    QFileDialog dialog(this);
    dialog.setWindowModality(Qt::WindowModal);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    QStringList files;
    if (dialog.exec())
        files = dialog.selectedFiles();
    else
        return false;

    return saveFile(files.at(0));
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
    codeEditor->setPlainText(in.readAll());
#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif

    setCurrentFile(fileName);
}

bool MainWindow::saveFile(const QString &fileName)
{
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
    out << codeEditor->toPlainText();
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
    pythonProcess->start(program, QStringList() << command << ui->tabCodeEditor->toPlainText());
    return true;
}

void MainWindow::readCommand()
{
    ui->codeOutput->append(pythonProcess->readAll());
}

void MainWindow::stopCommand(int exitCode, QProcess::ExitStatus exitStatus)
{
    ui->codeOutput->append(pythonProcess->readAll());
}

void MainWindow::transferGraphicCodeToEditorCode()
{
    QVariant tmp =  ui->tabGraphicEditor->page()->currentFrame()->evaluateJavaScript("showCode();");
    QString code = tmp.toString();
    ui->tabCodeEditor->document()->setPlainText(code);
}

void MainWindow::tabSelected()
{
    if (ui->tabEditor->currentIndex() == 1)
    {
        transferGraphicCodeToEditorCode();
    }
}
