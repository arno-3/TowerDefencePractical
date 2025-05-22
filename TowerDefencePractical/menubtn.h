#ifndef MENUBTN_H
#define MENUBTN_H

#include <QWidget>
#include <QLabel>
#include <QMouseEvent>

class MenuBtn : public QWidget
{
    Q_OBJECT
public:
    explicit MenuBtn(QWidget *parent = nullptr);

signals:
    void clicked(bool);

private:
    void mousePressEvent (QMouseEvent *);
    bool state;

    QLabel *outline;

};


#endif // MENUBTN_H
