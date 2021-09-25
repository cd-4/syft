
#include <QMessageBox>
#include <QAbstractButton>
#include <QHeaderView>
#include <QKeySequence>
#include <QDesktopWidget>
#include <QDesktopServices>
#include <QFileDialog>

#include "syftactions.h"
#include "syftorganizer.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_contentViewer(0),
    m_organizer(0),
    m_actionManager(0),
    m_directoryDialog(0)
{
    ui->setupUi(this);

    // Create Action Manager
    m_actionManager = new SyftActionManager();

    // Organizer
    m_organizer = new SyftOrganizer(m_actionManager, this);

    m_directoryDialog = new QFileDialog(this);
    m_directoryDialog->setFileMode(QFileDialog::Directory);
    m_directoryDialog->setDirectory(m_organizer->CurrentDirectory()->path());

    // Set Central Widget
    m_centralWidget = new QWidget(this);
    m_layout = new QGridLayout(m_centralWidget);
    m_centralWidget->setLayout(m_layout);
    setCentralWidget(m_centralWidget);

    // Create Content Viewer
    m_contentViewer = new ContentViewer(m_centralWidget);
    m_layout->addWidget(m_contentViewer, 0, 1, 1, 1);

    m_directoryView = new DirectoryTableView(this);
    m_directoryView->SetOrganizer(m_organizer);
    m_directoryView->show();
    m_directoryView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //QHeaderView* header = m_directoryView->horizontalHeader();
    //header->setSectionResizeMode(QHeaderView::Stretch);

    //m_directoryView->setStyleSheet("QHeaderView::section { background-color:red }");

    m_layout->addWidget(m_directoryView, 0, 0, 1, 1);
    m_directoryView->resize(100, m_directoryView->width());


    // Bullshit for testing poirposes
    SyftFile* file = new SyftFile("/Users/chaz/Desktop/TestDir/dark_truth_about_china.png");
    m_contentViewer->show();
    m_contentViewer->SetCurrentFile(file);
    m_contentViewer->setFocus();

    // Set Up Signals
    connect(m_organizer, 	SIGNAL(FileChangedSignal(SyftFile*)),
            this, 			SLOT(FileChangedSlot(SyftFile*)));
    connect(m_contentViewer->TitleLabel(), SIGNAL(returnPressed()),
            this,  						   SLOT(TitleLabelEnterSlot()));
    connect(m_actionManager,     SIGNAL(RefreshFileTitle()),
            m_contentViewer,     SLOT(UpdateFileText()));

    connect(m_directoryDialog, SIGNAL(urlSelected(const QUrl&)),
            this,			   SLOT(DirectorySelectedSlot(const QUrl&)));

    connect(m_organizer, SIGNAL(DirectoryChangedSignal(SyftDir*)),
            m_directoryView,   SLOT(DirectoryChangedSlot(SyftDir*)));

    QAction *nextFileAction = new QAction(this);
    addAction(nextFileAction);
    nextFileAction->setShortcut(Qt::Key_J);
    connect(nextFileAction, SIGNAL(triggered()),
            this, 			SLOT(NextFileSlot()));

    QAction *previousFileAction = new QAction(this);
    addAction(previousFileAction);
    previousFileAction->setShortcut(Qt::Key_K);
    connect(previousFileAction, SIGNAL(triggered()),
            this, 	       		SLOT(PreviousFileSlot()));

    QAction *undoAction = new QAction(this);
    addAction(undoAction);
    undoAction->setShortcut(Qt::Key_U);
    connect(undoAction, 	SIGNAL(triggered()),
            this,			SLOT(UndoSlot()));

    QAction *redoAction = new QAction(this);
    addAction(redoAction);
    redoAction->setShortcut(QKeySequence("Shift+U"));
    connect(redoAction, 	SIGNAL(triggered()),
            this,			SLOT(RedoSlot()));

    QAction *zoomInAction = new QAction(this);
    addAction(zoomInAction);
    zoomInAction->setShortcut(Qt::Key_I);
    connect(zoomInAction,    SIGNAL(triggered()),
            m_contentViewer, SLOT(ZoomInSlot()));

    QAction *zoomOutAction = new QAction(this);
    addAction(zoomOutAction);
    zoomOutAction->setShortcut(Qt::Key_O);
    connect(zoomOutAction,   SIGNAL(triggered()),
            m_contentViewer, SLOT(ZoomOutSlot()));

    QAction *scrollUpAction = new QAction(this);
    addAction(scrollUpAction);
    scrollUpAction->setShortcut(Qt::Key_W);
    connect(scrollUpAction,  SIGNAL(triggered()),
            m_contentViewer, SLOT(WPressSlot()));

    QAction *scrollDownAction = new QAction(this);
    addAction(scrollDownAction);
    scrollDownAction->setShortcut(Qt::Key_S);
    connect(scrollDownAction, SIGNAL(triggered()),
            m_contentViewer,  SLOT(SPressSlot()));

    QAction *scrollRightAction = new QAction(this);
    addAction(scrollRightAction);
    scrollRightAction->setShortcut(Qt::Key_D);
    connect(scrollRightAction, SIGNAL(triggered()),
            m_contentViewer,   SLOT(DPressSlot()));

    QAction *scrollLeftAction = new QAction(this);
    addAction(scrollLeftAction);
    scrollLeftAction->setShortcut(Qt::Key_A);
    connect(scrollLeftAction, SIGNAL(triggered()),
            m_contentViewer,  SLOT(APressSlot()));

    QAction *renameAction = new QAction(this);
    addAction(renameAction);
    renameAction->setShortcut(Qt::Key_R);
    connect(renameAction, SIGNAL(triggered()),
            this,         SLOT(RPressSlot()));

    QAction *startMoveFileAction = new QAction(this);
    addAction(startMoveFileAction);
    startMoveFileAction->setShortcut(Qt::Key_M);
    connect(startMoveFileAction, SIGNAL(triggered()),
            this,     			 SLOT(StartMoveFileSlot()));

    QAction *newDirAction = new QAction(this);
    addAction(newDirAction);
    newDirAction->setShortcut(Qt::Key_N);
    connect(newDirAction, SIGNAL(triggered()),
            this,     	  SLOT(NPressSlot()));

    QAction *muteAction = new QAction(this);
    addAction(muteAction);
    muteAction->setShortcut(Qt::Key_Z);
    connect(muteAction, SIGNAL(triggered()),
            this,     	  SLOT(ZPressSlot()));

    QAction *changeDirAction = new QAction(this);
    addAction(changeDirAction);
    changeDirAction->setShortcut(Qt::Key_Slash);
    connect(changeDirAction, SIGNAL(triggered()),
            this, 			 SLOT(ActivateChangeDirSlot()));

    QAction *upDirAction = new QAction(this);
    addAction(upDirAction);
    upDirAction->setShortcut(Qt::Key_Period);
    connect(upDirAction, SIGNAL(triggered()),
            this,		 SLOT(UpDirSlot()));

    QAction *defaultProgramAction = new QAction(this);
    addAction(defaultProgramAction);
    defaultProgramAction->setShortcut(Qt::Key_P);
    connect(defaultProgramAction, SIGNAL(triggered()),
            this,		 		  SLOT(DefaultProgSlot()));

    QAction *deleteFileAction = new QAction(this);
    addAction(deleteFileAction);
    deleteFileAction->setShortcut(Qt::Key_Delete);
    deleteFileAction->setShortcut(Qt::Key_Backspace);
    connect(deleteFileAction, SIGNAL(triggered()),
            this,		      SLOT(DeleteFileSlot()));

    resize(QDesktopWidget().availableGeometry(this).size() * 0.7);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ChangeFile(SyftFile* newFile) {
    m_contentViewer->SetCurrentFile(newFile);
}

void MainWindow::FileChangedSlot(SyftFile* newFile) {
    ChangeFile(newFile);
}

void MainWindow::NextFileSlot() {
    if (m_directoryView->hasFocus()) {
        m_directoryView->NextDir();
    } else {
        m_organizer->NextFile();
    }
}

void MainWindow::PreviousFileSlot() {
    if (m_directoryView->hasFocus()) {
        m_directoryView->PrevDir();
    } else {
        m_organizer->PreviousFile();
    }
}

void MainWindow::UndoSlot() {
    m_actionManager->UndoAction();
    m_contentViewer->UpdateFileText();
    m_directoryView->RefreshView();
}

void MainWindow::RedoSlot() {
    m_actionManager->RedoAction();
    m_contentViewer->UpdateFileText();
    m_directoryView->RefreshView();
}

void MainWindow::TitleLabelEnterSlot() {
    if (m_contentViewer->IsEditingFilename()) {
        QLineEdit* edit = m_contentViewer->TitleLabel();
        SyftFile* currentFile = m_organizer->CurrentFile();
        QString newFilename = currentFile->Dir() + edit->text();
        m_organizer->RenameFile(currentFile, newFilename);
    }
}

void MainWindow::RPressSlot() {
    if (m_directoryView->hasFocus()) {
        m_directoryView->StartRenameDir();
    } else {
        m_contentViewer->StartRenameFile();
    }
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Escape) {
        if (m_contentViewer->hasFocus()) {
            m_contentViewer->TryCancel();
        }
        m_contentViewer->setFocus();
    } else if (e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return) {
        if (m_directoryView->hasFocus()) {
            if (e->modifiers() == Qt::ShiftModifier) {
                SyftDir* selected = m_directoryView->SelectedDir();
                m_organizer->ChangeDirectory(selected);
            } else {
                m_contentViewer->setFocus();
                SyftDir* selected = m_directoryView->SelectedDir();
                QString newDir = selected->absolutePath() + QDir::separator();
                SyftFile* currentFile = m_organizer->CurrentFile();
                QString filename = currentFile->info()->fileName();
                QString newFilename = newDir + filename;
                m_organizer->MoveFile(currentFile, newFilename);
            }
        }
    } else if (e->key() == Qt::Key_Space) {
        m_contentViewer->PlayPause();
    }
}

