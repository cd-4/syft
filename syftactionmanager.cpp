
#include <list>

#include "syftactionmanager.h"

SyftActionManager::SyftActionManager()
{
}

void SyftActionManager::AddAction(SyftAction *action) {
    action->Perform();
    m_previousActions.push_back(action);
    if (m_undoneActions.size() > 0) {
        m_undoneActions.clear();
    }
}

void SyftActionManager::UndoAction() {
    if (m_previousActions.size() > 0) {
        SyftAction* mostRecentAction = m_previousActions.back();
        mostRecentAction->Revert();
        m_previousActions.pop_back();
        m_undoneActions.push_back(mostRecentAction);
        emit RefreshFileTitle();
    }
}

void SyftActionManager::RedoAction() {
    if (m_undoneActions.size() > 0) {
        SyftAction* mostRecentUndoneAction = m_undoneActions.back();
        mostRecentUndoneAction->Perform();
        m_undoneActions.pop_back();
        m_previousActions.push_back(mostRecentUndoneAction);
    }
}

