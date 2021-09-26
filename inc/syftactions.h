#ifndef SYFTACTIONS_H
#define SYFTACTIONS_H

#include <QString>

#include "syftfile.h"
#include "syftaction.h"
#include "syftorganizer.h"


// Create Subdirectory
class CreateSubdirectoryAction : public SyftAction {
public:
    CreateSubdirectoryAction(QString baseDirectory,
                             QString subDirectory);
    virtual int Perform();
    virtual int Revert();
    virtual QString Message();

private:
    QString m_baseDirectory;
    QString m_subDirectory;
};

// Move Sorter to another directory
class ChangeDirectoryAction : public SyftAction {
public:
    ChangeDirectoryAction(SyftOrganizer* organizer,
                          QString originalPath,
                          QString newPath);
    virtual int Perform();
    virtual int Revert();
    virtual QString Message();

private:
    SyftOrganizer* m_organizer;
    QString m_originalPath;
    QString m_newPath;
};

// Rename File
class RenameFileAction : public SyftAction {
public:
    RenameFileAction(SyftFile* file, QString newName);
    virtual int Perform();
    virtual int Revert();
    QString NewName() { return m_newName; }
    SyftFile* CurrentFile() { return m_file; }
    virtual QString Message();

private:
    SyftFile* m_file;
    QString m_originalName;
    QString m_newName;
};

// Rename Directory
class RenameDirectoryAction : public SyftAction {
public:
    RenameDirectoryAction(SyftDir* originalName, QString newName);
    virtual int Perform();
    virtual int Revert();
    virtual QString Message();

private:
    QString m_newName;
    SyftDir* m_dir;
    QString m_originalName;
};

// Move File
class MoveFileAction : public RenameFileAction {
public:
    MoveFileAction(SyftFile* file, QString newName, SyftOrganizer* organizer);
    virtual int Perform();
    virtual int Revert();
    virtual SyftAction* RepeatAction(QString filename);
    virtual bool CanRepeat() { return true; }
    virtual QString Message();

private:
    SyftOrganizer* m_organizer;
    SyftFile* m_file;
};

class DeleteFileAction : public SyftAction {
    QString m_fileName;
    QByteArray m_data;
public:
    DeleteFileAction(SyftFile* file, SyftOrganizer* organizer);
    virtual int Perform();
    virtual int Revert();
    virtual QString Message();
private:
    SyftOrganizer* m_organizer;
};

// Multiple Actions Chained together
class GroupAction : public SyftAction {
public:
    GroupAction();
    virtual int Perform();
    virtual int Revert();
    virtual bool CanRepeat();
    void AddAction(SyftAction* action);

protected:
    QList<SyftAction*> Actions() { return m_actions; };

private:
    QList<SyftAction*> m_actions;
    QList<SyftAction*> Reversed();
};

class MoveGroupAction : public GroupAction {
public:
    MoveGroupAction(QList<SyftFile*> files, SyftDir* dir, SyftOrganizer* organizer);
    virtual QString Message();
private:
    SyftDir* m_dir;
};

#endif // SYFTACTIONS_H