void MainWindow::StartMoveFileSlot()
{
    m_directoryView->EnterView();
}

void MainWindow::StartMoveSubdirSlot()
{

}

void MainWindow::NPressSlot()
{
    m_directoryView->NewDir();
}

void MainWindow::ZPressSlot()
{
    m_contentViewer->ToggleMute();
}

void MainWindow::ActivateChangeDirSlot()
{
    m_directoryDialog->exec();
}

void MainWindow::DirectorySelectedSlot(const QUrl& url)
{
    m_organizer->ChangeDirectory(url.path());
}

void MainWindow::UpDirSlot()
{
    m_organizer->UpDir();
}

void MainWindow::DefaultProgSlot()
{
    qDebug() << "Default Program Open";
    QDesktopServices::openUrl(QUrl("file:" + m_organizer->CurrentFile()->FullName()));
}

void MainWindow::DeleteFileSlot()
{
    qDebug() << "Deleting";
    QMessageBox::StandardButton reply;
    QString title = "Are you sure?"; // Ignored on OS X
    QString message = "This action cannot be undone.\nAre you sure you want to delete "
                       + m_organizer->CurrentFile()->FileName() + "?";

    QMessageBox msgBox;
    msgBox.setText(message);
    msgBox.setWindowTitle(title);
    QPushButton* pButtonYes =  msgBox.addButton(tr("Yes [Enter]"), QMessageBox::YesRole);
    QAbstractButton* yesButton = (QAbstractButton *) pButtonYes;
    msgBox.addButton(tr("No [Esc]"), QMessageBox::NoRole);
    msgBox.setDefaultButton(pButtonYes);

    msgBox.exec();

    if (msgBox.clickedButton() == yesButton) {
        m_organizer->DeleteFile(m_organizer->CurrentFile());
        m_organizer->reloadFiles(false);
    }




}


