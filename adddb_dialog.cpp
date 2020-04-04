#include "adddb_dialog.h"
#include "ui_adddb_dialog.h"

adddb_dialog::adddb_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::adddb_dialog)
{
    ui->setupUi(this);
}

adddb_dialog::~adddb_dialog()
{
    delete ui;
}
