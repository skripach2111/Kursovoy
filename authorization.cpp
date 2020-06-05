#include "authorization.h"
#include "ui_authorization.h"
#include<qdebug.h>

Authorization::Authorization(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Authorization)
{
    ui->setupUi(this);

    connect(ui->pushButton_Apply, SIGNAL(clicked()), this, SLOT(slot_pushButton_Apply_clicked()));
    connect(ui->pushButton_Discard, SIGNAL(clicked()), this, SLOT(slot_pushButton_Discard_clicked()));
    connect(ui->pushButton_Settings, SIGNAL(clicked()), this, SLOT(slot_pushButton_Settings_clicked()));

    QSettings settings("settings.conf", QSettings::IniFormat);

    settings.beginGroup("ConnectionSettings");
    ui->lineEdit_HostAddress->setText( settings.value("HostAddress", -1).toString() );
    ui->lineEdit_HostPort->setText( settings.value("HostPort", -1).toString() );
    settings.endGroup();

    settings.beginGroup("LoginSettings");
    ui->lineEdit_Login->setText(settings.value("UserLogin", -1).toString());
    settings.endGroup();
}

Authorization::~Authorization()
{
    delete ui;
}


void Authorization::on_pushButton_Exit_clicked()
{
    db.close();
    this->close();
}

void Authorization::on_pushButton_Entry_clicked()
{
    QSettings settings("settings.conf", QSettings::IniFormat);

    settings.beginGroup("LoginSettings");
    settings.setValue("UserLogin", ui->lineEdit_Login->text());
    settings.endGroup();

    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setDatabaseName("study");
    db.setHostName(ui->lineEdit_HostAddress->text());
    db.setUserName(ui->lineEdit_Login->text());
    db.setPassword(ui->lineEdit_Password->text());
    db.setPort(ui->lineEdit_HostPort->text().toInt());

    bool ok = db.open();

    if(ok)
    {
        ui->label_Message->setText("Введённые данные верны!");

        QSqlQuery query;
        query.exec("SELECT * FROM users");

        while (query.next())
        {
            if(query.value(0).toString() == ui->lineEdit_Login->text())
            {
                if(query.value(1).toString() == "Admin")
                {
                    AdminMain *window = new AdminMain;
                    if(window->takeConnect(db))
                    {
                        db.close();
                        this->close();

                        window->show();
                    }
                    else
                    {
                        ui->label_Message->setText("Не удалось подключится!");
                    }
                }
                else if(query.value(1).toString() == "Exp")
                {
                    ExpertMain *window = new ExpertMain;
                    if(window->takeConnect(db))
                    {
                        db.close();
                        this->close();

                        window->show();
                    }
                    else
                    {
                        ui->label_Message->setText("Не удалось подключится!");
                    }
                }

                break;
            }
            qDebug() << query.value(0).toString() << " " << query.value(1).toString() << endl;
        }
    }
    else
        ui->label_Message->setText("Неверный логин или пароль!");
}

void Authorization::slot_pushButton_Apply_clicked()
{
    QSettings settings("settings.conf", QSettings::IniFormat);
    settings.beginGroup("ConnectionSettings");
    settings.setValue("HostAddress", ui->lineEdit_HostAddress->text());
    settings.setValue("HostPort", ui->lineEdit_HostPort->text());
    settings.endGroup();

    ui->stackedWidget_MainWidget->setCurrentIndex(0);
}

void Authorization::slot_pushButton_Discard_clicked()
{
    ui->stackedWidget_MainWidget->setCurrentIndex(0);

    QSettings settings("settings.conf", QSettings::IniFormat);

    settings.beginGroup("ConnectionSettings");
    ui->lineEdit_HostAddress->setText( settings.value("HostAddress", -1).toString() );
    ui->lineEdit_HostPort->setText( settings.value("HostPort", -1).toString() );
    settings.endGroup();
}

void Authorization::slot_pushButton_Settings_clicked()
{
    ui->stackedWidget_MainWidget->setCurrentIndex(1);
}
