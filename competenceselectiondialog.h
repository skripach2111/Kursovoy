#ifndef COMPETENCESELECTIONDIALOG_H
#define COMPETENCESELECTIONDIALOG_H

#include <QDialog>

#include "database.h"
#include "groupbox_leapbuttons.h"

namespace Ui {
class CompetenceSelectionDialog;
}

class CompetenceSelectionDialog : public QDialog
{
    Q_OBJECT

    QList <QString> listCompetencesId;

public:
    explicit CompetenceSelectionDialog(QWidget *parent = nullptr);
    ~CompetenceSelectionDialog();

    void setAvailableCompetence(QList <QString> list);

public slots:
    void slot_groupBox_AllCompetences_triggerred(leapButton *button);

    void slot_groupBox_SelectedCompetences_triggerred(leapButton *button);

signals:
    void takeResult(QList <QString> listCompetences);

private slots:
    void on_pushButton_Save_clicked();

    void on_pushButton_Cancel_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::CompetenceSelectionDialog *ui;
};

#endif // COMPETENCESELECTIONDIALOG_H
