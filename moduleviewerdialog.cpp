#include "moduleviewerdialog.h"
#include "ui_moduleviewerdialog.h"

ModuleViewerDialog::ModuleViewerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModuleViewerDialog)
{
    ui->setupUi(this);
}

ModuleViewerDialog::~ModuleViewerDialog()
{
    delete ui;
}

void ModuleViewerDialog::setData(vector<Module> modules, Discipline subject)
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
void ModuleViewerDialog::on_tableWidget_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous)
{
    for(int i = 0; i < module.size(); i++)
        if(current->text() == module.at(i).name)
        {
            ui->label_id->setText(module.at(i).id);
            ui->label_name->setText(module.at(i).name);
            ui->label_credits->setText(QVariant(module.at(i).hours).toString());
        }
}

void ModuleViewerDialog::on_pushButton_close_clicked()
{
    this->close();
}
