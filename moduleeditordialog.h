#ifndef MODULEEDITORDIALOG_H
#define MODULEEDITORDIALOG_H

#include <QDialog>
#include <QTableWidgetItem>

#include "database.h"
#include "competenceselectiondialog.h"

namespace Ui {
class ModuleEditorDialog;
}

class ModuleEditorDialog : public QDialog
{
    Q_OBJECT

    Discipline subject;
    vector <Module> module;
    vector <Mod_Comp> mod_comp;
    vector <Competence> competences;
    QList <QString> listCompetensesID;

    int currentRow;

public:
    explicit ModuleEditorDialog(QWidget *parent = nullptr);
    ~ModuleEditorDialog();

    void setData(vector <Module> modules, Discipline subject, vector <Mod_Comp> modcomp, vector <Competence> compet);

signals:
    void takeResult(vector <Module> modules, vector <Mod_Comp> compet);

private slots:
    void on_pushButton_Add_clicked();

    void on_tableWidget_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous);

    void on_pushButton_Change_clicked();

    void on_pushButton_Delete_clicked();

    void on_pushButton_Cancel_clicked();

    void on_pushButton_Save_clicked();

    void on_pushButton_SetCompetences_clicked();

    void slot_getInfoFrom_CompetenceSelectionDialog(QList <QString> resultList);

private:
    Ui::ModuleEditorDialog *ui;
};

#endif // MODULEEDITORDIALOG_H
