#ifndef CONTENTVIEWER_H
#define CONTENTVIEWER_H

#include <QGraphicsVideoItem>
#include <QGraphicsView>
#include <QLineEdit>
#include <QLabel>
#include <QMediaPlayer>
#include <QPixmap>
#include <QVideoWidget>
#include <QWidget>

#include "directorytableview.h"
#include "syftfile.h"
#include "videoplayer.h"
#include "webmvideoplayer.h"

class ContentViewer : public QWidget
{
    Q_OBJECT
public:
    explicit ContentViewer(QWidget *parent = nullptr);

    SyftFile* CurrentFile() const {
        return m_currentFile;
    }

    void SetCurrentFile(SyftFile* file);

    void ScaleImage(float scaleAmount);
    void NudgeZoomIn() { ScaleImage(1.2); }
    void NudgeZoomOut() { ScaleImage(0.75); }

    void SetScrollPosition(int x, int y);
    void ScrollVertical(int amount);
    void ScrollHorizontal(int amount);

    bool IsEditingFilename();
    void TryCancel();

    QLineEdit* TitleLabel() { return m_titleLabel; }

    void ResetFocus();
    void StartRenameFile();
    void ResetImageFocus();
    void PlayPause();
    void ToggleMute();

    bool IsVideo();
    bool IsImage();

private:
    void ProcessNewImage();
    void ProcessNewVideo();
    void ProcessNewWeb();
    void ChangeTab(int newTab);

public slots:
    // Image Manipulation
    void ZoomInSlot();
    void ZoomOutSlot();
    void WPressSlot();
    void APressSlot();
    void SPressSlot();
    void DPressSlot();

    // File Manipulation
    void UpdateFileText();

private:
    // Interaction
    QString m_titleString;
    QString m_dirLabelString;
    QLabel* m_dirLabel;
    bool m_canZoomIn;

    // File Info
    SyftFile* m_currentFile;

    // Formatting
    QLayout* m_layout;
    QTabWidget* m_tabWidget;

    // Title
    QLineEdit* m_titleLabel;


    // Images
    QPixmap* m_originalPixmap;			// The full size original pixmap
    QGraphicsView* m_graphicsView;
    QGraphicsScene* m_imageScene;
    QGraphicsPixmapItem* m_pixmapItem;			// The pixmap shown in the view

    // Videos
    VideoPlayer* m_videoPlayer;

    // Web
    WebmVideoPlayer* m_webView;

};

#endif // CONTENTVIEWER_H
