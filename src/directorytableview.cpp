
#include <QWidget>
#include <QDebug>
#include <QHeaderView>

#include "syftorganizer.h"
#include "directorytableview.h"

DirectoryTableView::DirectoryTableView(QWidget* parent)
    :QTableWidget(parent),
      m_registerCellChanges(true),
      m_organizer(0),
      m_dirIndex(0)
{
    QHeaderView* verHeader = new QHeaderView(Qt::Vertical, this);
    setVerticalHeader(verHeader);
    verticalHeader()->setVisible(false);
    QHeaderView* horHeader = new QHeaderView(Qt::Horizontal, this);
    setHorizontalHeader(horHeader);
    horizontalHeader()->setVisible(false);
    setSelectionMode(QAbstractItemView::SingleSelection);

    connect(this, SIGNAL(cellChanged(int,int)),
            this, SLOT(CellChangedSlot(int,int)));
}

void DirectoryTableView::RefreshView()
{
    m_registerCellChanges = false;
    SyftOrganizer* org = Organizer();
    int numDirs = org->NumDirectories();
    setRowCount(numDirs);
    setColumnCount(1);
    for (int i=0; i<numDirs; i++)
    {
        SyftDir* dir = org->Directory(i);
        QTableWidgetItem* it = new QTableWidgetItem();
        it->setText(dir->basename());
        setItem(i, 0, it);
    }
    m_registerCellChanges = true;
}


void DirectoryTableView::SetOrganizer(SyftOrganizer* organizer)
{
    m_organizer=organizer;
    RefreshView();
}

void DirectoryTableView::SetSelected(int index)
{
    int maxInd = m_organizer->NumDirectories() - 1;
    if (index < 0) {
        index = maxInd;
    } else if (index > maxInd) {
        index = 0;
    }
    setCurrentCell(index, 0);
    m_dirIndex = index;
}

void DirectoryTableView::EnterView()
{
    setFocus();
    SetSelected(m_dirIndex);
}


void DirectoryTableView::PrevDir() {
    SetSelected(m_dirIndex-1);
}

void DirectoryTableView::NextDir() {
    SetSelected(m_dirIndex+1);
}

void DirectoryTableView::StartRenameDir() {
    edit(currentIndex());
}

SyftDir* DirectoryTableView::SelectedDir() {
    return m_organizer->Directory(m_dirIndex);
}

void DirectoryTableView::CellChangedSlot(int currentRow, int currentColumn) {
    if (m_registerCellChanges) {
        int realRow = m_dirIndex; // For some reason currentRow isn't correct here
        SyftDir* changedRow = m_organizer->Directory(realRow);
        QString oldDirname = changedRow->path();

        QString newName = item(realRow, currentColumn)->text();
        int lastSlash = oldDirname.lastIndexOf(QDir::separator());
        QString newDirname = oldDirname.mid(0, lastSlash) + QDir::separator() + newName;
        m_organizer->RenameDir(changedRow, newDirname);
    }
}

void DirectoryTableView::DirectoryChangedSlot(SyftDir* newDir) {
    RefreshView();
}


void DirectoryTableView::NewDir()
{
    //Creates a dir and selects it
    SyftDir* dir = m_organizer->NewDir();
    // Always last index
    int numDirs = m_organizer->NumDirectories();
    int index = numDirs - 1;
    setRowCount(numDirs);
    SetSelected(index);
    StartRenameDir();
}
