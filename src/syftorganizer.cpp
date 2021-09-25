
#include <vector>

#include <QDir>
#include <QDebug>
#include <QWidget>
#include <QStandardPaths>

#include "syftactions.h"
#include "syftactionmanager.h"
#include "syftorganizer.h"
#include "syftsettings.h"

SyftOrganizer::SyftOrganizer(SyftActionManager* manager, QWidget* parent):
    m_manager(manager),
    m_parent(parent),
    m_currentDirectory(0),
    m_currentFileIndex(0)
{
    QString dirname = SyftSettings::GetSettings()->GetLastDirectory();
    ChangeDirectory(dirname);
}

void SyftOrganizer::UpDir()
{
    m_currentDirectory->cdUp();
    ChangeDirectory(m_currentDirectory);
    emit DirectoryChangedSignal(m_currentDirectory);
}

void SyftOrganizer::ChangeDirectory(const QString newDirectory)
{
    ChangeDirectory(new SyftDir(newDirectory));
}

void SyftOrganizer::ChangeDirectory(SyftDir* newDir)
{
    int files = newDir->entryInfoList().count();
    if (!files) {
        return;
    }
    m_parent->setWindowTitle("Syft -- " + newDir->path());
    m_currentDirectory = newDir;
    reloadFiles(true);
    SyftSettings::GetSettings()->SetLastDirectory(m_currentDirectory->path());
    emit DirectoryChangedSignal(m_currentDirectory);
}

void SyftOrganizer::reloadFiles(bool resetIndex)
{
    m_files.clear();
    m_dirs.clear();

    QFileInfoList list = m_currentDirectory->entryInfoList();
    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);
        if (fileInfo.isDir()) {
            SyftDir* dir = new SyftDir(fileInfo.absoluteFilePath());
            if (fileInfo.absoluteFilePath().compare(m_currentDirectory->path())==0) {
                continue;
            }
            if (!fileInfo.absoluteFilePath().contains(m_currentDirectory->path())) {
                continue;
            }
            m_dirs.push_back(dir);
        } else {
            SyftFile* file = new SyftFile(fileInfo.absoluteFilePath());
            m_files.push_back(file);
        }
    }
    if (resetIndex || m_currentFileIndex >= NumFiles()) {
        m_currentFileIndex = 0;
    }
    if (m_files.size() != 0) {
        SetFileIndex(m_currentFileIndex);
    }
}

void SyftOrganizer::ChangeFileIndexBy(int amount)
{
    SetFileIndex(m_currentFileIndex + amount);
}

void SyftOrganizer::SetFileIndex(int index)
{
    // Modulo doesn't work with negatives for some reason
    if (index < 0) {
        index = m_files.size() + index;
    }
    m_currentFileIndex = index % m_files.size();
    SyftFile* file = m_files[m_currentFileIndex];
    emit FileChangedSignal(file);
}

void SyftOrganizer::NextFile() { ChangeFileIndexBy(1); }

void SyftOrganizer::PreviousFile() { ChangeFileIndexBy(-1); }

SyftFile* SyftOrganizer::File(int index) const {
    return m_files[index];
}

SyftFile* SyftOrganizer::CurrentFile() const {
    return File(m_currentFileIndex);
}

SyftDir* SyftOrganizer::CurrentDirectory() const {
    return m_currentDirectory;
}

SyftDir* SyftOrganizer::Directory(int index) const {
    return m_dirs[index];
}

void SyftOrganizer::RenameFile(SyftFile* file, QString newFile) {
    RenameFileAction *action = new RenameFileAction(file, newFile);
    m_manager->AddAction(action);
}

void SyftOrganizer::MoveFile(SyftFile* file, QString newFile) {
    MoveFileAction *action = new MoveFileAction(file, newFile, this);
    m_manager->AddAction(action);
}

void SyftOrganizer::DeleteFile(SyftFile *file) {
    DeleteFileAction *action = new DeleteFileAction(file);
    m_manager->AddAction(action);
    //SetFileIndex(m_currentFileIndex + amount);
}

void SyftOrganizer::RenameDir(SyftDir* dir, QString newName) {
    RenameDirectoryAction *action = new RenameDirectoryAction(dir, newName);
    m_manager->AddAction(action);
}

void SyftOrganizer::RepeatAction() {
    m_manager->RepeatAction(CurrentFile());
}

void SyftOrganizer::SetCurrentFile(SyftFile *file) {
    QString startFilename = file->FullName();
    for (int i=0; i<NumFiles(); i++) {
        SyftFile* f = m_files[i];
        QString testFilename = f->FullName();
        if(testFilename.compare(startFilename) == 0) {
            m_currentFileIndex = i;
            emit FileChangedSignal(file);
        }
    }
}

SyftDir* SyftOrganizer::NewDir() {
    QString newName = "untitled";
    int ind = 0;
    while (m_currentDirectory->exists(newName)) {
        newName = "untitled_" + QString::number(ind);
        ind++;
    }
    CreateSubdirectoryAction *action = new CreateSubdirectoryAction(m_currentDirectory->path(), newName);
    m_manager->AddAction(action);
    SyftDir *newDir = new SyftDir(m_currentDirectory->path() + QDir::separator() + newName);
    m_dirs.push_back(newDir);
    return newDir;
}
