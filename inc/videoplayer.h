#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H


#include <QGraphicsView>
#include <QGraphicsVideoItem>
#include <QMediaPlayer>
#include <QKeyEvent>
#include <QWidget>

#include "fileviewer.h"
#include "syftfile.h"

class VideoPlayer: public FileViewer
{
public:
    VideoPlayer(QWidget* parent);

    int m_currentSkipSize;
    SyftFile* m_currentFile;
    QMediaPlayer* m_mediaPlayer;
    QVideoWidget* m_videoWidget;

    virtual SyftFileType GetType();
    virtual void ProcessNewFile();
    virtual void TryCancel();
    virtual void PlayPauseSlot();
    virtual void ToggleSoundSlot();
    virtual void RightSlot();
    virtual void LeftSlot();
    virtual void StopAll();

private:
    void Play();
    void Pause();
    void Mute(bool is_muted);
    bool IsPlaying();
    void Skip(int amount);

};

#endif // VIDEOPLAYER_H
