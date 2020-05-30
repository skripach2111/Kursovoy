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
    ui->label_NameDB->setText(db_buffer.getDBList().at(currentRow).name);
    ui->label_MoreInformation->setText(db_buffer.getDBList().at(currentRow).text);
}

void ExpertMain::on_pushButton_Open_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);

    mydb.LoadData(&db);

    for(int i = 0; i < mydb.competence_1.size(); i++)
        ui->listWidget_Competence1->addItem(mydb.competence_1.at(i).name);

    for(int i = 0; i < mydb.competence_2.size(); i++)
        ui->listWidget_Competence2->addItem(mydb.competence_2.at(i).name);
}

void ExpertMain::on_listWidget_Competence1_currentRowChanged(int currentRow)
{
    ui->label_InfoCompetence1->setText(mydb.competence_1.at(currentRow).text);
}

void ExpertMain::on_listWidget_Competence2_currentRowChanged(int currentRow)
{
    ui->label_InfoCompetence2->setText(mydb.competence_2.at(currentRow).text);
}
