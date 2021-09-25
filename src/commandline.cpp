
#include <QRegularExpression>
#include <QDebug>

#include "../inc/commandline.h"

CommandLine::CommandLine(SyftOrganizer* organizer):
    m_organizer(organizer),
    m_command(""),
    m_output("")
{
    changeDir(m_organizer->CurrentDirectory()->path());
}

void CommandLine::changeDir(QString dir) {
    m_process.setWorkingDirectory(dir);
}

void CommandLine::Start(QString command) {
    m_process.start(command);
}

int CommandLine::run() {
    qDebug() << "RUN";
    qDebug() << "Command: " << m_command;
    Start(m_command);
    return Wait();
}

int CommandLine::runAll(QStringList arguments) {
    QString argString = arguments.join(" ");
    Start(m_command + " " + argString);
    return Wait();
}

int CommandLine::runEach(QStringList arguments) {
    int output = 0;
    for(QString arg : arguments) {
        // In case they leave the working dir
        m_process.setWorkingDirectory(m_organizer->CurrentDirectory()->path());
        Start(m_command + " " + arg);
        output += Wait();
    }
    return output;
}

int CommandLine::Wait() {
    m_process.waitForFinished();
    m_output = m_process.readAll();
    return m_process.exitCode();
}

QStringList CommandLine::lines() {
    QStringList out = output().split(QRegularExpression{R"-((\r\n?|\n))-"});
    out.removeAll("");
    return out;
}

