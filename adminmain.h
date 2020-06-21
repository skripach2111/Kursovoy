#ifndef ADMINMAIN_H
#define ADMINMAIN_H

#include <QtWidgets>
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
#include "informationdb_dialog.h"
#include "databaseselectiondialog.h"
#include "informationuser_dialog.h"


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

    QVBoxLayout *mainlayoutDB = new QVBoxLayout();
    QWidget *newWdgetDB;
    QVBoxLayout *layoutDB = new QVBoxLayout();

    QVBoxLayout *mainlayoutUser = new QVBoxLayout();
    QWidget *newWdgetUser;
    QVBoxLayout *layoutUser = new QVBoxLayout();
    QSpacerItem *my_spacer = new QSpacerItem(0,0, QSizePolicy::Expanding, QSizePolicy::Expanding);


public:
    explicit AdminMain(QWidget *parent = nullptr);
    ~AdminMain();

    bool takeConnect(QSqlDatabase d);

    void addDropButton_DB(QString name);
    void clear_viewdb();

    void addDropButton_User(QString fio);
    void clear_viewuser();

public slots:
    void slot_getInfoFrom_UserSelectionDialog(QList <QString> resultList);
    void slot_getInfoFrom_DatabaseSelectionDialog(QList <QString> resultList);
    void slot_showDetails_DB(QString nameDB);
    void slot_showDetails_User(QString nameUser);
    //void slot_deleteDB(QString nameDB);

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

    void on_lineEdit_FIO_editingFinished();

    void on_radioButton_Admin_clicked();

    void on_radioButton_Operator_clicked();

    void on_radioButton_Expert_clicked();

    void on_lineEdit_UserLogin_editingFinished();

    void on_lineEdit_UserPassword_1_editingFinished();

    void on_lineEdit_UserPassword_2_editingFinished();

    void on_pushButton_ChangeTableDB_clicked();

    void on_pushButton_SearchDB_clicked();

private:
    Ui::AdminMain *ui;
};

#endif // ADMINMAIN_H
