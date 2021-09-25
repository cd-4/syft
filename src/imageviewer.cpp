
#include <QVBoxLayout>
#include <QScrollBar>
#include <QElapsedTimer>

#include "imageviewer.h"

int IMAGE_HORIZONTAL_NUDGE_AMOUNT = 100;
int IMAGE_VERTICAL_NUDGE_AMOUNT = 100;

ImageViewer::ImageViewer(QWidget* parent) : FileViewer(parent),
    m_canZoomIn(true),
    m_graphicsView(0),
    m_imageScene(0),
    m_pixmapItem(0),
    m_originalPixmap(0)
{
    m_graphicsView = new QGraphicsView(this);
    m_imageScene = new QGraphicsScene(m_graphicsView);
    m_pixmapItem = m_imageScene->addPixmap(QPixmap());
    m_graphicsView->setScene(m_imageScene);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(m_graphicsView);
    setLayout(layout);
}

SyftFileType ImageViewer::GetType()
{
    return SyftFileType::Image;
}

void ImageViewer::ProcessNewFile()
{
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
}


void ImageViewer::TryCancel() {
    ProcessNewFile();
}

void ImageViewer::ZoomInSlot() {
    ScaleImage(1.2);
}

void ImageViewer::ZoomOutSlot() {
    ScaleImage(0.75);
}

void ImageViewer::UpSlot() {
    ScrollVertical(-IMAGE_VERTICAL_NUDGE_AMOUNT);
}

void ImageViewer::DownSlot() {
    ScrollVertical(IMAGE_VERTICAL_NUDGE_AMOUNT);
}

void ImageViewer::LeftSlot() {
    ScrollHorizontal(-IMAGE_HORIZONTAL_NUDGE_AMOUNT);
}

void ImageViewer::RightSlot() {
    ScrollHorizontal(IMAGE_HORIZONTAL_NUDGE_AMOUNT);
}

void ImageViewer::ScrollVertical(int amount) {
    QScrollBar* bar = m_graphicsView->verticalScrollBar();
    int verticalScroll = bar->value();
    bar->setValue(verticalScroll + amount);
}

void ImageViewer::ScrollHorizontal(int amount) {
    QScrollBar* bar = m_graphicsView->horizontalScrollBar();
    int horizontalScroll = bar->value();
    bar->setValue(horizontalScroll+ amount);
}

void ImageViewer::ScaleImage(float scaleAmount) {
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
