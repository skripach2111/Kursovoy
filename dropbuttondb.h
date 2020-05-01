#ifndef DROPBUTTONDB_H
#define DROPBUTTONDB_H

#include <QWidget>
#include "dropmenudb.h"

namespace Ui {
class dropButtonDB;
}

class dropButtonDB : public QWidget
{
    Q_OBJECT

    dropMenuDB *mydropMenu = new dropMenuDB;
    QString name;

public:
    explicit dropButtonDB(QWidget *parent = nullptr);

    void setInfo(QString nameDB);
    ~dropButtonDB();

public slots:
    void slot_commandLinkButton_clicked();
    void slot_pushButton_Details_clicked();
    void slot_pushButton_DeleteDB_clicked();

signals:
    void showDetails(QString nameDB);
signals:
    void deleteDB(QString nameDB);

private:
    Ui::dropButtonDB *ui;
};

#endif // DROPBUTTONDB_H
