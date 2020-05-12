#ifndef INFORMATIONDB_DIALOG_H
#define INFORMATIONDB_DIALOG_H

#include <QDialog>

namespace Ui {
class InformationDB_Dialog;
}

class InformationDB_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit InformationDB_Dialog(QWidget *parent = nullptr);
    ~InformationDB_Dialog();

private:
    Ui::InformationDB_Dialog *ui;
};

#endif // INFORMATIONDB_DIALOG_H
