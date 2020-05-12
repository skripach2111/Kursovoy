#include "informationuser_dialog.h"
#include "ui_informationuser_dialog.h"

InformationUser_Dialog::InformationUser_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InformationUser_Dialog)
{
    ui->setupUi(this);
}

InformationUser_Dialog::~InformationUser_Dialog()
{
    delete ui;
}
