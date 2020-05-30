#include "dropmenudb.h"
#include "ui_dropmenudb.h"

dropMenuDB::dropMenuDB(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dropMenuDB)
{
    ui->setupUi(this);

    connect(ui->pushButton_Details, SIGNAL(clicked()), this, SLOT(slot_pushButton_Details_clicked()));
    connect(ui->pushButton_DeleteDB, SIGNAL(clicked()), this, SLOT(slot_pushButton_DeleteDB_clicked()));
}

dropMenuDB::~dropMenuDB()
{
    delete ui;
}

void dropMenuDB::slot_pushButton_Details_clicked()
{
    emit pushButton_Details_clicked();
}

void dropMenuDB::slot_pushButton_DeleteDB_clicked()
{
    emit pushButton_DeleteDB_clicked();
}
