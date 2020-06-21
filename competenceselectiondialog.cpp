#include "competenceselectiondialog.h"
#include "ui_competenceselectiondialog.h"

CompetenceSelectionDialog::CompetenceSelectionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CompetenceSelectionDialog)
{
    ui->setupUi(this);

    connect(ui->groupBox_leapButtons_AllCompetences, SIGNAL(button_clicked(leapButton*)), this, SLOT(slot_groupBox_AllCompetences_triggerred(leapButton*)));
    connect(ui->groupBox_leapButtons_SelectedCompetences, SIGNAL(button_clicked(leapButton*)), this, SLOT(slot_groupBox_SelectedCompetences_triggerred(leapButton*)));
}

CompetenceSelectionDialog::~CompetenceSelectionDialog()
{
    delete ui;
}

void CompetenceSelectionDialog::setAvailableCompetence(QList<QString> list)
{
    listCompetencesId = list;

    for(int i = 0; i < list.length(); i++)
    {
        leapButton *button = new leapButton();
        button->setName(list.at(i));

        ui->groupBox_leapButtons_AllCompetences->addButton(button);
    }
}

void CompetenceSelectionDialog::slot_groupBox_AllCompetences_triggerred(leapButton *button)
{
    qDebug() << "Click AllComp";
    leapButton *newbutton = new leapButton;
    newbutton->setName(button->getName());
    ui->groupBox_leapButtons_SelectedCompetences->addButton(newbutton);
    ui->groupBox_leapButtons_AllCompetences->removeButton(button);
}

void CompetenceSelectionDialog::slot_groupBox_SelectedCompetences_triggerred(leapButton *button)
{
    qDebug() << "Click SelectedComp";
    leapButton *newbutton = new leapButton;
    newbutton->setName(button->getName());
    ui->groupBox_leapButtons_AllCompetences->addButton(newbutton);
    ui->groupBox_leapButtons_SelectedCompetences->removeButton(button);
}


void CompetenceSelectionDialog::on_pushButton_Save_clicked()
{
    emit takeResult(ui->groupBox_leapButtons_SelectedCompetences->getList());
    this->close();
}


void CompetenceSelectionDialog::on_pushButton_Cancel_clicked()
{
    this->close();
}

void CompetenceSelectionDialog::on_pushButton_3_clicked()
{
    ui->groupBox_leapButtons_AllCompetences->clear();
    ui->groupBox_leapButtons_SelectedCompetences->clear();

    for(int i = 0; i < listCompetencesId.length(); i++)
    {
        leapButton *button = new leapButton();
        button->setName(listCompetencesId.at(i));

        ui->groupBox_leapButtons_AllCompetences->addButton(button);
    }
}
