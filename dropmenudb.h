#ifndef DROPMENUDB_H
#define DROPMENUDB_H

#include <QWidget>

namespace Ui {
class dropMenuDB;
}

class dropMenuDB : public QWidget
{
    Q_OBJECT

public:
    explicit dropMenuDB(QWidget *parent = nullptr);
    ~dropMenuDB();

public slots:
    void slot_pushButton_Details_clicked();
    void slot_pushButton_DeleteDB_clicked();

signals:
    void pushButton_Details_clicked();
signals:
    void pushButton_DeleteDB_clicked();

private:
    Ui::dropMenuDB *ui;
};

#endif // DROPMENUDB_H
