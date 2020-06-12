#include "opermain.h"
#include "ui_opermain.h"

OperMain::OperMain(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OperMain)
{
    ui->setupUi(this);

    ui->frame_InfoBar->setVisible(false);
}

OperMain::~OperMain()
{
    delete ui;
}

bool OperMain::takeConnect(QSqlDatabase d)
{
    db = d;
    this->setWindowTitle(db.userName()+"::Оператор");

    if(db.open())
    {
        QSqlQuery query;
        query.prepare("SELECT database_name FROM study.user_database WHERE user_name = :user");
        query.bindValue(":user", db.userName());
        query.exec();

        ui->stackedWidget_Main->setCurrentIndex(0);
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
void OperMain::on_listWidget_ListDatabases_currentRowChanged(int currentRow)
{
    for(int i = 0; i < db_buffer.getDBList().size(); i++)
        if(db_buffer.getDBList().at(i).name == ui->listWidget_ListDatabases->currentItem()->text())
        {
            ui->label_NameDatabase->setText(db_buffer.getDBList().at(i).name);
            ui->label_DatabaseInformation->setText(db_buffer.getDBList().at(i).text);
        }
}

void OperMain::on_pushButton_Open_clicked()
{
    db.setDatabaseName(ui->listWidget_ListDatabases->currentItem()->text());

    Database d;
    mydb = d;

    if(mydb.LoadData(&db))
    {
        ui->stackedWidget_Main->setCurrentIndex(1);
        ui->stackedWidget_Workspace->setCurrentIndex(0);

        ui->frame_InfoBar->setVisible(true);
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Невозможно извлечь информаию из базы данных!\n");
        msgBox.exec();
    }

    ui->lineEdit_NameDB->setText(ui->label_NameDatabase->text());
    ui->plainTextEdit_InfoDB->setPlainText(ui->label_DatabaseInformation->text());

    ui->lineEdit_NameDB->setEnabled(false);
    ui->plainTextEdit_InfoDB->setEnabled(false);

    ui->stackedWidget_EditOrViewSpace->setVisible(false);

    ui->label_Status->setText("Сохранено");
    ui->label_Errors->setText("Ошибок нет");

    ui->toolBox_Menu->setItemText(0, ui->label_NameDatabase->text());

    mydb.LoadData(&db);
}

void OperMain::on_commandLinkButton_clicked()
{
    ui->stackedWidget_Workspace->setCurrentIndex(0);
    ui->stackedWidget_EditOrViewSpace->setVisible(false);

    ui->stackedWidget_Competences->setCurrentIndex(0);
}

void OperMain::on_commandLinkButton_2_clicked()
{
    ui->stackedWidget_Workspace->setCurrentIndex(1);
    ui->stackedWidget_EditOrViewSpace->setVisible(true);

    if(Mode)
        ui->stackedWidget_EditOrViewSpace->setCurrentIndex(0);
    else
        ui->stackedWidget_EditOrViewSpace->setCurrentIndex(1);

    ui->listWidget_Competences1->clear();
    ui->listWidget_Competences2->clear();

    for(int i = 0; i < mydb.competence_1.size(); i++)
        ui->listWidget_Competences1->addItem(mydb.competence_1.at(i).number);
    for(int i = 0; i < mydb.competence_2.size(); i++)
        ui->listWidget_Competences2->addItem(mydb.competence_2.at(i).number);
}

void OperMain::on_commandLinkButton_3_clicked()
{
    ui->stackedWidget_Workspace->setCurrentIndex(2);
    ui->stackedWidget_EditOrViewSpace->setVisible(true);

    if(Mode)
        ui->stackedWidget_EditOrViewSpace->setCurrentIndex(2);
    else
        ui->stackedWidget_EditOrViewSpace->setCurrentIndex(3);
}

void OperMain::on_commandLinkButton_4_clicked()
{
    ui->stackedWidget_Workspace->setCurrentIndex(3);
    ui->stackedWidget_EditOrViewSpace->setVisible(true);

    if(Mode)
        ui->stackedWidget_EditOrViewSpace->setCurrentIndex(4);
    else
        ui->stackedWidget_EditOrViewSpace->setCurrentIndex(5);

    ui->listWidget_ListCompetences->clear();

    for(int i = 0; i < mydb.competence_2.size(); i++)
        ui->listWidget_ListCompetences->addItem(mydb.competence_2.at(i).number);
}

void OperMain::on_listWidget_Competences2_currentRowChanged(int currentRow)
{
    ui->label_InformationCompetence->setText(mydb.competence_2.at(currentRow).name);
    ui->label_NumberCompetence->setText(mydb.competence_2.at(currentRow).number);

    switch (QVariant(mydb.competence_2.at(currentRow).text).toInt())
    {
    case 1:
    {
        ui->radioButton_Type1_view->setChecked(true);
        ui->radioButton_Type2_View->setChecked(false);
        ui->radioButton_Type3_View->setChecked(false);

        break;
    }
    case 2:
    {
        ui->radioButton_Type1_view->setChecked(false);
        ui->radioButton_Type2_View->setChecked(false);
        ui->radioButton_Type3_View->setChecked(true);

        break;
    }
    case 3:
    {
        ui->radioButton_Type1_view->setChecked(false);
        ui->radioButton_Type2_View->setChecked(true);
        ui->radioButton_Type3_View->setChecked(false);

        break;
    }
    }
}

void OperMain::on_listWidget_Competences1_currentRowChanged(int currentRow)
{
    ui->label_InformationCompetence->setText(mydb.competence_1.at(currentRow).name);
    ui->label_NumberCompetence->setText(mydb.competence_1.at(currentRow).number);

    switch (QVariant(mydb.competence_1.at(currentRow).text).toInt())
    {
    case 1:
    {
        ui->radioButton_Type1_view->setChecked(true);
        ui->radioButton_Type2_View->setChecked(false);
        ui->radioButton_Type3_View->setChecked(false);

        break;
    }
    case 2:
    {
        ui->radioButton_Type1_view->setChecked(false);
        ui->radioButton_Type2_View->setChecked(false);
        ui->radioButton_Type3_View->setChecked(true);

        break;
    }
    case 3:
    {
        ui->radioButton_Type1_view->setChecked(false);
        ui->radioButton_Type2_View->setChecked(true);
        ui->radioButton_Type3_View->setChecked(false);

        break;
    }
    }
}

void OperMain::on_comboBox_SetRange_currentIndexChanged(int index)
{
    ui->stackedWidget_Competences->setCurrentIndex(index);
}

void OperMain::on_listWidget_ListCompetences_currentRowChanged(int currentRow)
{
    ui->listWidget_ListQuestions->clear();

    for(int i = 0; i < mydb.question.size(); i++)
        if(ui->listWidget_ListCompetences->currentItem()->text() == mydb.question.at(i).id_compet)
            ui->listWidget_ListQuestions->addItem(mydb.question.at(i).text);
}

void OperMain::on_listWidget_ListQuestions_currentRowChanged(int currentRow)
{
    for(int i = 0; i < mydb.question.size(); i++)
        if(ui->listWidget_ListQuestions->currentItem()->text() == mydb.question.at(i).text)
        {
            ui->label_Question->setText(mydb.question.at(i).text);

            ui->radioButton_AnswerAViewer->setText(mydb.question.at(i).a);
            ui->radioButton_AnswerBViewer->setText(mydb.question.at(i).b);
            ui->radioButton_AnswerCViewer->setText(mydb.question.at(i).c);
            ui->radioButton_AnswerDViewer->setText(mydb.question.at(i).d);

            if(mydb.question.at(i).answer_true == "a")
            {
                ui->radioButton_AnswerAViewer->setChecked(true);
                ui->radioButton_AnswerBViewer->setChecked(false);
                ui->radioButton_AnswerCViewer->setChecked(false);
                ui->radioButton_AnswerDViewer->setChecked(false);
            }
            else if(mydb.question.at(i).answer_true == "b")
            {
                ui->radioButton_AnswerAViewer->setChecked(false);
                ui->radioButton_AnswerBViewer->setChecked(true);
                ui->radioButton_AnswerCViewer->setChecked(false);
                ui->radioButton_AnswerDViewer->setChecked(false);
            }
            else if(mydb.question.at(i).answer_true == "c")
            {
                ui->radioButton_AnswerAViewer->setChecked(false);
                ui->radioButton_AnswerBViewer->setChecked(false);
                ui->radioButton_AnswerCViewer->setChecked(true);
                ui->radioButton_AnswerDViewer->setChecked(false);
            }
            else if(mydb.question.at(i).answer_true == "d")
            {
                ui->radioButton_AnswerAViewer->setChecked(false);
                ui->radioButton_AnswerBViewer->setChecked(false);
                ui->radioButton_AnswerCViewer->setChecked(false);
                ui->radioButton_AnswerDViewer->setChecked(true);
            }

            break;
        }
}
