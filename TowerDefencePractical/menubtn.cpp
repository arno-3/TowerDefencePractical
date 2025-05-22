#include "menubtn.h"

MenuBtn::MenuBtn(QWidget *parent) : QWidget(parent)
{
    setFixedSize(250, 75);

    outline = new QLabel(this);
    outline->setGeometry(0, 0, width(), height());
    outline->setStyleSheet("border: 1px solid white;");

}

void MenuBtn::mousePressEvent(QMouseEvent *e)
{
//    if(e->button() == Qt::LeftButton)
//    {
//        state = !state;
//        if (state)
//             level->setStyleSheet("background-color: blue;");
//        else
//             level->setStyleSheet("background-color: cyan;");

}
