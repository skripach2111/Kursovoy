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

void ModuleEditorDialog::setData(vector<Module> modules, Discipline subject)
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
