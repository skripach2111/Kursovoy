#ifndef USERSSELECTIONDIALOG_H
#define USERSSELECTIONDIALOG_H

#include <QDialog>

#include "databasebuffer.h"
#include "groupbox_leapbuttons.h"
#include <QDebug>

namespace Ui {
class UsersSelectionDialog;
}

class UsersSelectionDialog : public QDialog
{
    Q_OBJECT

    QList <User> UsersList;

public:
    explicit UsersSelectionDialog(QWidget *parent = nullptr);

    void setTables(QList <User> NewUsersList);

    ~UsersSelectionDialog();

public slots:
    void slot_groupBox_AllUsers_triggerred(leapButton *button);

    void slot_groupBox_SelectetingUsers_triggerred(leapButton *button);

private slots:
    void on_pushButton_Search_clicked();

    void on_pushButton_Save_clicked();

    void on_pushButton_Cancel_clicked();

    void on_pushButton_ResetAll_clicked();

signals:
    void takeResult(QList <QString> listUsers);

private:
    Ui::UsersSelectionDialog *ui;
};

#endif // USERSSELECTIONDIALOG_H
