#include "../inc/syftlogger.h"

SyftLogger* SyftLogger::s_logger = 0;

SyftLogger::SyftLogger() : QObject()
{

}

SyftLogger* SyftLogger::GetLogger() {
    if (!s_logger) {
        s_logger = new SyftLogger();
    }
    return s_logger;
}

void SyftLogger::LogMessage(QString message) {
    emit LogLine(message);
}

void SyftLogger::LogError(QString errorMessage) {
    emit LogLine("[Error]: " + errorMessage);
}
