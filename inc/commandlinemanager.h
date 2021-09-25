#ifndef COMMANDLINEMANAGER_H
#define COMMANDLINEMANAGER_H

#include "syftorganizer.h"
#include "commandline.h"
#include "pythoncommandline.h"

class CommandLineManager
{
public:
    CommandLineManager(SyftOrganizer* organizer);

    CommandLine* GetCommand();
    CommandLine* GetCommand(QString command);
    PythonCommandLine* GetPythonCommand();
    PythonCommandLine* GetPythonCommand(QString module);

private:
    SyftOrganizer* m_organizer;
    QString m_python;

    QString Python() { return m_python; }
    QString DiscoverPythonPath();
};

#endif // COMMANDLINEMANAGER_H
