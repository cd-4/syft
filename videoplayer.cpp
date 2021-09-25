#include "videoplayer.h"

#include <QGraphicsScene>
#include <QGraphicsVideoItem>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QVideoWidget>
#include <QVBoxLayout>
#include <QWidget>
#include <QDebug>


VideoPlayer::VideoPlayer(QWidget* parent)
    :QWidget(parent),
    m_currentSkipSize(0),
    m_currentFile(0),
    m_mediaPlayer(0),
    m_videoWidget(0)
{
    m_mediaPlayer = new QMediaPlayer(this);
    m_videoWidget = new QVideoWidget(this);

    m_mediaPlayer->setVideoOutput(m_videoWidget);

    QVBoxLayout * mLayout=new QVBoxLayout(this);
    mLayout->addWidget(m_videoWidget);
    setLayout(mLayout);
}



void VideoPlayer::SetFile(SyftFile* newFile)
{
    m_currentFile = newFile;
    ReloadVideo();
}

void VideoPlayer::ReloadVideo()
{
    QMediaPlaylist* playlist = new QMediaPlaylist(m_mediaPlayer);
    playlist->addMedia(QUrl::fromLocalFile(m_currentFile->FullName()));
    m_mediaPlayer->setPlaylist(playlist);
    m_currentSkipSize = m_mediaPlayer->duration() / 10;
    Play();
}

bool VideoPlayer::IsPlaying()
{
    return m_mediaPlayer->state() == QMediaPlayer::PlayingState;
}

void VideoPlayer::Play()
{
    if (!IsPlaying()) {
        m_mediaPlayer->play();
    }
}

void VideoPlayer::Mute(bool is_muted)
{
    m_mediaPlayer->setMuted(is_muted);
}

void VideoPlayer::ToggleMute()
{
    m_mediaPlayer->setMuted(!m_mediaPlayer->isMuted());
}

void VideoPlayer::Pause()
{
    if (IsPlaying()) {
        m_mediaPlayer->pause();
    }
}

void VideoPlayer::Restart()
{
    m_mediaPlayer->setPosition(0);
}

void VideoPlayer::PlayPause()
{
    if (IsPlaying()) {
        m_mediaPlayer->pause();
    } else {
        m_mediaPlayer->play();
    }
}

void VideoPlayer::Skip(int amount)
{
    int old_pos = m_mediaPlayer->position();
    int new_pos = amount + old_pos;
    if (new_pos < 0) {
        new_pos = 0;
    } else if (new_pos > m_mediaPlayer->duration()) {
        new_pos = m_mediaPlayer->duration();
    }
    m_mediaPlayer->setPosition(new_pos);
}

void VideoPlayer::FFBig()
{
    Skip(m_currentSkipSize);
}

void VideoPlayer::FFLittle()
{
    Skip(m_currentSkipSize/2);
}

void VideoPlayer::RWBig()
{
    Skip(-m_currentSkipSize);
}

void VideoPlayer::RWLittle()
{
    Skip(-m_currentSkipSize/2);
}

