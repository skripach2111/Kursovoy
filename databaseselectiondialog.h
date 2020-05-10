#ifndef DATABASESELECTIONDIALOG_H
#define DATABASESELECTIONDIALOG_H

#include <QDialog>
#include "groupbox_leapbuttons.h"

namespace Ui {
class DatabaseSelectionDialog;
}

class DatabaseSelectionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DatabaseSelectionDialog(QWidget *parent = nullptr);

    void setAvailableDB(QList <QString> list);

    ~DatabaseSelectionDialog();

public slots:
    void slot_groupBox_AllDB_triggerred(leapButton *button);

    void slot_groupBox_SelectedDB_triggerred(leapButton *button);

private:
    Ui::DatabaseSelectionDialog *ui;
};

#endif // DATABASESELECTIONDIALOG_H
