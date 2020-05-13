#ifndef USERSSELECTIONDIALOG_H
#define USERSSELECTIONDIALOG_H

#include <QDialog>

namespace Ui {
class UsersSelectionDialog;
}

class UsersSelectionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UsersSelectionDialog(QWidget *parent = nullptr);
    ~UsersSelectionDialog();

private:
    Ui::UsersSelectionDialog *ui;
};

#endif // USERSSELECTIONDIALOG_H
