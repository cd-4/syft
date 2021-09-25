#ifndef PYTHONCOMMANDLINE_H
#define PYTHONCOMMANDLINE_H

#include "syftorganizer.h"

#include "commandline.h"

class PythonCommandLine : public CommandLine
{
public:
    PythonCommandLine(SyftOrganizer* org, QString pythonLocation);

    virtual void Start(QString command);

private:
    QString m_pythonLocation;
};

#endif // PYTHONCOMMANDLINE_H
