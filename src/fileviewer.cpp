
#include "fileviewer.h"

FileViewer::FileViewer(QWidget* parent)
    :QWidget(parent)
{

}

void FileViewer::SetCurrentFile(SyftFile* file) {
    m_file = file;
    this->ProcessNewFile();
};


void FileViewer::ProcessNewFile() {};

SyftFileType FileViewer::GetType() {
    // Default is image
    return SyftFileType::Image;
}
