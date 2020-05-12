#include "informationdb_dialog.h"
#include "ui_informationdb_dialog.h"

InformationDB_Dialog::InformationDB_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InformationDB_Dialog)
{
    ui->setupUi(this);
}

InformationDB_Dialog::~InformationDB_Dialog()
{
    delete ui;
}
