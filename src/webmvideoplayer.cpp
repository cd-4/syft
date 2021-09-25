
#include <QApplication>
#include <QVBoxLayout>
#include <QDebug>
#include <QAction>
#include <QKeyEvent>

#include "webmvideoplayer.h"

WebmVideoPlayer::WebmVideoPlayer(QWidget* parent)
    :FileViewer(parent),
    m_webWidget(0),
    m_webPage(0)
{
    m_webWidget = new QWebEngineView(this);
    m_webPage = new QWebEnginePage(m_webWidget);
    QVBoxLayout * mLayout = new QVBoxLayout(this);
    mLayout->addWidget(m_webWidget);
    setLayout(mLayout);
}

SyftFileType WebmVideoPlayer::GetType() {
    return SyftFileType::Web;
}

void WebmVideoPlayer::ProcessNewFile()
{
    if (CurrentFile()) {
        m_webPage->setUrl(QUrl::fromLocalFile(CurrentFile()->FullName()));
        m_webWidget->setPage(m_webPage);

        // Set the focus here because for some reason these triggerAction slots do not work with the view
        // This allows the video to automatically use the webm presets for play/pause which is the space bar
        m_webWidget->setFocus();
    }
}

void WebmVideoPlayer::TryCancel() {}

void WebmVideoPlayer::PlayPauseSlot() {
    //qDebug() << "Play Pause Webm";
    //m_webPage->triggerAction(QWebEnginePage::ToggleMediaPlayPause);
    //m_webWidget->triggerPageAction(QWebEnginePage::ToggleMediaPlayPause);
}

void WebmVideoPlayer::ToggleSoundSlot() {
    //m_webPage->triggerAction(QWebEnginePage::ToggleMediaMute);
    //m_webWidget->triggerPageAction(QWebEnginePage::ToggleMediaMute);
}

void WebmVideoPlayer::RightSlot() {}

void WebmVideoPlayer::LeftSlot() {}

void WebmVideoPlayer::StopAll() {
    // This should mute and pause the view, but I can get neither of those to work the way I'd like (or at all)
    SetCurrentFile(new SyftFile(""));
}
