#ifndef MODULEEDITORDIALOG_H
#define MODULEEDITORDIALOG_H

#include <QDialog>
#include <QTableWidgetItem>

#include "database.h"

namespace Ui {
class ModuleEditorDialog;
}

class ModuleEditorDialog : public QDialog
{
    Q_OBJECT

    Discipline subject;
    vector <Module> module;
    vector <Mod_Comp> mod_comp;

    int currentRow;

public:
    explicit ModuleEditorDialog(QWidget *parent = nullptr);
    ~ModuleEditorDialog();

    void setData(vector <Module> modules, Discipline subject, vector <Mod_Comp> modcomp);

signals:
    void takeResult(vector <Module> modules);

private slots:
    void on_pushButton_Add_clicked();

    void on_tableWidget_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous);

    void on_pushButton_Change_clicked();

    void on_pushButton_Delete_clicked();

    void on_pushButton_Cancel_clicked();

    void on_pushButton_Save_clicked();

private:
    Ui::ModuleEditorDialog *ui;
};

#endif // MODULEEDITORDIALOG_H
