#include "adminmain.h"
#include "ui_adminmain.h"

AdminMain::AdminMain(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminMain)
{
    ui->setupUi(this);
}

AdminMain::~AdminMain()
{
    delete ui;
}


void AdminMain::takeConnect(QSqlDatabase d)
{
    ui->groupBox_Result->setVisible(false);
    ui->groupBox_Settings->setVisible(false);

    db = d;
    if(db.open())
    {
        qDebug() << "Connect to database!";
        QSqlQuery query;
        query.exec("SELECT * FROM study.databases");

        while (query.next())
        {
            ui->listWidget_Databases->addItem(query.value(0).toString());

            qDebug() << query.value(0).toString() << endl;
        }
    }
}

void AdminMain::on_pushButton_clicked()
{
}

void AdminMain::on_pushButton_2_clicked()
{
}

void AdminMain::on_pushButton_Return_clicked()
{
    ui->groupBox_Result->setVisible(false);
    ui->groupBox_Info->setVisible(true);
    ui->groupBox_Databases->setVisible(true);
}

void AdminMain::on_pushButton_Open_clicked()
{
    ui->groupBox_Databases->setVisible(false);
    ui->groupBox_Info->setVisible(false);
    ui->groupBox_Result->setVisible(false);
    ui->groupBox_Settings->setVisible(true);

//    QSqlQuery query;
//    query.exec("USE " + ui->listWidget_Databases->item(ui->listWidget_Databases->currentRow())->text());


}
