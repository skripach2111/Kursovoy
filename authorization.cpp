#include "authorization.h"
#include "ui_authorization.h"
#include<qdebug.h>

Authorization::Authorization(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Authorization)
{
    ui->setupUi(this);
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
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setDatabaseName("study");
    db.setHostName("127.0.0.1");
    db.setUserName(ui->lineEdit_Login->text());
    db.setPassword(ui->lineEdit_Password->text());
    db.setPort(3306);

    bool ok = db.open();

    if(ok)
    {
        ui->label_Message->setText("Подключено!");

        QSqlQuery query;
        query.exec("SELECT * FROM users");

        while (query.next())
        {
            if(query.value(0).toString() == ui->lineEdit_Login->text())
            {
                if(query.value(1).toString() == "admin")
                {
                    AdminMain *window = new AdminMain;
                    window->takeConnect(db);

                    db.close();
                    this->close();

                    window->show();
                }

                break;
            }
            qDebug() << query.value(0).toString() << " " << query.value(1).toString() << endl;
        }
    }
    else
        ui->label_Message->setText("Неверный логин или пароль!");
}
