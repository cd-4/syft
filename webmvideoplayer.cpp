#include <QVBoxLayout>
#include <QDebug>

#include "webmvideoplayer.h"

WebmVideoPlayer::WebmVideoPlayer(QWidget* parent)
    :QWidget(parent),
    m_currentFile(0),
    m_mediaPlayer(0),
    m_webWidget(0)
{

    m_webWidget = new QWebEngineView(this);
    QVBoxLayout * mLayout = new QVBoxLayout(this);
    mLayout->addWidget(m_webWidget);
    setLayout(mLayout);
}

void WebmVideoPlayer::SetFile(SyftFile *newFile)
{
    m_currentFile = newFile;
    m_webWidget->setUrl(QUrl::fromLocalFile(newFile->FullName()));
}
