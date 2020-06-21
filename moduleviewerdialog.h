#ifndef MODULEVIEWERDIALOG_H
#define MODULEVIEWERDIALOG_H

#include <QDialog>
#include <QTableWidgetItem>
#include "database.h"

namespace Ui {
class ModuleViewerDialog;
}

class ModuleViewerDialog : public QDialog
{
    Q_OBJECT

    vector <Module> module;

public:
    explicit ModuleViewerDialog(QWidget *parent = nullptr);
    ~ModuleViewerDialog();

    void setData(vector <Module> modules, Discipline subject);

private slots:
    void on_tableWidget_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous);

    void on_pushButton_close_clicked();

private:
    Ui::ModuleViewerDialog *ui;
};

#endif // MODULEVIEWERDIALOG_H
