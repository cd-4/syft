
#include <QStandardPaths>

#include "syftsettings.h"

QString LAST_ACTIVE_DIRECTORY = "last_active_directory";

bool SyftSettings::s_settingsExist = false;
SyftSettings* SyftSettings::s_settings = 0;

SyftSettings::SyftSettings() : QSettings("syftking", "Syft")
{
}

SyftSettings* SyftSettings::GetSettings() {
    if (!s_settingsExist) {
        s_settings = new SyftSettings();
    }
    return s_settings;

}

void SyftSettings::SetLastDirectory(QString dir)
{
    setValue(LAST_ACTIVE_DIRECTORY, dir);
}

QString SyftSettings::GetLastDirectory()
{
    if (contains(LAST_ACTIVE_DIRECTORY)) {
        QString stored = value(LAST_ACTIVE_DIRECTORY).toString();
        if (QDir(stored).exists()) {
            return stored;
        }
    }
    QStringList dirs = QStandardPaths::standardLocations(QStandardPaths::DesktopLocation);
    return dirs.at(0);
}
