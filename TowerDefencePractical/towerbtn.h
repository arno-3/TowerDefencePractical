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
    int getDamage() const {return damage;}
    bool canAttack() const { return cooldownTimer <= 0; }
    void resetCooldown() { cooldownTimer = attackCooldown; }
    void updateCooldown(int deltaTime) { if (cooldownTimer > 0) cooldownTimer -= deltaTime; }


signals:
    void clicked(bool);
    void towerSelected(int towerType);

private:
    void mousePressEvent (QMouseEvent *);
    bool state;

    QLabel *outline;
    int towerType;
    int damage;
    int attackCooldown;
    int cooldownTimer;

};

#endif // TOWERBTN_H
