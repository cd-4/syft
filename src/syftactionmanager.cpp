
#include <list>
#include <QDebug>

#include "syftactionmanager.h"

SyftActionManager::SyftActionManager()
    :QObject(),
    m_logger(0)
{
    m_logger = SyftLogger::GetLogger();
}

void SyftActionManager::AddAction(SyftAction *action) {
    if (!action->Perform()) {
        m_logger->LogMessage(action->Message());
    } else {
        m_logger->LogError(action->Message());
    }
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
        emit RefreshFileTitle(); // This shouldn't be here
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

void SyftActionManager::RepeatAction(SyftFile *file) {
    qDebug() << "Repeat Attempt";
    if (!m_previousActions.size()) {
        return;
    }
    SyftAction* most_recent = m_previousActions.back();
    qDebug() << "Repeating Action";
    if (most_recent->CanRepeat()) {
        qDebug() << "Repeating Action";
        SyftAction* repeat = most_recent->RepeatAction(file->FullName());
        AddAction(repeat);
    }
}
