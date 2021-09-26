#ifndef SYFTLOGGER_H
#define SYFTLOGGER_H

#include <QObject>
#include <QString>
#include <QStringList>

// Currently doesn't log anything to a file. What a shame..
class SyftLogger : public QObject
{
    Q_OBJECT
private:
    SyftLogger();

public:
    static SyftLogger* GetLogger();

    void LogMessage(QString message);
    void LogError(QString errorMessage);

signals:
    void LogLine(QString message);

public:
    static SyftLogger* s_logger;
};

#endif // SYFTLOGGER_H
