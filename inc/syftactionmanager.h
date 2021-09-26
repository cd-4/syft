#ifndef SYFTACTIONMANAGER_H
#define SYFTACTIONMANAGER_H

#include <list>

#include <QObject>

#include "syftlogger.h"
#include "syftfile.h"
#include "syftaction.h"

class SyftActionManager : public QObject
{
    Q_OBJECT
public:
    SyftActionManager();

    void AddAction(SyftAction* action);
    void UndoAction();
    void RedoAction();
    void RepeatAction(SyftFile* file);

signals:
    void RefreshFileTitle();

private:
    std::list<SyftAction*> m_previousActions;
    std::list<SyftAction*> m_undoneActions;
    SyftLogger* m_logger;
};

#endif // SYFTACTIONMANAGER_H
