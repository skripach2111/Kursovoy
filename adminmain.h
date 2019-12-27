#ifndef ADMINMAIN_H
#define ADMINMAIN_H

#include <QDialog>
#include <QtSql>
#include <QDebug>
#include <QVariant>
#include <QAxObject>
#include

#include "database.h"

namespace Ui {
class AdminMain;
}

class AdminMain : public QDialog
{
    Q_OBJECT

    QSqlDatabase db;
    Database mydb;


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

//    void on_tableWidget_Zachet_itemClicked(QTableWidgetItem *item);

    void on_tableWidget_Zachet_cellClicked(int row, int column);
    void slotPushButtonExportDoc_clicked();

private:
    Ui::AdminMain *ui;
};

#endif // ADMINMAIN_H
