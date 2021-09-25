#include "videoplayer.h"

#include <QGraphicsScene>
#include <QGraphicsVideoItem>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QVideoWidget>
#include <QVBoxLayout>
#include <QWidget>


VideoPlayer::VideoPlayer(QWidget* parent)
    :FileViewer(parent),
    m_currentSkipSize(0),
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

SyftFileType VideoPlayer::GetType() {
    return SyftFileType::Video;
}



void VideoPlayer::ProcessNewFile()
{
    QMediaPlaylist* playlist = new QMediaPlaylist(m_mediaPlayer);
    playlist->addMedia(QUrl::fromLocalFile(CurrentFile()->FullName()));
    m_mediaPlayer->setPlaylist(playlist);
    m_currentSkipSize = m_mediaPlayer->duration() / 10;
    Mute(true);
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

void VideoPlayer::ToggleSoundSlot()
{
    m_mediaPlayer->setMuted(!m_mediaPlayer->isMuted());
}

void VideoPlayer::Pause()
{
    if (IsPlaying()) {
        m_mediaPlayer->pause();
    }
}

void VideoPlayer::TryCancel()
{
    m_mediaPlayer->setPosition(0);
}

void VideoPlayer::PlayPauseSlot()
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

void VideoPlayer::RightSlot()
{
    Skip(m_currentSkipSize);
}

void VideoPlayer::LeftSlot()
{
    Skip(-m_currentSkipSize);
}

void VideoPlayer::StopAll()
{
    Pause();
    Mute(true);
}

