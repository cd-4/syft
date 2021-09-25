#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPixmap>
#include <QGraphicsPixmapItem>

#include "fileviewer.h"

class ImageViewer : public FileViewer
{
public:
    ImageViewer(QWidget* parent);

    virtual void ProcessNewFile();
    virtual SyftFileType GetType();

private:
    bool m_canZoomIn;
    QGraphicsView* m_graphicsView;		// View that is shown
    QGraphicsScene* m_imageScene;		// Scene in view
    QGraphicsPixmapItem* m_pixmapItem;	// Pixmap in view
    QPixmap* m_originalPixmap;			// Original full size pixmap

    void ScrollVertical(int amount);
    void ScrollHorizontal(int amount);
    void ScaleImage(float scaleAmount);

public slots:
    virtual void TryCancel();
    virtual void ZoomInSlot();
    virtual void ZoomOutSlot();
    virtual void UpSlot();
    virtual void DownSlot();
    virtual void LeftSlot();
    virtual void RightSlot();
};

#endif // IMAGEVIEWER_H
