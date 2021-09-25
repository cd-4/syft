#ifndef DIRECTORYTABLEVIEW_H
#define DIRECTORYTABLEVIEW_H

#include <QTableWidget>

#include "syftorganizer.h"

class DirectoryTableView : public QTableWidget
{
    Q_OBJECT
public:
    DirectoryTableView(QWidget* parent);

    void RefreshView();
    SyftOrganizer* Organizer() { return m_organizer; }
    void SetOrganizer(SyftOrganizer* organizer);

    void SetSelected(int index);
    void EnterView();
    void NextDir();
    void PrevDir();
    SyftDir* SelectedDir();

    void StartRenameDir();
    void NewDir();

public slots:
    void CellChangedSlot(int currentRow, int currentColumn);
    void DirectoryChangedSlot(SyftDir* newDir);



private:
    bool m_registerCellChanges;
    SyftOrganizer* m_organizer;
    int m_dirIndex;
};

#endif // DIRECTORYTABLEVIEW_H
