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
    db.setDatabaseName(ui->listWidget_Databases->item(ui->listWidget_Databases->currentRow())->text());
    qDebug() << ui->listWidget_Databases->item(ui->listWidget_Databases->currentRow())->text();

    Database d;
    mydb = d;
    mydb.LoadData(&db);
    mydb.Calculate(ui->spinBox_hours->value(), ui->doubleSpinBox_coeff->value());

    ui->listWidget_Temu->clear();
    ui->tableWidget_Zachet->setRowCount(0);


    if(ui->checkBox_Visble_Predmet->isChecked())
    {
        ui->groupBox_Zachet->setVisible(true);

        qDebug() << "1/3";

        vector <QString> predmet;
        vector <int> kredit;

        for(int i = 0; i < mydb.result_mod.size(); i++)
        {
            bool flag = false;
            int number;

            for(int j = 0; j < predmet.size(); j++)
                if(predmet[j] == mydb.result_mod[i].discipline)
                {
                    flag = true;
                    number = j;
                }
            qDebug() << "1.1/3";

            if(!flag)
            {
                predmet.push_back(mydb.result_mod[i].discipline);
                kredit.push_back(mydb.result_mod[i].hours);
            }
            else
                kredit[number] = kredit[number] + mydb.result_mod[i].hours;

            qDebug() << "1.2/3";
        }

        qDebug() << "2/3";


        for(int i = 0; i < predmet.size(); i++)
        {
            ui->tableWidget_Zachet->insertRow(ui->tableWidget_Zachet->rowCount());
            ui->tableWidget_Zachet->setItem(ui->tableWidget_Zachet->rowCount()-1, 0, new QTableWidgetItem(predmet[i]));
            ui->tableWidget_Zachet->setItem(ui->tableWidget_Zachet->rowCount()-1, 1, new QTableWidgetItem((QVariant(kredit[i]/30)).toString()));
        }

    }
    else
        ui->groupBox_Zachet->setVisible(false);

    if(ui->groupBox_ChekModule->isChecked())
    {
        ui->groupBox_Temu->setVisible(true);

        if(ui->radioButton_All->isChecked())
        {
            for(int i = 0; i < mydb.result_mod.size(); i++)
                ui->listWidget_Temu->addItem(mydb.result_mod[i].name);
        }
    }
    else
        ui->groupBox_Temu->setVisible(false);

    qDebug() << "3/3";

    if(ui->checkBox_Form_Quest->isChecked())
    {
        ui->groupBox_Tests->setVisible(true);
        ui->label_Tests->setText("");

        for(int i = 0; i < mydb.result_question.size(); i++)
        {
            ui->label_Tests->setText(ui->label_Tests->text() + "\n" + QVariant(i+1).toString() + ". " + mydb.result_question[i].text + "\n" + mydb.result_question[i].a + "\n" + mydb.result_question[i].b + "\n" + mydb.result_question[i].c + "\n" + mydb.result_question[i].d + "\n");
        }
    }
    else
        ui->groupBox_Tests->setVisible(false);

    ui->groupBox_Result->setVisible(true);
    ui->groupBox_Info->setVisible(false);
    ui->groupBox_Databases->setVisible(false);
    ui->groupBox_Settings->setVisible(false);
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

//void AdminMain::on_tableWidget_Zachet_itemClicked(QTableWidgetItem *item)
//{
//    ui->listWidget_Temu->clear();

//    for(int i = 0; i < mydb.result_mod.size(); i++)
//    {
//        if(mydb.result_mod[i].discipline == ui->tableWidget_Zachet->selectedItems()[0]->text())
//            ui->listWidget_Temu->addItem(mydb.result_mod[i].name);
//    }
//}

void AdminMain::on_tableWidget_Zachet_cellClicked(int row, int column)
{
    ui->listWidget_Temu->clear();

    for(int i = 0; i < mydb.result_mod.size(); i++)
    {
        if(mydb.result_mod[i].discipline == ui->tableWidget_Zachet->selectedItems()[0]->text())
            ui->listWidget_Temu->addItem(mydb.result_mod[i].name);
    }
}
