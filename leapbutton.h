#ifndef LEAPBUTTON_H
#define LEAPBUTTON_H

#include <QWidget>

namespace Ui {
class leapButton;
}

class leapButton : public QWidget
{
    Q_OBJECT

public:
    explicit leapButton(QWidget *parent = nullptr);

    void setName(QString newName);
    QString getName();

    ~leapButton();

public slots:
    void slot_pushButton_clicked();

signals:
    void  clicked(leapButton *widget);

private:
    Ui::leapButton *ui;
};

#endif // LEAPBUTTON_H
