#ifndef ADDDB_DIALOG_H
#define ADDDB_DIALOG_H

#include <QDialog>

namespace Ui {
class adddb_dialog;
}

class adddb_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit adddb_dialog(QWidget *parent = nullptr);
    ~adddb_dialog();

private:
    Ui::adddb_dialog *ui;
};

#endif // ADDDB_DIALOG_H
