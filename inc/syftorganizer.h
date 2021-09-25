#ifndef SYFTORGANIZER_H
#define SYFTORGANIZER_H

#include <vector>

#include <QWidget>
#include <QObject>
#include <QDir>

#include "syftfile.h"
#include "syftdir.h"
#include "syftfile.h"
#include "syftactionmanager.h"

class SyftOrganizer : public QObject
{
    Q_OBJECT

public:
    SyftOrganizer(SyftActionManager* manager, QWidget* parent);

    void UpDir();
    void ChangeDirectory(const QString newDirectory);
    void ChangeDirectory(SyftDir* newDir);
    void reloadFiles(bool resetIndex=true);

    // Directory Selection Model Help
    int NumDirectories() const { return m_dirs.size(); }
    int NumFiles() const { return m_files.size(); }
    SyftDir* Directory(int index) const;
    SyftFile* File(int index) const;
    SyftFile* CurrentFile() const;
    SyftDir* CurrentDirectory() const;
    void SetCurrentFile(SyftFile* file);

    // Actions
    void ChangeFileIndexBy(int amount);
    void SetFileIndex(int index);
    void NextFile();
    void PreviousFile();

    void RenameFile(SyftFile* file, QString newFile); // full paths
    void RenameDir(SyftDir* dir, QString newName); // full paths
    void MoveFile(SyftFile* file, QString newFile); // full paths
    void DeleteFile(SyftFile* file);
    void RepeatAction();

    SyftDir* NewDir(); // Creates "untitled", then we call "RenameDir" immediately so the user can name it


private:
    SyftActionManager* m_manager;
    QWidget* m_parent;
    SyftDir* m_currentDirectory;
    int m_currentFileIndex;

    std::vector<SyftFile*> m_files;
    std::vector<SyftDir*> m_dirs;

signals:
    void FileChangedSignal(SyftFile* newFile);
    void DirectoryChangedSignal(SyftDir* newDir);
};

#endif // SYFTORGANIZER_H
