#ifndef SYFTSETTINGS_H
#define SYFTSETTINGS_H

#include <QSettings>

#include "syftdir.h"

class SyftSettings : public QSettings
{
public:
    SyftSettings();

    void SetLastDirectory(QString dir);
    QString GetLastDirectory();

    static SyftSettings* GetSettings();

    static bool s_settingsExist;
    static SyftSettings* s_settings;
};

#endif // SYFTSETTINGS_H
