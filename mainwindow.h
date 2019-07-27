#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QProcess>
#include <QList>

QT_BEGIN_NAMESPACE
class QAction;
class CodeEditor;
class Highlighter;
class SettingWindow;
class ConnectConditionItem;
class SpriteDetailPanel;
QT_END_NAMESPACE

namespace Ui {
class MainWindow;
}

class MainWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

Q_SIGNALS:
    void closed();

private slots:
    void newFile();
    void open();
    bool save();
    bool saveAs();
    bool run();
    bool setting();
    void readCommand();
    void stopCommand(int exitCode, QProcess::ExitStatus exitStatus);
    void tabSelected();

private:
    Ui::MainWindow *ui;

    bool maybeSave();
    void loadFile(const QString &fileName);
    bool saveFile(const QString &fileName);
    void setCurrentFile(const QString &fileName);
    QString strippedName(const QString &fullFileName);
    void transferGraphicCodeToEditorCode();

    CodeEditor *codeEditor;
    Highlighter *highlighter;
    SettingWindow *settingWindow;
    QString curFile;
    QProcess *pythonProcess;
    QList<ConnectConditionItem*> spriteConnectionConditions;
    QList<SpriteDetailPanel*> spriteDetailPanels;
};

#endif // MAINWINDOW_H
