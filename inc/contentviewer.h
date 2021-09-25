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
#include "imageviewer.h"
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

    bool IsEditingFilename();
    void TryCancel();

    QLineEdit* TitleLabel() { return m_titleLabel; }

    void StartRenameFile();
    void ResetImageFocus();
    void PlayPause();
    void ToggleMute();

private:
    void addPage(FileViewer* page, QString name);
    void ProcessFileChange();
    int FileTypeIndex();
    void ChangeTab(SyftFileType type);
    FileViewer* CurrentView() { return m_currentViewer; }

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
    QMap<SyftFileType, int> m_tabIndices;
    QMap<SyftFileType, FileViewer*> m_tabs;
    FileViewer* m_currentViewer;

    QString m_titleString;
    QString m_dirLabelString;
    bool m_canZoomIn;

    // File Info
    SyftFile* m_currentFile;

    // Formatting
    QLayout* m_layout;
    QTabWidget* m_tabWidget;

    // Title
    QLineEdit* m_titleLabel;

    // FileViewers
    ImageViewer* m_imageViewer;
    VideoPlayer* m_videoPlayer;
    WebmVideoPlayer* m_webView;

};

#endif // CONTENTVIEWER_H
