#ifndef SYFTDIR_H
#define SYFTDIR_H

#include <QString>
#include <QDir>
#include <QFileInfo>

class SyftDir : public QDir
{

public:
    SyftDir(QString path);
    QString basename();

    QFileInfo* info();

private:
    int numFiles;

};

#endif // SYFTDIR_H
