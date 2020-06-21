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
#include <QTreeWidgetItem>

#include "database.h"
#include "databasebuffer.h"
#include "moduleviewerdialog.h"
#include "moduleeditordialog.h"

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

    void on_comboBox_SetRange_2_currentIndexChanged(int index);

    void on_treeWidget_Subjects1_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

    void on_treeWidget_Subjects2_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

    void on_pushButton_ViewModulesViewer_clicked();

    void on_pushButton_ViewMode_clicked();

    void on_pushButton_EditMode_clicked();

    void on_pushButton_EditModuleEditor_clicked();

    void slot_getResult(vector <Module> module, vector <Mod_Comp> mod_comp);

    void on_pushButton_3_clicked();

    void on_commandLinkButton_5_clicked();

    void on_tableWidget_Subjects_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous);

    void on_tableWidget_Subjects_cellClicked(int row, int column);

private:
    Ui::OperMain *ui;
};

#endif // OPERMAIN_H
