#ifndef SYFTACTION_H
#define SYFTACTION_H

#include <QString>

class SyftAction
{
public:
    virtual QString Message() { return ""; }
    virtual int Perform() { return 0; }
    virtual int Revert() { return 0; }
    virtual bool CanRepeat() { return false; }
    virtual SyftAction* RepeatAction(QString filename) { return 0; }
};


#endif // SYFTACTION_H
