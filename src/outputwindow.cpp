
#include <QDebug>

#include "outputwindow.h"

OutputWindow::OutputWindow(QWidget* parent)
    :QTextEdit(parent)
{
    setReadOnly(true);
    setFixedHeight(220);
    setLineWrapMode(QTextEdit::LineWrapMode::WidgetWidth);
}

void OutputWindow::Clear() {
    clear();
}

void OutputWindow::WriteContent(QString content) {
    append(content);
    update();
}
