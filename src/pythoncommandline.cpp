#include <QDebug>

#include "../inc/pythoncommandline.h"

PythonCommandLine::PythonCommandLine(SyftOrganizer* organizer, QString pythonLocation)
    :CommandLine(organizer),
      m_pythonLocation(pythonLocation)
{
}

void PythonCommandLine::Start(QString command) {
    QString nCommand = m_pythonLocation + " " + command;
    qDebug() << "Start Python Command";
    qDebug() << nCommand;
    CommandLine::Start(nCommand);
}
