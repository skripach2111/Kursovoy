#include "usersselectiondialog.h"
#include "ui_usersselectiondialog.h"

UsersSelectionDialog::UsersSelectionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UsersSelectionDialog)
{
    ui->setupUi(this);
}

UsersSelectionDialog::~UsersSelectionDialog()
{
    delete ui;
}
