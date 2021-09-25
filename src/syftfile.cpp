
#include <QFile>
#include <QDir>
#include <QFileInfo>

#include "syftfile.h"

SyftFile::SyftFile(const QString &name)
         :QFile(name)
{

}

SyftFile::~SyftFile()
{

}

SyftFileType SyftFile::FileType() {
    QString suffix = info()->suffix();

    QStringList imageSuffixes = {
        "jpg", "png", "ppm", "xpm"
    };
    for(QString testSuffix : imageSuffixes) {
        if (suffix.compare(testSuffix) == 0) {
            return SyftFileType::Image;
        }
    }

    QStringList videoSuffixes = {
        "mp4"
    };
    for(QString testSuffix : videoSuffixes) {
        if (suffix.compare(testSuffix) == 0) {
            return SyftFileType::Video;
        }

    }

    QStringList webSuffixes = {
        "webm"
    };
    for (QString testSuffix : webSuffixes) {
        if (suffix.compare(testSuffix) == 0) {
            return SyftFileType::Web;
        }
    }
    return SyftFileType::Image;
}

QFileInfo* SyftFile::info() {
    return new QFileInfo(fileName());
}

QString SyftFile::basename() {
    return info()->baseName();
}

QString SyftFile::Dir() {
    return  QFileInfo(fileName()).dir().absolutePath() + QDir::separator();
}

QString SyftFile::FullName() {
    return info()->filePath();
}

QString SyftFile::FileName() {
    return info()->fileName();
}
