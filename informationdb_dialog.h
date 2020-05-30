#ifndef INFORMATIONDB_DIALOG_H
#define INFORMATIONDB_DIALOG_H

#include <QDialog>
#include "databasebuffer.h"
#include "usersselectiondialog.h"

namespace Ui {
class InformationDB_Dialog;
}

class InformationDB_Dialog : public QDialog
{
    Q_OBJECT

    QList <User> AllUsersList;
    QList <User> UserList;
    DatabaseInfo DBInfo;

public:
    explicit InformationDB_Dialog(QWidget *parent = nullptr);

    void takeInfo(QList <User> newAllUsersList, QList <User> newUsersList, DatabaseInfo newDBInfo);

    ~InformationDB_Dialog();

public slots:
    void slot_getInfoFrom_UserSelectionDialog(QList <QString> resultList);

private slots:
    void on_pushButton_Edit_clicked();

    void on_pushButton_Cancel_clicked();

    void on_pushButton_EditUsers_clicked();

private:
    Ui::InformationDB_Dialog *ui;
};

#endif // INFORMATIONDB_DIALOG_H
