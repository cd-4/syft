#ifndef SYFTFILE_H
#define SYFTFILE_H

#include <QFile>
#include <QFileInfo>

enum SyftFileType {
    Image,      // images
    Video,      // videos
    Web,	// webviews
    Text,       // txt and code
    Document    // pdf docx
};


class SyftFile : public QFile
{
public:
    SyftFile(const QString &name);
    ~SyftFile();

    QString basename();

    QString Dir();
    QString FullName();
    QString FileName();
    SyftFileType FileType();
    QFileInfo* info();

    static QString TypeName(SyftFileType type) {
        switch(type) {
        case SyftFileType::Image:
            return "Image";
            break;
        case SyftFileType::Video:
            return "Video";
            break;
        case SyftFileType::Web:
            return "Web";
            break;
        case SyftFileType::Document:
            return "Document";
            break;
        case SyftFileType::Text:
            return "Text";
            break;
        }
    }


};

#endif // SYFTFILE_H
