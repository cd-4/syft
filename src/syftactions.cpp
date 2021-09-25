#include <QFile>
#include <QDir>
#include <QDebug>

#include "syftactions.h"
#include "syftorganizer.h"
#include "syftaction.h"

// Create a subdirectory in the given base directory
//		baseDirectory - full path
//		subDirectory - just the sub dir name (NOT full path)
CreateSubdirectoryAction::CreateSubdirectoryAction(QString baseDirectory,
                                                   QString subDirectory):
    m_baseDirectory(baseDirectory),
    m_subDirectory(subDirectory)
{}

int CreateSubdirectoryAction::Perform()
{
    QDir baseDir(m_baseDirectory);
    baseDir.mkdir(m_subDirectory);
    return 0;
}

int CreateSubdirectoryAction::Revert()
{
    QString newPath = QDir(m_baseDirectory).filePath(m_subDirectory);
    QDir toDelete(newPath);
    toDelete.removeRecursively();
    return 0;
}

// Move to a new directory
// 		originalPath - full path of start
// 		newPath - full path of destination
ChangeDirectoryAction::ChangeDirectoryAction(SyftOrganizer* organizer,
                                             QString originalPath,
                                             QString newPath):
    m_organizer(organizer),
    m_originalPath(originalPath),
    m_newPath(newPath)
{}

int ChangeDirectoryAction::Perform() {
    m_organizer->ChangeDirectory(m_newPath);
    return 0;
}

int ChangeDirectoryAction::Revert() {
    m_organizer->ChangeDirectory(m_originalPath);
    return 0;
}

// Rneame a file
// 		originalName - full path of original file
// 		newName - full path of new file
RenameFileAction::RenameFileAction(SyftFile* file,
                                   QString newName):
    m_file(file),
    m_originalName(file->fileName()),
    m_newName(newName)
{
}

int RenameFileAction::Perform() {
    m_file->rename(m_newName);
    return 0;
}

int RenameFileAction::Revert() {
    m_file->rename(m_originalName);
    return 0;
}

// Rename Directory
// 		originalName - full path etc
// 		newName - full path etc
RenameDirectoryAction::RenameDirectoryAction(SyftDir* dir,
                                             QString newName):
    m_dir(dir),
    m_originalName(dir->path()),
    m_newName(newName)
{
}

int RenameDirectoryAction::Perform() {
    qDebug() << "Performing";
    m_dir->rename(m_originalName, m_newName);
    return 0;
}

int RenameDirectoryAction::Revert() {
    qDebug() << "Reverting";
    m_dir->rename(m_newName, m_originalName);
    return 0;
}

// Move File
//    both full paths
MoveFileAction::MoveFileAction(SyftFile* file,
                               QString newName,
                               SyftOrganizer* organizer)
    :RenameFileAction(file, newName),
     m_organizer(organizer),
     m_file(file)
{}

int MoveFileAction::Perform() {
    int output = RenameFileAction::Perform();
    m_organizer->NextFile();
    m_organizer->reloadFiles(false);
    return output;
}

int MoveFileAction::Revert() {
    int output = RenameFileAction::Revert();
    m_organizer->reloadFiles(false);
    m_organizer->SetCurrentFile(m_file);
    return output;
}

DeleteFileAction::DeleteFileAction(SyftFile* file)
{
    m_fileName = file->FullName();
    /*
    if (file->open(QIODevice::ReadOnly | QIODevice::Text)) {
        m_data = file->readAll();
        file->close();
    }
    */
}

int DeleteFileAction::Perform() {
    QFile(m_fileName).remove();
    return 0;
}

int DeleteFileAction::Revert() {
    /*
    auto out = "Revert Attempt: ";
    QFile file(m_fileName);
    if (file.open(QIODevice::WriteOnly)) {
        for (auto iter = m_data.begin(); iter != m_data.end(); ++iter) {
            file.write(m_data, qstrlen(m_data));
        }
        file.close();
        qDebug() << out << "Success";
        return 0;
    }
    qDebug() << out << "Failure";
    return 1;
    */
}

