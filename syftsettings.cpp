#include "syftsettings.h"

bool SyftSettings::s_settingsExist = false;
SyftSettings* SyftSettings::s_settings = 0;

SyftSettings::SyftSettings() : QSettings("MemeLord", "Syft")
{
}

SyftSettings* SyftSettings::GetSettings() {
    if (!s_settingsExist) {
        s_settings = new SyftSettings();
    }
    return s_settings;

}
