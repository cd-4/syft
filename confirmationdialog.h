#ifndef CONFIRMATIONDIALOG_H
#define CONFIRMATIONDIALOG_H

#include <QWidget>
#include <QMessageBox>

class ConfirmationDialog : public QMessageBox
{
public:
    ConfirmationDialog(QWidget* parent, QString message);
};

#endif // CONFIRMATIONDIALOG_H
