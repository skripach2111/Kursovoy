#include "databaseselectiondialog.h"
#include "ui_databaseselectiondialog.h"
#include <QDebug>

DatabaseSelectionDialog::DatabaseSelectionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DatabaseSelectionDialog)
{
    ui->setupUi(this);

    connect(ui->groupBux_leapButtons_AllDB, SIGNAL(button_clicked(leapButton*)), this, SLOT(slot_groupBox_AllDB_triggerred(leapButton*)));
    connect(ui->groupBox_leapButtons_SelectedDB, SIGNAL(button_clicked(leapButton*)), this, SLOT(slot_groupBox_SelectedDB_triggerred(leapButton*)));
}

DatabaseSelectionDialog::~DatabaseSelectionDialog()
{
    delete ui;
}

void DatabaseSelectionDialog::setAvailableDB(QList<QString> list)
{
    qDebug() << "Step 1";

    for(int i = 0; i < list.length(); i++)
    {
        qDebug() << "Step 2";
        leapButton *button = new leapButton();
        qDebug() << "Step 3";
        button->setName(list.at(i));

        qDebug() << i;

        ui->groupBux_leapButtons_AllDB->addButton(button);
        qDebug() << "Step 4";
    }
}

void DatabaseSelectionDialog::slot_groupBox_AllDB_triggerred(leapButton *button)
{
    qDebug() << "Click AllDB";
    leapButton *newbutton = new leapButton;
    newbutton->setName(button->getName());
    ui->groupBox_leapButtons_SelectedDB->addButton(newbutton);
    ui->groupBux_leapButtons_AllDB->removeButton(button);
}

void DatabaseSelectionDialog::slot_groupBox_SelectedDB_triggerred(leapButton *button)
{
    qDebug() << "Click SelectedDB";
    leapButton *newbutton = new leapButton;
    newbutton->setName(button->getName());
    ui->groupBux_leapButtons_AllDB->addButton(newbutton);
    ui->groupBox_leapButtons_SelectedDB->removeButton(button);
}
