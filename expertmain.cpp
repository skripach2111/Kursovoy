#include "expertmain.h"
#include "ui_expertmain.h"

ExpertMain::ExpertMain(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExpertMain)
{
    ui->setupUi(this);
}

ExpertMain::~ExpertMain()
{
    delete ui;
}

bool ExpertMain::takeConnect(QSqlDatabase d)
{
    db = d;
    this->setWindowTitle(db.userName()+"::Эксперт");

    if(db.open())
    {
        QSqlQuery query;
        query.prepare("SELECT database_name FROM study.user_database WHERE user_name = :user");
        query.bindValue(":user", db.userName());
        query.exec();

        ui->stackedWidget->setCurrentIndex(0);
        db_buffer.setDB(&db);
        db_buffer.DownloadDatabase();
        //mydb.LoadData(&db);

        while (query.next())
        {
            ui->listWidget_ListDatabases->addItem(query.value(0).toString());
        }

        return true;
    }

    return false;
}
void ExpertMain::on_listWidget_ListDatabases_currentRowChanged(int currentRow)
{
    //    ui->label_NameDB->setText(db_buffer.getDBList().at(currentRow).name);
    //    ui->label_MoreInformation->setText(db_buffer.getDBList().at(currentRow).text);
}

void ExpertMain::on_pushButton_Open_clicked()
{
    //ui->stackedWidget->setCurrentIndex(1);

    db.setDatabaseName(ui->listWidget_ListDatabases->currentItem()->text());

    Database d;
    mydb = d;

    if(mydb.LoadData(&db))
        ui->stackedWidget->setCurrentIndex(1);
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Невозможно извлечь информаию из базы данных!\n");
        msgBox.exec();
    }

    ui->listWidget_Competence1->clear();
    ui->listWidget_Competence2->clear();
    ui->label_InfoCompetence1->clear();
    ui->label_InfoCompetence2->clear();

    for(int i = 0; i < mydb.competence_1.size(); i++)
        ui->listWidget_Competence1->addItem(mydb.competence_1.at(i).number);

    //    for(int i = 0; i < mydb.competence_2.size(); i++)
    //        ui->listWidget_Competence2->addItem(mydb.competence_2.at(i).number);
}

void ExpertMain::on_listWidget_Competence1_currentRowChanged(int currentRow)
{
    //ValueCoefUpdate();
    ui->label_InfoCompetence1->setText(mydb.competence_1.at(currentRow).name);

    ui->listWidget_Competence2->clear();
    ui->label_InfoCompetence2->clear();

    for(int i = 0; i < mydb.competence_2.size(); i++)
        if(mydb.competence_1.at(currentRow).text == mydb.competence_2.at(i).text)
            ui->listWidget_Competence2->addItem(mydb.competence_2.at(i).number);
}

void ExpertMain::on_listWidget_Competence2_currentRowChanged(int currentRow)
{
    ValueCoefUpdate();
    if(currentRow < mydb.competence_2.size())
        ui->label_InfoCompetence2->setText(mydb.competence_2.at(currentRow).name);
}

void ExpertMain::on_pushButton_Set_clicked()
{
    bool flag = false;

    for(int i = 0; i < mydb.conf.size(); i++)
        if(mydb.conf.at(i).compet_1 == ui->listWidget_Competence1->currentItem()->text() && mydb.conf.at(i).compet_2 == ui->listWidget_Competence2->currentItem()->text())
        {
            mydb.conf.at(i).value_coef = ui->doubleSpinBox_value_coef->value();
            flag = true;
        }

    if(flag == false)
    {
        Conformity tmp;
        tmp.compet_1 = ui->listWidget_Competence1->currentItem()->text();
        tmp.compet_2 = ui->listWidget_Competence2->currentItem()->text();
        tmp.value_coef = ui->doubleSpinBox_value_coef->value();

        mydb.conf.push_back(tmp);
    }
}

void ExpertMain::ValueCoefUpdate()
{
    if(ui->listWidget_Competence1->selectedItems().size() > 0 && ui->listWidget_Competence2->selectedItems().size() > 0)
    {
        for(int k = 0; k < mydb.conf.size(); k++)
        {
            if(ui->listWidget_Competence1->currentItem()->text() == mydb.conf.at(k).compet_1 && ui->listWidget_Competence2->currentItem()->text() == mydb.conf.at(k).compet_2)
            {
                ui->doubleSpinBox_value_coef->setValue(mydb.conf.at(k).value_coef);
                k = mydb.conf.size();
            }
            else
                ui->doubleSpinBox_value_coef->setValue(0);

        }
    }
}
void ExpertMain::on_listWidget_Competence1_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    //    ValueCoefUpdate();

    //    for(int i = 0; i < mydb.competence_1.size(); i++)
    //    {
    //        if(mydb.competence_1.at(i).number == ui->listWidget_Competence1->currentItem()->text())
    //            ui->label_InfoCompetence1->setText(mydb.competence_1.at(i).name);
    //    }
}

void ExpertMain::on_listWidget_Competence2_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    //    ValueCoefUpdate();

    //    for(int i = 0; i < mydb.competence_2.size(); i++)
    //    {
    //        if(mydb.competence_2.at(i).number == ui->listWidget_Competence2->currentItem()->text())
    //            ui->label_InfoCompetence2->setText(mydb.competence_2.at(i).name);
    //    }
}

void ExpertMain::on_pushButton_Cancel_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void ExpertMain::on_listWidget_ListDatabases_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    for(int i = 0; i < db_buffer.getDBList().size(); i++)
        if(db_buffer.getDBList().at(i).name == ui->listWidget_ListDatabases->currentItem()->text())
        {
            ui->label_NameDB->setText(db_buffer.getDBList().at(i).name);
            ui->label_MoreInformation->setText(db_buffer.getDBList().at(i).text);
        }
}
