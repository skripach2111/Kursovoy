#ifndef INFORMATIONUSER_DIALOG_H
#define INFORMATIONUSER_DIALOG_H

#include <QDialog>

#include "databasebuffer.h"
#include "databaseselectiondialog.h"

namespace Ui {
class InformationUser_Dialog;
}

class InformationUser_Dialog : public QDialog
{
    Q_OBJECT

    QList <QString> DatabaseList;
    User ThisUser;
    QList <QString> DatabaseNameList;

public:
    explicit InformationUser_Dialog(QWidget *parent = nullptr);
    ~InformationUser_Dialog();

    void takeInfo(QList <QString> newDatabaseList, User newUser, QList <QString> newDatabaseNameList);

public slots:
    void slot_getInfoFrom_DatabaseSelectionDialog(QList <QString> resultList);

private slots:
    void on_pushButton_SetInformation_clicked();

    void on_pushButton_Cancel_clicked();

    void on_pushButton_ChangeDB_clicked();

private:
    Ui::InformationUser_Dialog *ui;
};

#endif // INFORMATIONUSER_DIALOG_H
