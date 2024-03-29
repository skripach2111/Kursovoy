#include "groupbox_leapbuttons.h"
#include "ui_groupbox_leapbuttons.h"

groupBox_leapButtons::groupBox_leapButtons(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::groupBox_leapButtons)
{
    ui->setupUi(this);

    newWdget = new QWidget(ui->scrollArea);

    ui->scrollArea->setLayout(mainlayout);
    ui->scrollArea->setWidget(newWdget);
    newWdget->setLayout(layout);
    layout->setSpacing(0);
}

groupBox_leapButtons::~groupBox_leapButtons()
{
    delete ui;
}

void groupBox_leapButtons::slot_pushButton_clicked(leapButton *button)
{
    emit button_clicked(button);
}

void groupBox_leapButtons::addButton(leapButton *button)
{
    connect(button, SIGNAL(clicked(leapButton*)), this, SLOT(slot_pushButton_clicked(leapButton*)));

    layout->removeItem(my_spacer);
    layout->addWidget(button);
    layout->addItem(my_spacer);
}

void groupBox_leapButtons::addButton(QString name)
{
    leapButton *button = new leapButton();
    button->setName(name);

    connect(button, SIGNAL(clicked(leapButton*)), this, SLOT(slot_pushButton_clicked(leapButton*)));

    layout->removeItem(my_spacer);
    layout->addWidget(button);
    layout->addItem(my_spacer);
}

void groupBox_leapButtons::removeButton(leapButton *button)
{
    layout->removeWidget(button);
    delete button;
}

void groupBox_leapButtons::clear()
{
    leapButton *button;
    int i = 0;

    while(i < layout->count())
    {
        button = (leapButton*)layout->takeAt(0)->widget();
        removeButton(button);
    }
}

QList <QString> groupBox_leapButtons::getList()
{
    QList <QString> tempList;
    leapButton *tempButton;

    qDebug() << layout->count();

    for(int i = 0; i < layout->count()-1; i++)
    {
        tempButton = (leapButton*)layout->takeAt(i)->widget();
        tempList.push_back(tempButton->getName());
        layout->insertWidget(i, tempButton);
    }

    return tempList;
}
