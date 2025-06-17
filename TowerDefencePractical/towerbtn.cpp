#include "towerbtn.h"
#include <QSoundEffect>
#include <QDebug>

TowerBtn::TowerBtn(QWidget *parent, int towerType) : QWidget(parent), towerType(towerType), state(false)
{
    setFixedSize(100, 100);
    setStyleSheet("background: transparent;"); // Ensure widget background is transparent

    outline = new QLabel(this);
    outline->setGeometry(0, 0, width(), height());
    outline->setAttribute(Qt::WA_TransparentForMouseEvents); // Allows parent to receive clicks



    switch(towerType)
    {
    case 0: // Regular Tower
        outline->setStyleSheet("width:100px;height:100px;border: 1px solid white;image: url(:/RegTower.png);background: transparent;");
        towerCost = 20;
        damage = 15;
        attackCooldown = 1000;


        break;
    case 1: // Big Tower
        outline->setStyleSheet("width:100px;height:100px;border: 1px solid white;image: url(:/BigTower.png);background: transparent;");
        towerCost = 30;
        damage = 20;
        attackCooldown = 1500;
        break;
    case 2: // Fast Tower
        outline->setStyleSheet("width:100px;height:100px;border: 1px solid white;image: url(:/FastTower.png);background: transparent;");
        towerCost = 25;
        attackCooldown = 500;
        damage = 10;
        break;
    case 3: // LandMine
        outline->setStyleSheet("width:100px;height:100px;border: 1px solid white;image: url(:/Mine.png);background: transparent;");
        towerCost = 15;
        damage = 100;
        break;
    default: // Wall
        outline->setStyleSheet("width:100px;height:100px;border: 1px solid white;image: url(:/RegTower.png);background: transparent;");
        break;
    }
    state = false;
}

void TowerBtn::setInteractive(bool interactive)
{
    if (!interactive) {
        outline->setStyleSheet(outline->styleSheet().replace("border: 1px solid white;", ""));
        setAttribute(Qt::WA_TransparentForMouseEvents, true);
        setStyleSheet("background: transparent;"); // Reinforce transparency for placed towers
    } else {
        setAttribute(Qt::WA_TransparentForMouseEvents, false);
        setStyleSheet("background: transparent;"); // Ensure transparency for interactive buttons
    }
}

void TowerBtn::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        state = !state;
        emit towerSelected(towerType);
        qDebug() << towerType << endl;
    }
}
