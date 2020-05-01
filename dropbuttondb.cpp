#include "dropbuttondb.h"
#include "ui_dropbuttondb.h"

#include <QDebug>

dropButtonDB::dropButtonDB(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dropButtonDB)
{
    ui->setupUi(this);

    connect(ui->commandLinkButton, SIGNAL(clicked()), this, SLOT(slot_commandLinkButton_clicked()));

    connect(mydropMenu, SIGNAL(pushButton_Details_clicked()), this, SLOT(slot_pushButton_Details_clicked()));
    connect(mydropMenu, SIGNAL(pushButton_DeleteDB_clicked()), this, SLOT(slot_pushButton_DeleteDB_clicked()));
}

dropButtonDB::~dropButtonDB()
{
    delete ui;
}

void dropButtonDB::slot_commandLinkButton_clicked()
{
    if(ui->commandLinkButton->isChecked())
    {
        ui->verticalLayout->addWidget(mydropMenu);

        qDebug() << "Menu is drop!";
    }
    else
    {
        ui->verticalLayout->removeWidget(mydropMenu);

        qDebug() << "Menu is break!";
    }
}

void dropButtonDB::slot_pushButton_Details_clicked()
{
    emit showDetails(name);
}

void dropButtonDB::slot_pushButton_DeleteDB_clicked()
{
    emit deleteDB(name);
}

void dropButtonDB::setInfo(QString nameDB)
{
    name = nameDB;
}
