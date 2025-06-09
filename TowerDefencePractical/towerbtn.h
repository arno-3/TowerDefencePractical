#ifndef TOWERBTN_H
#define TOWERBTN_H

#include <QWidget>
#include <QLabel>
#include <QMouseEvent>

class TowerBtn : public QWidget
{
    Q_OBJECT
public:
    explicit TowerBtn(QWidget *parent = nullptr, int towerSelect = 0);

signals:
    void clicked(bool);

private:
    void mousePressEvent (QMouseEvent *);
    bool state;

    QLabel *outline;

};

#endif // TOWERBTN_H
