#include "contentviewer.h"

#include <QMultimedia>
#include <QApplication>
#include <QMediaPlayer>
#include <QScrollBar>
#include <QLabel>
#include <QPixmap>
#include <QElapsedTimer>
#include <QVideoWidget>
#include <QPixmap>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QDebug>

#include "videoplayer.h"


// Just works out to be a good value
int HORIZONTAL_NUDGE_AMOUNT = 100;
int VERTICAL_NUDGE_AMOUNT = 100;


ContentViewer::ContentViewer(QWidget *parent)
    : QWidget(parent),
      m_currentViewer(0),
      m_titleString(""),
      m_dirLabelString(""),
      m_canZoomIn(true),
      m_currentFile(0),
      m_layout(0),
      m_tabWidget(0),
      m_videoPlayer(0),
      m_webView(0)
{

    // Title/Edit widget
    m_titleString = QString("Syft");
    m_titleLabel = new QLineEdit(m_titleString, this);
    m_titleLabel->setAlignment(Qt::AlignCenter);
    m_titleLabel->setStyleSheet("* { background-color: rgba(0, 0, 0, 0); }");

    QHBoxLayout* topBarLayout = new QHBoxLayout(this);
    topBarLayout->addWidget(m_titleLabel);

    QWidget* w = new QWidget(this); w->setLayout(topBarLayout);

    // Add Scroll Area to Main Widget

    m_layout = new QVBoxLayout(this);
    m_layout->addWidget(w);

    m_webView = new WebmVideoPlayer(this);
    m_imageViewer = new ImageViewer(this);
    // Video Player
    m_videoPlayer = new VideoPlayer(this);

    addPage(m_imageViewer, "Image");
    addPage(m_videoPlayer, "Video");
    addPage(m_webView, "Webm");
    m_currentViewer = m_imageViewer;
    //m_tabWidget->addTab(m_webView, "Web");
    m_tabWidget->tabBar()->hide();
    m_tabWidget->setCurrentIndex(0);

    m_layout->addWidget(m_tabWidget);

    setLayout(m_layout);

}

void ContentViewer::addPage(FileViewer* page, QString name) {
    if (!m_tabWidget) {
        m_tabWidget = new QTabWidget(this);
    }
    int ind = m_tabWidget->count();
    SyftFileType type = page->GetType();
    m_tabWidget->addTab(page, name);
    m_tabIndices[type] = ind;
    m_tabs[type] = page;
}

void ContentViewer::SetCurrentFile(SyftFile* file) {
    m_currentViewer->StopAll();
    m_currentFile = file;
    SyftFileType type = file->FileType();
    ChangeTab(type);
    m_currentViewer->SetCurrentFile(file);
    m_titleLabel->setText(CurrentFile()->info()->fileName());
}

void ContentViewer::ResetImageFocus() {
    m_currentViewer->TryCancel();
}

int ContentViewer::FileTypeIndex()
{
    int output = 0;
    SyftFile* file = CurrentFile();
    switch(file->FileType()) {
    case SyftFileType::Image:
        output = 0;
        break;
    case SyftFileType::Video:
        output = 1;
        break;
    case SyftFileType::Web:
        output = 2;
        break;
    case SyftFileType::Document:
        break;
    case SyftFileType::Text:
        break;
    default:
        output = 1;
        break;
    }
    return output;
}

void ContentViewer::StartRenameFile() {
    int end = m_titleLabel->text().indexOf(".");
    m_titleLabel->setSelection(0, end);
    m_titleLabel->setFocus();
}

void ContentViewer::UpdateFileText() {
    m_titleLabel->setText(CurrentFile()->info()->fileName());
}

bool ContentViewer::IsEditingFilename() {
    return m_titleLabel->hasFocus();
}


void ContentViewer::ChangeTab(SyftFileType type) {
    if (m_tabIndices.contains(type)) {
        int newIndex = m_tabIndices[type];
        if (m_tabWidget->currentIndex() == newIndex) {
            return;
        }
        m_tabWidget->setCurrentIndex(newIndex);
        m_currentViewer = m_tabs[type];
    }
}

void ContentViewer::ResetFocus() {
    //m_graphicsView->setFocus();
}

void ContentViewer::ZoomInSlot() {
    CurrentView()->ZoomInSlot();
}

void ContentViewer::ZoomOutSlot() {
    CurrentView()->ZoomOutSlot();
}

void ContentViewer::WPressSlot() {
    CurrentView()->UpSlot();
}

void ContentViewer::APressSlot() {
    CurrentView()->LeftSlot();
}

void ContentViewer::SPressSlot() {
    CurrentView()->DownSlot();
}

void ContentViewer::DPressSlot() {
    CurrentView()->RightSlot();
}

void ContentViewer::TryCancel() {
    if (IsEditingFilename()) {
        m_titleLabel->setText(CurrentFile()->info()->fileName());
        ResetFocus();
    }
}

void ContentViewer::PlayPause() {
    CurrentView()->PlayPauseSlot();
}

void ContentViewer::ToggleMute() {
    CurrentView()->ToggleSoundSlot();
}












