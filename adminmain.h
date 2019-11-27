#ifndef ADMINMAIN_H
#define ADMINMAIN_H

#include <QDialog>
#include <QtSql>
#include <QDebug>

#include "database.h"

namespace Ui {
class AdminMain;
}

class AdminMain : public QDialog
{
    Q_OBJECT

    QSqlDatabase db;

public:
    explicit AdminMain(QWidget *parent = nullptr);
    ~AdminMain();

    void takeConnect(QSqlDatabase d);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_Return_clicked();

    void on_pushButton_Open_clicked();

    void on_pushButton_Gotovo_clicked();

private:
    Ui::AdminMain *ui;
};

#endif // ADMINMAIN_H
