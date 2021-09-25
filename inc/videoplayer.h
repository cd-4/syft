#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H


#include <QGraphicsView>
#include <QGraphicsVideoItem>
#include <QMediaPlayer>
//#include <QVideoWidget>
#include <QWidget>

#include "syftfile.h"

class VideoPlayer: public QWidget
{
public:
    VideoPlayer(QWidget* parent);

    int m_currentSkipSize;
    SyftFile* m_currentFile;
    QMediaPlayer* m_mediaPlayer;
    QVideoWidget* m_videoWidget;


    void SetFile(SyftFile* newFile);
    void ReloadVideo();

    bool IsPlaying();
    void Play();
    void Pause();
    void Restart();
    void PlayPause();
    void Mute(bool is_muted);
    void ToggleMute();

    void FFBig();
    void FFLittle();
    void RWBig();
    void RWLittle();

private:
    void Skip(int amount);

};

#endif // VIDEOPLAYER_H
