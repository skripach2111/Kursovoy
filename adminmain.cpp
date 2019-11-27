#include "adminmain.h"
#include "ui_adminmain.h"

AdminMain::AdminMain(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminMain)
{
    ui->setupUi(this);
    this->resize(560, 600);
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
    ui->groupBox_Result->setVisible(true);
    ui->groupBox_Info->setVisible(false);
    ui->groupBox_Databases->setVisible(false);
    ui->groupBox_Settings->setVisible(false);

    db.setDatabaseName(ui->listWidget_Databases->item(ui->listWidget_Databases->currentRow())->text());
    qDebug() << ui->listWidget_Databases->item(ui->listWidget_Databases->currentRow())->text();

    Database mydb;
    mydb.LoadData(&db);
    mydb.Calculate(ui->spinBox_hours->value(), ui->doubleSpinBox_coeff->value());
}

void AdminMain::on_pushButton_2_clicked()
{
    ui->groupBox_Result->setVisible(false);
    ui->groupBox_Info->setVisible(true);
    ui->groupBox_Databases->setVisible(true);
    ui->groupBox_Settings->setVisible(false);
}

void AdminMain::on_pushButton_Return_clicked()
{
    ui->groupBox_Databases->setVisible(false);
    ui->groupBox_Info->setVisible(false);
    ui->groupBox_Result->setVisible(false);
    ui->groupBox_Settings->setVisible(true);
}

void AdminMain::on_pushButton_Open_clicked()
{
    ui->groupBox_Databases->setVisible(false);
    ui->groupBox_Info->setVisible(false);
    ui->groupBox_Result->setVisible(false);
    ui->groupBox_Settings->setVisible(true);
}

void AdminMain::on_pushButton_Gotovo_clicked()
{
    ui->groupBox_Result->setVisible(false);
    ui->groupBox_Info->setVisible(true);
    ui->groupBox_Databases->setVisible(true);
}
