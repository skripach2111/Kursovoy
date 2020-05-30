#include "informationuser_dialog.h"
#include "ui_informationuser_dialog.h"

InformationUser_Dialog::InformationUser_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InformationUser_Dialog)
{
    ui->setupUi(this);
}

InformationUser_Dialog::~InformationUser_Dialog()
{
    delete ui;
}

void InformationUser_Dialog::takeInfo(QList<QString> newDatabaseList, User newUser, QList<QString> newDatabaseNameList)
{
    DatabaseList = newDatabaseList;
    ThisUser = newUser;
    DatabaseNameList = newDatabaseNameList;

    ui->lineEdit_FIO->setText(ThisUser.fio);
    ui->lineEdit_Login->setText(ThisUser.login);

    if(ThisUser.role == "Admin")
        ui->radioButton_Admin->setChecked(true);
    else if(ThisUser.role == "Oper")
        ui->radioButton_Oper->setChecked(true);
    else
        ui->radioButton_Exp->setChecked(true);

    ui->listWidget_DB->clear();
    ui->listWidget_DB->addItems(DatabaseNameList);
}

void InformationUser_Dialog::on_pushButton_SetInformation_clicked()
{
    ui->lineEdit_FIO->setEnabled(true);
    ui->lineEdit_Login->setEnabled(true);
    ui->groupBox_Position->setEnabled(true);
    ui->lineEdit_Password_1->setEnabled(true);
    ui->lineEdit_Password_2->setEnabled(true);
    ui->pushButton_ChangeDB->setEnabled(true);

    ui->stackedWidget->setCurrentIndex(1);
}

void InformationUser_Dialog::on_pushButton_Cancel_clicked()
{
    ui->lineEdit_FIO->setEnabled(false);
    ui->lineEdit_Login->setEnabled(false);
    ui->groupBox_Position->setEnabled(false);
    ui->lineEdit_Password_1->setEnabled(false);
    ui->lineEdit_Password_2->setEnabled(false);
    ui->pushButton_ChangeDB->setEnabled(false);

    ui->stackedWidget->setCurrentIndex(0);

    ui->lineEdit_FIO->setText(ThisUser.fio);
    ui->lineEdit_Login->setText(ThisUser.login);
    ui->lineEdit_Password_1->setText("");
    ui->lineEdit_Password_2->setText("");

    if(ThisUser.role == "Admin")
        ui->radioButton_Admin->setChecked(true);
    else if(ThisUser.role == "Oper")
        ui->radioButton_Oper->setChecked(true);
    else
        ui->radioButton_Exp->setChecked(true);

    ui->listWidget_DB->clear();
    ui->listWidget_DB->addItems(DatabaseNameList);
}

void InformationUser_Dialog::on_pushButton_ChangeDB_clicked()
{
    DatabaseSelectionDialog *DBSelectionDialog = new DatabaseSelectionDialog;
    DBSelectionDialog->setAvailableDB(DatabaseList);
    connect(DBSelectionDialog, SIGNAL(takeResult(QList <QString>)), this, SLOT(slot_getInfoFrom_DatabaseSelectionDialog(QList <QString>)));
    DBSelectionDialog->exec();
}

void InformationUser_Dialog::slot_getInfoFrom_DatabaseSelectionDialog(QList <QString> resultList)
{
    ui->listWidget_DB->clear();
    ui->listWidget_DB->addItems(resultList);
}
