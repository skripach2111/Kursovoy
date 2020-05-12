#ifndef INFORMATIONUSER_DIALOG_H
#define INFORMATIONUSER_DIALOG_H

#include <QDialog>

namespace Ui {
class InformationUser_Dialog;
}

class InformationUser_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit InformationUser_Dialog(QWidget *parent = nullptr);
    ~InformationUser_Dialog();

private:
    Ui::InformationUser_Dialog *ui;
};

#endif // INFORMATIONUSER_DIALOG_H
