#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "highlighter.h"
#include <QProcess>
#include <QDebug>
#include <QSysInfo>

extern QSysInfo gSysInfo;
QString header_code("def execute_sprite_func(func_name, *args):\n"
                    "  print(func_name)\n"
                    "  for arg in args:\n"
                    "    print(arg)\n"
                    "\n");

MainWindow::MainWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainWindow)
{
    pythonProcess = NULL;
    highlighter = NULL;

    ui->setupUi(this);
    codeEditor = ui->tabCodeEditor;
    QFileInfo currentFileInfo(__FILE__);
    QString blocklyFilePath = QDir(currentFileInfo.absolutePath()).filePath("blockly-master/zebra_forest/index.html");
    ui->tabGraphicEditor->load(QUrl(QString("file:///") + blocklyFilePath));
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
                                                    "blk (*.blk);;All Files (*)");
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
    QString evaluateSource = "loadBlockly(\'" + contentByteArrayBase64 + "\');";
    ui->tabGraphicEditor->page()->currentFrame()->evaluateJavaScript(evaluateSource);

#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif

    setCurrentFile(fileName);
}

bool MainWindow::saveFile(const QString &fileName)
{
    QVariant tmp =  ui->tabGraphicEditor->page()->currentFrame()->evaluateJavaScript("saveBlockly();");
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

void MainWindow::readCommand()
{
    // ui->codeOutput->append(pythonProcess->readAll());
}

void MainWindow::stopCommand(int exitCode, QProcess::ExitStatus exitStatus)
{
    // ui->codeOutput->append(pythonProcess->readAll());
}

void MainWindow::transferGraphicCodeToEditorCode()
{
    QVariant tmp =  ui->tabGraphicEditor->page()->currentFrame()->evaluateJavaScript("showCode();");
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
