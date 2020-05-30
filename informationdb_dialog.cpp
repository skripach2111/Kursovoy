#include "informationdb_dialog.h"
#include "ui_informationdb_dialog.h"

InformationDB_Dialog::InformationDB_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InformationDB_Dialog)
{
    ui->setupUi(this);
}

InformationDB_Dialog::~InformationDB_Dialog()
{
    delete ui;
}

void InformationDB_Dialog::takeInfo(QList<User> newAllUsersList, QList<User> newUsersList, DatabaseInfo newDBInfo)
{
    AllUsersList = newAllUsersList;
    UserList = newUsersList;
    DBInfo = newDBInfo;

    ui->lineEdit_Name->setText(DBInfo.name);
    ui->plainTextEdit_MoreInfo->setPlainText(DBInfo.text);

    ui->tableWidget_Users->setRowCount(0);

    for(int i = 0; i < UserList.size(); i++)
    {
        ui->tableWidget_Users->insertRow(ui->tableWidget_Users->rowCount());
        ui->tableWidget_Users->setItem(ui->tableWidget_Users->rowCount()-1, 0, new QTableWidgetItem(UserList.at(i).fio));

        if(UserList.at(i).role == "Admin")
            ui->tableWidget_Users->setItem(ui->tableWidget_Users->rowCount()-1, 1, new QTableWidgetItem("Администратор"));
        else if(UserList.at(i).role == "Oper")
            ui->tableWidget_Users->setItem(ui->tableWidget_Users->rowCount()-1, 1, new QTableWidgetItem("Оператор"));
        else if(UserList.at(i).role == "Exp")
            ui->tableWidget_Users->setItem(ui->tableWidget_Users->rowCount()-1, 1, new QTableWidgetItem("Эксперт"));
    }
}

void InformationDB_Dialog::on_pushButton_Edit_clicked()
{
    ui->lineEdit_Name->setReadOnly(false);
    ui->plainTextEdit_MoreInfo->setReadOnly(false);
    ui->pushButton_EditUsers->setEnabled(true);

    ui->stackedWidget->setCurrentIndex(1);
}

void InformationDB_Dialog::on_pushButton_Cancel_clicked()
{
    ui->lineEdit_Name->setReadOnly(true);
    ui->plainTextEdit_MoreInfo->setReadOnly(true);
    ui->pushButton_EditUsers->setEnabled(false);

    ui->lineEdit_Name->setText(DBInfo.name);
    ui->plainTextEdit_MoreInfo->setPlainText(DBInfo.text);

    ui->stackedWidget->setCurrentIndex(0);

    ui->tableWidget_Users->setRowCount(0);

    for(int i = 0; i < UserList.size(); i++)
    {
        ui->tableWidget_Users->insertRow(ui->tableWidget_Users->rowCount());
        ui->tableWidget_Users->setItem(ui->tableWidget_Users->rowCount()-1, 0, new QTableWidgetItem(UserList.at(i).fio));

        if(UserList.at(i).role == "Admin")
            ui->tableWidget_Users->setItem(ui->tableWidget_Users->rowCount()-1, 1, new QTableWidgetItem("Администратор"));
        else if(UserList.at(i).role == "Oper")
            ui->tableWidget_Users->setItem(ui->tableWidget_Users->rowCount()-1, 1, new QTableWidgetItem("Оператор"));
        else if(UserList.at(i).role == "Exp")
            ui->tableWidget_Users->setItem(ui->tableWidget_Users->rowCount()-1, 1, new QTableWidgetItem("Эксперт"));
    }
}

void InformationDB_Dialog::on_pushButton_EditUsers_clicked()
{
    UsersSelectionDialog *SelectionDialog = new UsersSelectionDialog;
    SelectionDialog->setTables(AllUsersList);
    connect(SelectionDialog, SIGNAL(takeResult(QList <QString>)), this, SLOT(slot_getInfoFrom_UserSelectionDialog(QList <QString>)));
    SelectionDialog->exec();
}

void InformationDB_Dialog::slot_getInfoFrom_UserSelectionDialog(QList <QString> resultList)
{
    ui->tableWidget_Users->setRowCount(0);

    QList <User> tempList = AllUsersList;
    int x = 0;
    bool flag;

    while(x < tempList.size())
    {
        flag = false;

        for(int i = 0; i < resultList.size(); i++)
        {
            if(resultList.at(i) == tempList.at(x).fio)
            {
                flag = true;
                resultList.removeAt(i);
                x++;
                i = resultList.size();
            }
        }

        if(!flag)
        {
            tempList.removeAt(x);
        }
    }


    for(int i = 0; i < tempList.size(); i++)
    {
        ui->tableWidget_Users->insertRow(ui->tableWidget_Users->rowCount());
        ui->tableWidget_Users->setItem(ui->tableWidget_Users->rowCount()-1, 0, new QTableWidgetItem(tempList.at(i).fio));

        if(tempList.at(i).role == "Admin")
            ui->tableWidget_Users->setItem(ui->tableWidget_Users->rowCount()-1, 1, new QTableWidgetItem("Администратор"));
        else if(tempList.at(i).role == "Oper")
            ui->tableWidget_Users->setItem(ui->tableWidget_Users->rowCount()-1, 1, new QTableWidgetItem("Оператор"));
        else if(tempList.at(i).role == "Exp")
            ui->tableWidget_Users->setItem(ui->tableWidget_Users->rowCount()-1, 1, new QTableWidgetItem("Эксперт"));
    }
}
