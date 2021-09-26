
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
    m_logger(0),
    m_manager(manager),
    m_parent(parent),
    m_currentDirectory(0),
    m_currentFileIndex(0)
{
    m_logger = SyftLogger::GetLogger();
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
    //m_parent->setWindowTitle("Syft -- " + newDir->path());
    m_parent->setWindowTitle("Syft -- ~/Path/To/Directory/");
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

void SyftOrganizer::RenameFile(QString newFile) {
    RenameFileAction *action = new RenameFileAction(CurrentFile(), newFile);
    m_manager->AddAction(action);
}

void SyftOrganizer::Move(SyftDir* dir) {
    m_lastMovementDest = new SyftDir(dir->path());
    m_lastMovementDest->cdUp();

    if (m_grabbedFiles.size() > 0) {
        MoveGroupAction* action = new MoveGroupAction(m_grabbedFiles, m_lastMovementDest, this);
        m_manager->AddAction(action);
    } else {
        QString newDir = dir->absolutePath() + QDir::separator();
        QString newFile = newDir + CurrentFile()->FileName();
        MoveFileAction *action = new MoveFileAction(CurrentFile(), newFile, this);
        m_manager->AddAction(action);
    }
}

void SyftOrganizer::DeleteFile() {
    DeleteFileAction *action = new DeleteFileAction(CurrentFile(), this);
    m_manager->AddAction(action);
}

void SyftOrganizer::RenameDir(SyftDir* dir, QString newName) {
    RenameDirectoryAction *action = new RenameDirectoryAction(dir, newName);
    m_manager->AddAction(action);
}

void SyftOrganizer::RepeatAction() {
    m_manager->RepeatAction(CurrentFile());
}

void SyftOrganizer::RepeatMovement() {
    SyftDir* dest = m_lastMovementDest;
    if (!dest) {
        return;
    }
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

void SyftOrganizer::ClearGrab() {
    m_grabbedFiles.clear();
    m_logger->LogMessage("G:[0] Cleared");
}

void SyftOrganizer::ToggleGrab() {
    SyftFile* file = CurrentFile();
    bool isAdding = false;
    if (m_grabbedFiles.contains(file)) {
        m_grabbedFiles.removeOne(file);
    } else {
        isAdding = true;
        m_grabbedFiles.append(file);
    }
    int size = m_grabbedFiles.count();
    QString message = "G:[" + QString::number(size) + "] files ";
    message += (isAdding ? "+" : "-") + file->FileName();
    m_logger->LogMessage(message);
}



