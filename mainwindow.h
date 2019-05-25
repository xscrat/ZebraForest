#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>

QT_BEGIN_NAMESPACE
class QAction;
class CodeEditor;
class Highlighter;
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

private slots:
    void newFile();
    void open();
    bool save();
    bool saveAs();
    bool run();

private:
    Ui::MainWindow *ui;

    void createActions();
    bool maybeSave();
    void loadFile(const QString &fileName);
    bool saveFile(const QString &fileName);
    void setCurrentFile(const QString &fileName);
    QString strippedName(const QString &fullFileName);

    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *saveAsAct;

    CodeEditor *textEdit;
    Highlighter *highlighter;
    QString curFile;
};

#endif // MAINWINDOW_H
