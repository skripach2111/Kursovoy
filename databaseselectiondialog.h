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

    QList <QString> DatabaseNameList;

public:
    explicit DatabaseSelectionDialog(QWidget *parent = nullptr);

    void setAvailableDB(QList <QString> list);

    ~DatabaseSelectionDialog();

public slots:
    void slot_groupBox_AllDB_triggerred(leapButton *button);

    void slot_groupBox_SelectedDB_triggerred(leapButton *button);

signals:
    void takeResult(QList <QString> listUsers);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_Cancel_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_Search_clicked();

private:
    Ui::DatabaseSelectionDialog *ui;
};

#endif // DATABASESELECTIONDIALOG_H
