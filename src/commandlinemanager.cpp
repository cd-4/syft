#include <QDebug>

#include "commandline.h"
#include "pythoncommandline.h"
#include "commandlinemanager.h"

CommandLineManager::CommandLineManager(SyftOrganizer* organizer):
    m_organizer(organizer)
{
    m_python = DiscoverPythonPath();
}

CommandLine* CommandLineManager::GetCommand() {
    return new CommandLine(m_organizer);
}
CommandLine* CommandLineManager::GetCommand(QString command) {
    CommandLine* cmd = new CommandLine(m_organizer);
    cmd->setCommand(command);
    return cmd;
}
PythonCommandLine* CommandLineManager::GetPythonCommand() {
    return new PythonCommandLine(m_organizer, Python());
}
PythonCommandLine* CommandLineManager::GetPythonCommand(QString module) {
    PythonCommandLine* cmd = new PythonCommandLine(m_organizer, Python());
    cmd->setCommand(module);
    return cmd;
}

QString CommandLineManager::DiscoverPythonPath() {
    CommandLine* cmd = new CommandLine(m_organizer);
    cmd->setCommand("which python3");
    cmd->run();
    QString python = cmd->lines()[0];
    if (python.contains("python")) {
        return python;
    }
    return "";
}
