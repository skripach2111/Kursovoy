#include "usersselectiondialog.h"
#include "ui_usersselectiondialog.h"

UsersSelectionDialog::UsersSelectionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UsersSelectionDialog)
{
    ui->setupUi(this);

    connect(ui->groupBox_LeapButtons_AllUsers, SIGNAL(button_clicked(leapButton*)), this, SLOT(slot_groupBox_AllUsers_triggerred(leapButton*)));
    connect(ui->groupBox_leapButtons_Selecting_Users, SIGNAL(button_clicked(leapButton*)), this, SLOT(slot_groupBox_SelectetingUsers_triggerred(leapButton*)));
}

UsersSelectionDialog::~UsersSelectionDialog()
{
    delete ui;
}

void UsersSelectionDialog::setTables(QList<User> NewUsersList)
{
    UsersList = NewUsersList;

    for(int i = 0; i < UsersList.size(); i++)
    {
        ui->groupBox_LeapButtons_AllUsers->addButton(UsersList.at(i).fio);
    }
}

void UsersSelectionDialog::on_pushButton_Search_clicked()
{
    QList <QString> listSelectingUser = ui->groupBox_leapButtons_Selecting_Users->getList();
    qDebug() << "Getting name";
    bool flag = true;

    ui->groupBox_LeapButtons_AllUsers->clear();

    if(!ui->checkBox_Admin->isChecked() && !ui->checkBox_Expert->isChecked() && !ui->checkBox_Operator->isChecked())
    {
        for(int i = 0; i < UsersList.size(); i++)
        {
            for(int x = 0; x < listSelectingUser.size(); x++)
            {
                if(UsersList.at(i).fio == listSelectingUser.at(x))
                {
                    flag = false;
                    listSelectingUser.removeAt(x);
                    x = listSelectingUser.size();
                }
            }

            if(flag)
            {
                if(UsersList.at(i).fio.indexOf(ui->lineEdit_Search->text(), 0) > -1)
                    ui->groupBox_LeapButtons_AllUsers->addButton(UsersList.at(i).fio);
                else if(ui->lineEdit_Search->text().size() == 0)
                    ui->groupBox_LeapButtons_AllUsers->addButton(UsersList.at(i).fio);
            }

            flag = true;
        }
    }
    else
    {
        for(int i = 0; i < UsersList.size(); i++)
        {
            for(int x = 0; x < listSelectingUser.size(); x++)
            {
                if(UsersList.at(i).fio == listSelectingUser.at(x))
                {
                    flag = false;
                    listSelectingUser.removeAt(x);
                    x = listSelectingUser.size();
                }
            }

            if(flag)
            {
                if(UsersList.at(i).fio.indexOf(ui->lineEdit_Search->text(), 0) > -1)
                {
                    if(UsersList.at(i).role == "Admin" && ui->checkBox_Admin->isChecked())
                        ui->groupBox_LeapButtons_AllUsers->addButton(UsersList.at(i).fio);
                    else if(UsersList.at(i).role == "Oper" && ui->checkBox_Operator->isChecked())
                        ui->groupBox_LeapButtons_AllUsers->addButton(UsersList.at(i).fio);
                    else if(UsersList.at(i).role == "Exp" && ui->checkBox_Expert->isChecked())
                        ui->groupBox_LeapButtons_AllUsers->addButton(UsersList.at(i).fio);
                }
                else if(ui->lineEdit_Search->text().size() == 0)
                {
                    if(UsersList.at(i).role == "Admin" && ui->checkBox_Admin->isChecked())
                        ui->groupBox_LeapButtons_AllUsers->addButton(UsersList.at(i).fio);
                    else if(UsersList.at(i).role == "Oper" && ui->checkBox_Operator->isChecked())
                        ui->groupBox_LeapButtons_AllUsers->addButton(UsersList.at(i).fio);
                    else if(UsersList.at(i).role == "Exp" && ui->checkBox_Expert->isChecked())
                        ui->groupBox_LeapButtons_AllUsers->addButton(UsersList.at(i).fio);
                }
            }

            flag = true;
        }
    }
}

void UsersSelectionDialog::slot_groupBox_AllUsers_triggerred(leapButton *button)
{
    leapButton *newbutton = new leapButton;
    newbutton->setName(button->getName());
    ui->groupBox_leapButtons_Selecting_Users->addButton(newbutton);
    ui->groupBox_LeapButtons_AllUsers->removeButton(button);
}

void UsersSelectionDialog::slot_groupBox_SelectetingUsers_triggerred(leapButton *button)
{
    leapButton *newbutton = new leapButton;
    newbutton->setName(button->getName());
    ui->groupBox_LeapButtons_AllUsers->addButton(newbutton);
    ui->groupBox_leapButtons_Selecting_Users->removeButton(button);
}

void UsersSelectionDialog::on_pushButton_Save_clicked()
{
    emit takeResult(ui->groupBox_leapButtons_Selecting_Users->getList());
    this->close();
}

void UsersSelectionDialog::on_pushButton_Cancel_clicked()
{
    this->close();
}


void UsersSelectionDialog::on_pushButton_ResetAll_clicked()
{
    ui->groupBox_LeapButtons_AllUsers->clear();
    ui->groupBox_leapButtons_Selecting_Users->clear();

    for(int i = 0; i < UsersList.size(); i++)
    {
        ui->groupBox_LeapButtons_AllUsers->addButton(UsersList.at(i).fio);
    }
}
