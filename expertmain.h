#ifndef EXPERTMAIN_H
#define EXPERTMAIN_H

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

namespace Ui {
class ExpertMain;
}

class ExpertMain : public QWidget
{
    Q_OBJECT

    QSqlDatabase db;
    Database mydb;
    QPrinter printer;

    DatabaseBuffer db_buffer;

public:
    explicit ExpertMain(QWidget *parent = nullptr);
    ~ExpertMain();

    bool takeConnect(QSqlDatabase d);

private slots:
    void on_listWidget_ListDatabases_currentRowChanged(int currentRow);

    void on_pushButton_Open_clicked();

    void on_listWidget_Competence1_currentRowChanged(int currentRow);

    void on_listWidget_Competence2_currentRowChanged(int currentRow);

private:
    Ui::ExpertMain *ui;
};

#endif // EXPERTMAIN_H
