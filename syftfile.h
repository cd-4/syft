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


};

#endif // SYFTFILE_H
