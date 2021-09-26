#include <QFile>
#include <QDir>
#include <QDebug>

#include "syftaction.h"
#include "syftactions.h"
#include "syftorganizer.h"

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

QString CreateSubdirectoryAction::Message() {
    return "N: " + SyftDir(m_subDirectory).basename();
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

QString ChangeDirectoryAction::Message() {
    return "D: " + SyftDir(m_newPath).basename() + QDir::separator();
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

QString RenameFileAction::Message() {
    return "R:" + SyftFile(m_originalName).FileName() + " -> " + SyftFile(m_newName).FileName();
}

// Rename Directory
// 		originalName - full path etc
// 		newName - full path etc
RenameDirectoryAction::RenameDirectoryAction(SyftDir* dir,
                                             QString newName):
    m_newName(newName),
    m_dir(dir),
    m_originalName(dir->path())
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

QString RenameDirectoryAction::Message() {
    return "R:" + SyftDir(m_originalName).basename() + QDir::separator() + " to " + QDir(m_newName).path() + QDir::separator();
}

// Move File
//    both full paths
MoveFileAction::MoveFileAction(SyftFile* file,
                               QString newName,
                               SyftOrganizer* organizer)
    :RenameFileAction(file, newName),
     m_organizer(organizer)
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

QString MoveFileAction::Message() {
    QString newName = NewName();
    QString dirName = newName.left(newName.lastIndexOf(QDir::separator()));
    int lastInd = dirName.lastIndexOf(QDir::separator()) + 1;
    QString baseName = dirName.right(dirName.size() - lastInd);
    return "M:" + CurrentFile()->FileName() + " -> " + baseName + QDir::separator();
}

SyftAction* MoveFileAction::RepeatAction(QString filename) {
    // Calculate file names
    QString sep = QDir::separator();
    int lastInd = filename.lastIndexOf(sep);
    QString baseName = filename.right(lastInd);
    QString otherFileNewName = NewName();
    int lastId = otherFileNewName.lastIndexOf(sep);
    QString newFile = otherFileNewName.left(lastId) + sep + baseName;

    MoveFileAction* action = new MoveFileAction(new SyftFile(filename), newFile, m_organizer);
    return action;

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
    // Something like this should work. Just need to work out the kinks
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
    return 0;
}

QString DeleteFileAction::Message() {
    return "D:" + SyftFile(m_fileName).FileName();
}

