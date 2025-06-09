#ifndef MENUBTN_H
#define MENUBTN_H

#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QString>

class MenuBtn : public QWidget
{
    Q_OBJECT
public:
    explicit MenuBtn(QWidget *parent = nullptr, QString text = "Menu Item", int style = 0);
    void setState(bool);

signals:
    //signal for clicking to be sent
    void clicked(bool);

private:
    void mousePressEvent (QMouseEvent *);
    bool state;

    QLabel *outline;

};


#endif // MENUBTN_H
