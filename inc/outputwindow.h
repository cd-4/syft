#ifndef OUTPUTWINDOW_H
#define OUTPUTWINDOW_H

#include <QObject>
#include <QWidget>
#include <QString>
#include <QStringList>
#include <QTextEdit>

class OutputWindow : public QTextEdit
{
    Q_OBJECT
public:
    OutputWindow(QWidget* parent);

    void Clear();

public slots:
    void WriteContent(QString content);

};

#endif // OUTPUTWINDOW_H
