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
    DatabaseNameList = list;

    for(int i = 0; i < list.length(); i++)
    {
        leapButton *button = new leapButton();
        button->setName(list.at(i));

        ui->groupBux_leapButtons_AllDB->addButton(button);
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
void DatabaseSelectionDialog::on_pushButton_clicked()
{
    emit takeResult(ui->groupBox_leapButtons_SelectedDB->getList());
    this->close();
}

void DatabaseSelectionDialog::on_pushButton_Cancel_clicked()
{
    this->close();
}

void DatabaseSelectionDialog::on_pushButton_3_clicked()
{
    ui->groupBux_leapButtons_AllDB->clear();
    ui->groupBox_leapButtons_SelectedDB->clear();

    for(int i = 0; i < DatabaseNameList.length(); i++)
    {
        leapButton *button = new leapButton();
        button->setName(DatabaseNameList.at(i));

        ui->groupBux_leapButtons_AllDB->addButton(button);
    }
}

void DatabaseSelectionDialog::on_pushButton_Search_clicked()
{
    QList <QString> listSelectingDB = ui->groupBox_leapButtons_SelectedDB->getList();
    qDebug() << "Getting name";
    bool flag = true;

    ui->groupBux_leapButtons_AllDB->clear();

    for(int i = 0; i < DatabaseNameList.size(); i++)
    {
        for(int x = 0; x < listSelectingDB.size(); x++)
        {
            if(DatabaseNameList.at(i) == listSelectingDB.at(x))
            {
                flag = false;
                listSelectingDB.removeAt(x);
                x = listSelectingDB.size();
            }
        }

        if(flag)
        {
            if(DatabaseNameList.at(i).indexOf(ui->lineEdit_Search->text(), 0) > -1)
                ui->groupBux_leapButtons_AllDB->addButton(DatabaseNameList.at(i));
            else if(ui->lineEdit_Search->text().size() == 0)
                ui->groupBux_leapButtons_AllDB->addButton(DatabaseNameList.at(i));
        }

        flag = true;
    }

}
