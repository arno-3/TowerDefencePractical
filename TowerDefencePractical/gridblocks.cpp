#include "gridblocks.h"
//#include <QPushButton>
#include <QDebug>

gridBlocks::gridBlocks(QWidget *parent) : QWidget(parent), row(0), col(0)
{
    setFixedSize(100,100);
    mapGrid = new QLabel(this);
    mapGrid->setGeometry(0,0,width(),height());
    mapGrid->setStyleSheet("background:rgba(0, 0, 0, 0);");

    //setMouseTracking(true);
    setAttribute(Qt::WA_TranslucentBackground);

    btn = new QPushButton(this);
    btn->setStyleSheet("border-radius:15px; background-color: rgba(0,0,0,0);");
    btn->setFixedSize(30,30);
//    btn->show();
    btn->raise();
    int X = (mapGrid->x());
    int Y = mapGrid->y();

    btn->move(X+mapGrid->width()/2-10,Y+mapGrid->height()/2-10);
    btn->raise();


    mapGrid->setAlignment(Qt::AlignCenter);
//    btn
}

void gridBlocks::setGridPosition(int r, int c)
{
    row = r;
    col = c;
   // connect(btn, &QPushButton::clicked,this,&gridBlocks::btnClicked);
}

//void gridBlocks::mousePressEvent(QMouseEvent *event)
//{
//    if (event->button() == Qt::LeftButton)
//    {
//        QPointF p = event->localPos();

//        bool hr =p.x() >(this->x()+25) || p.x()<(x()+width()-25);
//        bool vr = p.y()>(this->y()+25) || p.y()<(y()+height()-25);
//        qDebug() << "CLICKED: :" << p<<endl;
//        if(hr && vr)
//            emit gridClicked(row, col);

//    }
//}

void gridBlocks::btnClicked()
{
    emit gridClicked(row, col);
    qDebug() <<"CLICKED"<<endl;
}

void gridBlocks::setProperly()
{/*
    mapGrid->setAttribute(Qt::WA_TransparentForMouseEvents);
    mapGrid->hide();
    btn->raise();
    btn->show();*/
}

int gridBlocks::get_x()
{
    return x();
}


int gridBlocks::get_y()
{
    return y();
}
