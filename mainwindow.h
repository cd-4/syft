#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QFileDialog>
#include <QKeyEvent>

#include "contentviewer.h"
#include "syftorganizer.h"
#include "syftactionmanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum ActionMode {
    DefaultMode, RenameFileMode, MoveFileMode, RenameDirMode
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void NextFile();
    void PreviousFile();
    ActionMode Mode() {return m_mode;}

private:
    void ChangeFile(SyftFile* newFile);
    void ChangeMode(ActionMode newMode);

    ActionMode m_mode;
    Ui::MainWindow *ui;

    // Main Widgets
    ContentViewer *m_contentViewer;
    DirectoryTableView *m_directoryView;

    QWidget *m_centralWidget;
    QGridLayout *m_layout;

    // Main Data Management
    SyftOrganizer *m_organizer;
    SyftActionManager *m_actionManager;
    QFileDialog *m_directoryDialog;

private slots:
    void FileChangedSlot(SyftFile* newFile);
    void NextFileSlot();
    void PreviousFileSlot();
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

    void keyPressEvent(QKeyEvent *e);

};
#endif // MAINWINDOW_H
