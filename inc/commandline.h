#ifndef COMMANDLINE_H
#define COMMANDLINE_H

#include <QProcess>
#include <QString>
#include <QStringList>

#include "syftorganizer.h"

class CommandLine
{
public:
    CommandLine(SyftOrganizer* org);

    virtual void setCommand(QString command) { m_command = command; }

    int run();
    int runAll(QStringList arguments);
    int runEach(QStringList arguments);
    void changeDir(QString dir);

    QString output() { return m_output; }
    QStringList lines();

protected:
    virtual void Start(QString command);

private:
    int Wait();

private:
    QProcess m_process;
    SyftOrganizer* m_organizer;
    QString m_command;
    QString m_output;
};

#endif // COMMANDLINE_H
