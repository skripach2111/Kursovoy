#include "moduleeditordialog.h"
#include "ui_moduleeditordialog.h"

ModuleEditorDialog::ModuleEditorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModuleEditorDialog)
{
    ui->setupUi(this);
}

ModuleEditorDialog::~ModuleEditorDialog()
{
    delete ui;
}

void ModuleEditorDialog::setData(vector<Module> modules, Discipline subject, vector <Mod_Comp> mod, vector <Competence> compet)
{
    module = modules;
    mod_comp = mod;
    competences = compet;

    int sum_hours = 0;

    for(int i = 0; i < modules.size(); i++)
        if(subject.name == modules.at(i).discipline)
        {
            ui->tableWidget->insertRow(ui->tableWidget->rowCount());
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0, new QTableWidgetItem(modules.at(i).name));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1, new QTableWidgetItem(QVariant(modules.at(i).hours).toString()));

            sum_hours += module.at(i).hours;
        }

    ui->label_sum_credits->setText(QVariant(sum_hours).toString());
}

void ModuleEditorDialog::on_pushButton_Add_clicked()
{
    Module temp;
    temp.id = "0";
    temp.name = "-";
    temp.hours = 0;
    temp.discipline = subject.name;

    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0, new QTableWidgetItem("-"));
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1, new QTableWidgetItem("0"));

    module.push_back(temp);
}

void ModuleEditorDialog::on_tableWidget_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous)
{
    for(int i = 0; i < module.size(); i++)
        if(current->text() == module.at(i).name)
        {
            ui->lineEdit_id->setText(module.at(i).id);
            ui->lineEdit_name->setText(module.at(i).name);
            ui->spinBox_Credits->setValue(module.at(i).hours);

            currentRow = i;
        }

    ui->listWidget_listCompetenceForModule->clear();

    for(int i = 0; i < mod_comp.size(); i++)
        if(module.at(currentRow).id == mod_comp.at(i).id_module)
            ui->listWidget_listCompetenceForModule->addItem(mod_comp.at(i).id_competence);
}

void ModuleEditorDialog::on_pushButton_Change_clicked()
{
    int countCredits = 0;

    module.at(currentRow).id = ui->lineEdit_id->text();
    module.at(currentRow).name = ui->lineEdit_name->text();
    module.at(currentRow).hours = ui->spinBox_Credits->value();

    ui->tableWidget->item(ui->tableWidget->currentRow(), 0)->setText(ui->lineEdit_name->text());
    ui->tableWidget->item(ui->tableWidget->currentRow(), 1)->setText(ui->spinBox_Credits->text());

    for(int i = 0; i < ui->tableWidget->rowCount(); i++)
        countCredits += ui->tableWidget->item(i, 1)->text().toInt();

    ui->label_sum_credits->setText(QVariant(countCredits).toString());

    for(int i = 0; i < mod_comp.size(); i++)
        if(ui->lineEdit_id->text() == mod_comp.at(i).id_module)
            mod_comp.erase(mod_comp.begin()+i);

    Mod_Comp tmp;

    for(int i = 0; i < ui->listWidget_listCompetenceForModule->count(); i++)
    {
         tmp.id_module = ui->lineEdit_id->text();
         tmp.id_competence = ui->listWidget_listCompetenceForModule->item(i)->text();
         mod_comp.push_back(tmp);
    }

}

void ModuleEditorDialog::on_pushButton_Delete_clicked()
{
    int countCredits = 0;

    for(int i = 0; i < mod_comp.size(); i++)
        if(mod_comp.at(i).id_module == ui->lineEdit_id->text())
            mod_comp.erase(mod_comp.begin()+i);

    module.erase(module.begin()+currentRow);
    ui->tableWidget->removeRow(ui->tableWidget->currentRow());

    for(int i = 0; i < ui->tableWidget->rowCount(); i++)
        countCredits += ui->tableWidget->item(i, 1)->text().toInt();

    ui->label_sum_credits->setText(QVariant(countCredits).toString());
}

void ModuleEditorDialog::on_pushButton_Cancel_clicked()
{
    this->close();
}

void ModuleEditorDialog::on_pushButton_Save_clicked()
{
    emit takeResult(module, mod_comp);
    this->close();
}

void ModuleEditorDialog::on_pushButton_SetCompetences_clicked()
{
    CompetenceSelectionDialog *window = new CompetenceSelectionDialog;

    QList <QString> list;

    for(int i = 0; i < competences.size(); i++)
        list.push_back(competences.at(i).number);

    window->setAvailableCompetence(list);
    connect(window, SIGNAL(takeResult(QList <QString>)), this, SLOT(slot_getInfoFrom_CompetenceSelectionDialog(QList <QString>)));
    window->exec();

    delete window;
}

void ModuleEditorDialog::slot_getInfoFrom_CompetenceSelectionDialog(QList <QString> resultList)
{
    listCompetensesID = resultList;

    ui->listWidget_listCompetenceForModule->clear();
    ui->listWidget_listCompetenceForModule->addItems(resultList);
}
