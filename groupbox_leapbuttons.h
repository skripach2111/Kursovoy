#ifndef GROUPBOX_LEAPBUTTONS_H
#define GROUPBOX_LEAPBUTTONS_H

#include <QWidget>
#include <QVBoxLayout>
#include "leapbutton.h"

#include <QDebug>

namespace Ui {
class groupBox_leapButtons;
}

class groupBox_leapButtons : public QWidget
{
    Q_OBJECT

    QVBoxLayout *mainlayout = new QVBoxLayout();
    QWidget *newWdget;
    QVBoxLayout *layout = new QVBoxLayout();
    QSpacerItem * my_spacer = new QSpacerItem(0,0, QSizePolicy::Expanding, QSizePolicy::Expanding);

public:
    explicit groupBox_leapButtons(QWidget *parent = nullptr);

    void addButton(QString name);
    void addButton(leapButton *button);

    void removeButton(leapButton *button);
    void clear();

    QList <QString> getList();

    ~groupBox_leapButtons();

public slots:
    void slot_pushButton_clicked(leapButton *button);

signals:
    void button_clicked(leapButton *button);

private:
    Ui::groupBox_leapButtons *ui;
};

#endif // GROUPBOX_LEAPBUTTONS_H
