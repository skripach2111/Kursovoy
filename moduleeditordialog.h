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

    int currentRow;

public:
    explicit ModuleEditorDialog(QWidget *parent = nullptr);
    ~ModuleEditorDialog();

    void setData(vector <Module> modules, Discipline subject);

signals:
    void takeResult(vector <Module> modules);

private slots:
    void on_pushButton_Add_clicked();

    void on_tableWidget_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous);

private:
    Ui::ModuleEditorDialog *ui;
};

#endif // MODULEEDITORDIALOG_H
