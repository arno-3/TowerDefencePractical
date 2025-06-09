#include "towerbtn.h"
#include <QSoundEffect>

TowerBtn::TowerBtn(QWidget *parent, int towerSelect) : QWidget(parent)
{
    setFixedSize(100, 100);

    outline = new QLabel(this);
    outline->setGeometry(0, 0, width(), height());
    outline->setStyleSheet("border: 1px solid white; background-color: rgba(0, 0, 0, 0);");
    outline->setAttribute(Qt::WA_TransparentForMouseEvents);  // Allows the parent to receive the click


    switch(towerSelect)
    {
    case 0://Regular Tower
        outline->setStyleSheet("width:100px;height:100px;border: 1px solid white; image: url(:/RegTower.png);");
        break;
    case 1://Big Tower
        outline->setStyleSheet("width:100px;height:100px;border: 1px solid white; image: url(:/BigTower.png);");
        break;
    case 2://Fast Tower
        outline->setStyleSheet("width:100px;height:100px;border: 1px solid white; image: url(:/FastTower.png);");
        break;
    case 3://LandMine
        outline->setStyleSheet("width:100px;height:100px;border: 1px solid white; image: url(:/RegTower.png);");
        break;
    default://Wall
        outline->setStyleSheet("width:100px;height:100px;border: 1px solid white; image: url(:/RegTower.png);");
        break;
    }
    state = false;
}

void TowerBtn::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        state = !state;
        emit clicked(state);
    }
}
