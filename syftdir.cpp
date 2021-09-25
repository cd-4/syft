#include "syftdir.h"

SyftDir::SyftDir(QString path)
    :QDir(path)
{
}

QString SyftDir::basename() {
    return info()->baseName();
}

QFileInfo* SyftDir::info() {
    return new QFileInfo(path());
}
