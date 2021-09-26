#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QGridLayout>
#include <QFileDialog>
#include <QKeyEvent>

#include "commandlinemanager.h"
#include "contentviewer.h"
#include "syftorganizer.h"
#include "syftactionmanager.h"
#include "syftlogger.h"
#include "outputwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    void NextFile();
    void PreviousFile();

    static QApplication application;

private:
    void ChangeFile(SyftFile* newFile);

    Ui::MainWindow* ui;

    // Main Widgets
    ContentViewer* m_contentViewer;
    DirectoryTableView* m_directoryView;
    OutputWindow* m_outputWindow;
    QWidget* m_centralWidget;
    QGridLayout* m_layout;

    // Main Data Management
    SyftLogger* m_logger;
    SyftOrganizer* m_organizer;
    SyftActionManager* m_actionManager;
    QFileDialog* m_directoryDialog;

    // Subprocesses
    CommandLineManager* m_commandLineManager;

private slots:
    void FileChangedSlot(SyftFile* newFile);
    void NextFileSlot();
    void PreviousFileSlot();
    void DeleteFileSlot();
    void UndoSlot();
    void RedoSlot();
    void TitleLabelEnterSlot();
    void StartMoveFileSlot();
    void StartMoveSubdirSlot();
    void RPressSlot();
    void NPressSlot();
    void ZPressSlot();
    void ActivateChangeDirSlot();
    void DirectorySelectedSlot(const QUrl& url);
    void UpDirSlot();
    void DefaultProgSlot();

    // Hotkeys
    void ZeroActionSlot();

    void keyPressEvent(QKeyEvent *e);

};
#endif // MAINWINDOW_H
