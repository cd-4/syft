#ifndef WEBMVIDEOPLAYER_H
#define WEBMVIDEOPLAYER_H

#include <QWebEngineView>

#include "syftfile.h"

#include "videoplayer.h"

class WebmVideoPlayer : public QWidget
{
public:
    WebmVideoPlayer(QWidget* parent);

    SyftFile* m_currentFile;
    QMediaPlayer* m_mediaPlayer;
    QWebEngineView* m_webWidget;


    void SetFile(SyftFile* newFile);
    void ReloadVideo();
};

#endif // WEBMVIDEOPLAYER_H
