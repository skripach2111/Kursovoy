#ifndef ADMINMAIN_H
#define ADMINMAIN_H

#include <QDialog>
#include <QtSql>
#include <QDebug>
#include <QVariant>
//#include <QAxObject>
#include <QPrinter>
#include <QPainter>
#include <QFileDialog>
#include <QMessageBox>

#include "database.h"
#include "databasebuffer.h"
#include "dropbuttondb.h"
#include "usersselectiondialog.h"


namespace Ui {
class AdminMain;
}

class AdminMain : public QDialog
{
    Q_OBJECT

    QSqlDatabase db;
    Database mydb;
    QPrinter printer;

    DatabaseBuffer db_buffer;


public:
    explicit AdminMain(QWidget *parent = nullptr);
    ~AdminMain();

    bool takeConnect(QSqlDatabase d);

public slots:
    void slot_getInfoFrom_UserSelectionDialog(QList <QString> resultList);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_Return_clicked();

    void on_pushButton_Open_clicked();

    void on_pushButton_Gotovo_clicked();

//    void on_tableWidget_Zachet_itemClicked(QTableWidgetItem *item);

    void on_tableWidget_Zachet_cellClicked(int row, int column);
    void slotPushButtonExportDoc_clicked();
    void slotAddNewDB();

    void on_pushButton_ExportPdf_clicked();

    void on_commandLinkButton_AddNewDB_clicked();

    void on_commandLinkButton_ViewDBs_clicked();

    void on_commandLinkButton_AddNewUser_clicked();

    void on_commandLinkButton_ViewUsers_clicked();

    void on_lineEdit_NameDB_editingFinished();

    void on_pushButton_AddNewDB_Next_1_clicked();

    void on_pushButton_InMainPage_DB_clicked();

    void on_pushButton_AddMoreDB_clicked();

    void on_pushButton_ChangeUsers_clicked();

    void on_plainTextEdit_InformationDB_textChanged();

private:
    Ui::AdminMain *ui;
};

#endif // ADMINMAIN_H
