#ifndef SYFTACTION_H
#define SYFTACTION_H

#include <QString>

class SyftAction
{
public:
    virtual int Perform() = 0;
    virtual int Revert() = 0;
};


#endif // SYFTACTION_H
