#include "towerbtn.h"
#include <QSoundEffect>

TowerBtn::TowerBtn(QWidget *parent) : QWidget(parent)
{
    setFixedSize(100, 100);

    outline = new QLabel(this);
    outline->setGeometry(0, 0, width(), height());
    outline->setStyleSheet("border: 1px solid white; background-color: rgba(0, 0, 0, 0);");
    outline->setAttribute(Qt::WA_TransparentForMouseEvents);  // Allows the parent to receive the click
    state = true;

}

void TowerBtn::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        state = !state;
        emit clicked(state);
    }
}
