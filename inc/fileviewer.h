#ifndef FILEVIEWER_H
#define FILEVIEWER_H

#include <QWidget>

#include "syftfile.h"

class FileViewer : public QWidget
{
    Q_OBJECT

public:
    FileViewer(QWidget* parent);

    void SetCurrentFile(SyftFile* file);
    virtual SyftFile* CurrentFile() { return m_file; }
    virtual SyftFileType GetType();

private:
    SyftFile* m_file;
    virtual void ProcessNewFile(); // Updates view

public slots:
    // Image Manipulation
    virtual void TryCancel() {};
    virtual void ZoomInSlot() {};
    virtual void ZoomOutSlot() {};
    virtual void UpSlot() {};
    virtual void DownSlot() {};
    virtual void LeftSlot() {};
    virtual void RightSlot() {};
    virtual void PlayPauseSlot() {};
    virtual void ToggleSoundSlot() {};
    virtual void StopAll() {}; // Called when the file is changed. Everything should stop

private:
    QLayout* m_layout;
};

#endif // FILEVIEWER_H
