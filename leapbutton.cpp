#include "leapbutton.h"
#include "ui_leapbutton.h"
#include <QDebug>

leapButton::leapButton(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::leapButton)
{
    ui->setupUi(this);

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(slot_pushButton_clicked()));
}

leapButton::~leapButton()
{
    delete ui;
}

void leapButton::slot_pushButton_clicked()
{
    emit clicked(this);
}

void leapButton::setName(QString newName)
{
    ui->pushButton->setText(newName);
}

QString leapButton::getName()
{
    qDebug() << ui->pushButton->text();
    return ui->pushButton->text();
}
