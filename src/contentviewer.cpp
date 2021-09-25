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
      m_titleString(""),
      m_dirLabelString(""),
      m_dirLabel(0),
      m_canZoomIn(true),
      m_currentFile(0),
      m_layout(0),
      m_tabWidget(0),
      m_graphicsView(0),
      m_imageScene(0),
      m_pixmapItem(0),
      m_videoPlayer(0),
      m_webView(0)
{
    // Construct Widgets
    m_graphicsView = new QGraphicsView(this);

    // Construct Base Image Scene
    m_imageScene = new QGraphicsScene(m_graphicsView);
    m_pixmapItem = m_imageScene->addPixmap(QPixmap());
    m_graphicsView->setScene(m_imageScene);

    // Video Player
    m_videoPlayer = new VideoPlayer(this);

    // Title/Edit widget
    m_titleString = QString("Syft");
    m_titleLabel = new QLineEdit(m_titleString, this);
    m_titleLabel->setAlignment(Qt::AlignCenter);
    m_titleLabel->setStyleSheet("* { background-color: rgba(0, 0, 0, 0); }");

    QLabel* m_dirLabel = new QLabel(this);
    //m_dirLabel->setText("ASS");

    QHBoxLayout* topBarLayout = new QHBoxLayout(this);
    topBarLayout->addWidget(m_dirLabel);
    topBarLayout->addWidget(m_titleLabel);

    QWidget* w = new QWidget(this); w->setLayout(topBarLayout);

    // Add Scroll Area to Main Widget

    m_layout = new QVBoxLayout(this);
    m_layout->addWidget(w);

    m_webView = new WebmVideoPlayer(this);

    m_tabWidget = new QTabWidget(this);
    m_tabWidget->addTab(m_graphicsView, "Image");
    m_tabWidget->addTab(m_videoPlayer, "Video");
    m_tabWidget->addTab(m_webView, "Web");
    m_tabWidget->tabBar()->hide();
    m_tabWidget->setCurrentIndex(0);

    m_layout->addWidget(m_tabWidget);

    setLayout(m_layout);

}

void ContentViewer::SetCurrentFile(SyftFile* file) {
    if (CurrentFile() && CurrentFile()->FileType() == SyftFileType::Video) {
        m_videoPlayer->Pause();
    }
    m_currentFile = file;

    m_titleLabel->setText(CurrentFile()->info()->fileName());
    QString dirPath =  CurrentFile()->info()->dir().absolutePath() + QDir::separator();
    // This doesn't work but I'm not gonna pull my hair out for a dumb label
    //m_dirLabel->setText(dirPath);
    switch(CurrentFile()->FileType()) {
    case SyftFileType::Image:
        ProcessNewImage();
        break;
    case SyftFileType::Video:
        ProcessNewVideo();
        break;
    case SyftFileType::Web:
        ProcessNewWeb();
        break;
    default:
        return;
    }

}

void ContentViewer::ResetImageFocus() {
    if (IsImage()) {
        ProcessNewImage();
    } else if (IsVideo()) {
        m_videoPlayer->Restart();
    }
}


void ContentViewer::ProcessNewImage() {
    ChangeTab(0);
    m_originalPixmap = new QPixmap(CurrentFile()->fileName(), "1");

    QSize pmSize = m_originalPixmap->rect().size();
    qreal pmHeight = qreal(pmSize.height());
    qreal pmWidth = qreal(pmSize.width());

    // Size of widget, not inner size
    QSize viewSize = m_graphicsView->rect().size();
    qreal sHeight = qreal(viewSize.height() - 50);
    qreal sWidth = qreal(viewSize.width() - 50);

    bool restrictHeight = false;
    qreal scaleAmount = 1.0;
    if (pmHeight > pmWidth) {
        if (pmHeight / pmWidth < 1.8) {
        restrictHeight = true;
        }
    } else {
        if (pmWidth / pmHeight > 2.5) {
        restrictHeight = true;
        }

    }

    if (restrictHeight) {
        scaleAmount = 0.9 * sHeight / pmHeight;
    } else {
        scaleAmount = 0.9 * sWidth / pmWidth;
    }

    QTransform t;
    t.scale(scaleAmount, scaleAmount);
    QPixmap pm = m_originalPixmap->transformed(t);

    m_pixmapItem->setPixmap(pm);
    m_imageScene->setSceneRect(pm.rect());
    m_tabWidget->setCurrentIndex(0);
}

void ContentViewer::ProcessNewVideo()
{

    m_videoPlayer->SetFile(CurrentFile());
    m_videoPlayer->Mute(true); // Always start video with mute off
    ChangeTab(1);
}

void ContentViewer::ProcessNewWeb()
{

    m_webView->SetFile(CurrentFile());
    ChangeTab(2);
}

