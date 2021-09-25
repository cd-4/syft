#ifndef WEBMVIDEOPLAYER_H
#define WEBMVIDEOPLAYER_H

#include <QWebEngineView>
#include <QWebEnginePage>
#include <QMediaPlayer>

#include "syftfile.h"
#include "fileviewer.h"

class WebmVideoPlayer : public FileViewer
{
public:
    WebmVideoPlayer(QWidget* parent);

    QWebEngineView* m_webWidget;
    QWebEnginePage* m_webPage;

    virtual SyftFileType GetType();
    virtual void ProcessNewFile();
    virtual void TryCancel();
    virtual void PlayPauseSlot();
    virtual void ToggleSoundSlot();
    virtual void RightSlot();
    virtual void LeftSlot();
    virtual void StopAll();
};

#endif // WEBMVIDEOPLAYER_H
