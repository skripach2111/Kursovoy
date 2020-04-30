#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <debug/debug.h>
#include <QSqlDriver>
#include <QSql>
#include <QDebug>

#include "adminmain.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Authorization; }
QT_END_NAMESPACE

class Authorization : public QDialog
{
    Q_OBJECT

public:
    Authorization(QWidget *parent = nullptr);
    ~Authorization();

    void GetSettings(QString HostAddress, QString HostPort);

private slots:
    void on_pushButton_Exit_clicked();

    void on_pushButton_Entry_clicked();

    void slot_pushButton_Apply_clicked();
    void slot_pushButton_Discard_clicked();
    void slot_pushButton_Settings_clicked();

private:
    Ui::Authorization *ui;

    QSqlDatabase db;
};
#endif // AUTHORIZATION_H
