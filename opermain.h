#ifndef OPERMAIN_H
#define OPERMAIN_H

#include <QDialog>
#include <QtSql>
#include <QDebug>
#include <QVariant>
//#include <QAxObject>
#include <QPrinter>
#include <QPainter>
#include <QFileDialog>
#include <QMessageBox>
#include <QListWidgetItem>

#include "database.h"
#include "databasebuffer.h"

namespace Ui {
class OperMain;
}

class OperMain : public QWidget
{
    Q_OBJECT

    QSqlDatabase db;
    Database mydb;
    QPrinter printer;

    DatabaseBuffer db_buffer;

    bool Mode = true;

public:
    explicit OperMain(QWidget *parent = nullptr);
    ~OperMain();

    bool takeConnect(QSqlDatabase d);

private slots:
    void on_listWidget_ListDatabases_currentRowChanged(int currentRow);

    void on_pushButton_Open_clicked();

    void on_commandLinkButton_clicked();

    void on_commandLinkButton_2_clicked();

    void on_commandLinkButton_3_clicked();

    void on_commandLinkButton_4_clicked();

    void on_listWidget_Competences2_currentRowChanged(int currentRow);

    void on_listWidget_Competences1_currentRowChanged(int currentRow);

    void on_comboBox_SetRange_currentIndexChanged(int index);

    void on_listWidget_ListCompetences_currentRowChanged(int currentRow);

    void on_listWidget_ListQuestions_currentRowChanged(int currentRow);

private:
    Ui::OperMain *ui;
};

#endif // OPERMAIN_H
