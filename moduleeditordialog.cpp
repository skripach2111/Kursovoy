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

void ModuleEditorDialog::setData(vector<Module> modules, Discipline subject, vector <Mod_Comp> mod)
{
    module = modules;
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
}

void ModuleEditorDialog::on_pushButton_Change_clicked()
{
    module.at(currentRow).id = ui->lineEdit_id->text();
    module.at(currentRow).name = ui->lineEdit_name->text();
    module.at(currentRow).hours = ui->spinBox_Credits->value();

    ui->tableWidget->item(ui->tableWidget->currentRow(), 0)->setText(ui->lineEdit_name->text());
    ui->tableWidget->item(ui->tableWidget->currentRow(), 1)->setText(ui->spinBox_Credits->text());

    ui->label_sum_credits->setText(QVariant(QVariant(ui->label_sum_credits->text()).toInt() + ui->spinBox_Credits->value()).toString());
}

void ModuleEditorDialog::on_pushButton_Delete_clicked()
{
    ui->label_sum_credits->setText(QVariant(QVariant(ui->label_sum_credits->text()).toInt() - ui->spinBox_Credits->value()).toString());
    module.erase(module.begin()+currentRow);
    ui->tableWidget->removeRow(ui->tableWidget->currentRow());
}

void ModuleEditorDialog::on_pushButton_Cancel_clicked()
{
    this->close();
}

void ModuleEditorDialog::on_pushButton_Save_clicked()
{
    emit takeResult(module);
    this->close();
}
