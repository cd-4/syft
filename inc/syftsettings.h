#ifndef SYFTSETTINGS_H
#define SYFTSETTINGS_H

#include <QSettings>
#include <QApplication>

#include "outputwindow.h"
#include "syftdir.h"

class SyftSettings : public QSettings
{
private:
    SyftSettings();

public:
    static SyftSettings* GetSettings();

    void SetLastDirectory(QString dir);
    QString GetLastDirectory();

public:
    static SyftSettings* s_settings;

private:
    QApplication* m_application;

};

#endif // SYFTSETTINGS_H
