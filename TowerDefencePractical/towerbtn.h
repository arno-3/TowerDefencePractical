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
    int getTowerType() const { return towerType; }
    void setInteractive(bool interactive);
    int towerCost;


signals:
    void clicked(bool);
    void towerSelected(int towerType);

private:
    void mousePressEvent (QMouseEvent *);
    bool state;

    QLabel *outline;
    int towerType;

};

#endif // TOWERBTN_H