void ContentViewer::ChangeTab(int newTab) {
    if (m_tabWidget->currentIndex() == newTab) {
        return;
    }
    m_tabWidget->setCurrentIndex(newTab);
}

void ContentViewer::ScaleImage(float scaleAmount)
{
    // This is not perfect but it works good enough
    QPixmap pm;
    QScrollBar* vbar = m_graphicsView->verticalScrollBar();
    QScrollBar* hbar = m_graphicsView->horizontalScrollBar();
    QElapsedTimer timer;
    timer.start();
    int oldMaxY = vbar->maximum();
    int yVal= vbar->value();
    int oldMaxX = hbar->maximum();
    int xVal = hbar->value();

    if (scaleAmount > 1.0) {
        if (!m_canZoomIn) {
            return;
        }
        // If you zoom "normally" the sections that had been reduced to pixels when
        // zoomed out will stay pixelated on zoom in so we reload the image
        QSize currentSize = m_pixmapItem->pixmap().size();
        QSize newSize = QSize(currentSize.width() * scaleAmount, currentSize.height() * scaleAmount);
        pm =  m_originalPixmap->copy().scaled(newSize);
        m_pixmapItem->setPixmap(pm);
        m_imageScene->setSceneRect(pm.rect());
        if (timer.elapsed() > 1000) {
            m_canZoomIn = false;
        }
    } else {
        pm = m_pixmapItem->pixmap();
        QTransform t;
        t.scale(scaleAmount, scaleAmount);
        pm = pm.transformed(t);
        m_pixmapItem->setPixmap(pm);
        m_canZoomIn = true;
    }

    vbar->setValue(float(yVal) / float(oldMaxY) * vbar->maximum());
    hbar->setValue(float(xVal) / float(oldMaxX) * hbar->maximum());

}

void ContentViewer::ResetFocus() {
    m_graphicsView->setFocus();
}

void ContentViewer::ScrollVertical(int amount) {
    QScrollBar* bar = m_graphicsView->verticalScrollBar();
    int verticalScroll = bar->value();
    bar->setValue(verticalScroll + amount);
}

void ContentViewer::ScrollHorizontal(int amount) {
    QScrollBar* bar = m_graphicsView->horizontalScrollBar();
    int horizontalScroll = bar->value();
    bar->setValue(horizontalScroll+ amount);
}

void ContentViewer::ZoomInSlot() {
    NudgeZoomIn();
}

void ContentViewer::ZoomOutSlot() {
    NudgeZoomOut();
}

void ContentViewer::WPressSlot() {
    if (IsImage()) {
        ScrollVertical(-VERTICAL_NUDGE_AMOUNT);
    }
}

void ContentViewer::APressSlot() {
    if (IsImage()) {
        ScrollHorizontal(-HORIZONTAL_NUDGE_AMOUNT);
    } else if (IsVideo()) {
        if (QApplication::keyboardModifiers() == Qt::ShiftModifier) {
            qDebug() << "Shift";
        }
        m_videoPlayer->RWBig();
    }
}

void ContentViewer::SPressSlot() {
    ScrollVertical(VERTICAL_NUDGE_AMOUNT);
}

void ContentViewer::DPressSlot() {
    if (IsImage()) {
        ScrollHorizontal(HORIZONTAL_NUDGE_AMOUNT);
    } else if (IsVideo()) {
        if (QApplication::keyboardModifiers() == Qt::ShiftModifier) {
            qDebug() << "Shift";
        }
        m_videoPlayer->FFBig();
    }
}

void ContentViewer::StartRenameFile() {
    int end = m_titleLabel->text().indexOf(".");
    qDebug() << "START RENAME" << end;
    m_titleLabel->setSelection(0, end);
    m_titleLabel->setFocus();
}

void ContentViewer::UpdateFileText() {
    m_titleLabel->setText(CurrentFile()->info()->fileName());
}

bool ContentViewer::IsEditingFilename() {
    return m_titleLabel->hasFocus();
}

void ContentViewer::TryCancel() {
    // If you are editing the filename
    if (IsEditingFilename()) {
        m_titleLabel->setText(CurrentFile()->info()->fileName());
        ResetFocus();
    }
}

void ContentViewer::PlayPause() {
    if (CurrentFile()->FileType() == SyftFileType::Video) {
        m_videoPlayer->PlayPause();
    }
}

void ContentViewer::ToggleMute() {
    if (IsVideo()) {
        m_videoPlayer->ToggleMute();
    }
}

bool ContentViewer::IsVideo() {
    return CurrentFile()->FileType() == SyftFileType::Video;
}

bool ContentViewer::IsImage() {
    return CurrentFile()->FileType() == SyftFileType::Image;
}











