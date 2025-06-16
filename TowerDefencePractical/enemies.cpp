#include "enemies.h"
#include <QTimer>
#include <QGraphicsOpacityEffect>
#include <QDebug>
#include <cmath>
#include <QThread>

enemies::enemies(QWidget *parent, int enemyType, QPoint *spawnPos, int x, int y) : QWidget(parent)
{
    setFixedSize(100, 100);
    setStyleSheet("background: transparent;"); // Ensure widget background is transparent

    outline = new QLabel(this);
    outline->setGeometry(0,0,width(),height());
//    outline->setAttribute(Qt::WA_TranslucentBackground);

    switch(enemyType)
    {
    case 0://Small
        properties.damage = 5;//percentage
        properties.speed = 1000;
        properties.type = 0;//store type
        outline->setStyleSheet("image: url(:/SmallAlien.png);");
        break;
    case 1://Big
        properties.damage = 25;//percentage
        properties.speed = 1500;
        properties.type = 1;//store type
        outline->setStyleSheet("image: url(:/BigAlien.png); background:rgba(0,0,0,0);");
        break;
    case 2://Spaceship
        properties.damage = 30;//percentage
        properties.speed = 2000;
        properties.type = 2;//store type
        outline->setStyleSheet("image: url(:/Spaceship.png);");
        break;
    default:
        properties.damage = 20;//percentage
        properties.speed = 2;//blocks per second
        properties.type = 2;//store type
        outline->setStyleSheet("image: url(:/Spaceship.png);");
        break;
    }
    outline->raise();
    outline->show();

    currentHop = *spawnPos;
    move(x, y);

    timer = new QTimer();
    connect(timer,&QTimer::timeout,this,&enemies::start);
    tick = 0;
    timer->setInterval(10);
    timer->start();
}



void enemies::glow()
{
    timer = new QTimer();
    connect(timer,&QTimer::timeout,this,&enemies::glowTick);
//    outline->setStyleSheet("opacity: 0%;");
    timer->setInterval(10);
    timer->start();
    tick = 0.0;
}

void enemies::glowTick()
{
    ++tick;
    QGraphicsOpacityEffect *opacity = new QGraphicsOpacityEffect;
    double qr = 1.0f;
    if(glowCount<=3)
    {
        if(tick<=100)
        {
            qr = (100-tick)/100;
        }
        else if(tick<=200)
        {
            qr = (tick-100)/100;

        }
        else if(tick>201)
        {
            tick = 0;
             ++glowCount;
            qr = 1.0f;
        }
    }
    else
    {
        glowCount = 0;
        timer->stop();
        timer->deleteLater();
    }
    opacity->setOpacity(qr);
    outline->setGraphicsEffect(opacity);
}

void enemies::mousePressEvent(QMouseEvent *m)
{
    glow();
    qDebug() << "Buttoned"<<endl;
}


QPoint enemies::getPos()
{
    return currentHop;
}

void enemies::moveTo(QPoint nexPosition, int x, int y)
{
    moving = true;
    currentHop = nexPosition;
    tX = x;
    tY = y;
    glide(x, y);
    //move(x,y);
    //moving = false;
}

void enemies::moveNext()
{
//    this->move(nextHop.x(),nextHop.y());

}

bool enemies::isMoving()
{
    return moving;
}

void enemies::glideTick()
{
    ++glideT;

  // move(x()+dShiftX,y()+dShiftY);
    qDebug() << properties.type <<"|"<<abs(x()-tX)<<":"<<(y()-tY)<<endl;
    if(glideMax != glideT)
    {
        int cX = qRound(glideT*properties.dX);
        int cY = qRound(glideT*properties.dY);
        move(tX+cX,y());
        move(x(),tY+cY);
    }

    else
    {
        glideT = 0;
        glideMax = 0;
        moving =false;
        t->stop();
        t->deleteLater();
    }
    //QThread::msleep(5);

}

void enemies::glide(int x, int y)
{
    int dX = (x-this->x());
    int dY = (y-this->y());

    tX = this->x();
    tY = this->y();

    int tickInterval = 10;

    double tickpermovement = (properties.speed/tickInterval);
    double dx = ((dX)/tickpermovement);
    double dy = ((dY)/tickpermovement);

    properties.dX = (dx);
    properties.dY = (dy);

    glideMax =tickpermovement;
    glideT = 0;
    qDebug() <<"|| "<<glideMax;

    t = new QTimer();
    t->setInterval(tickInterval);

    connect(t, &QTimer::timeout,this,&enemies::glideTick);
    t->start();
}

void enemies::start()
{
    ++tick;
    QGraphicsOpacityEffect *opacity = new QGraphicsOpacityEffect;
    double qr = 1.0f;
    qDebug()<<"SPAWNING |"<<tick <<endl;

    if(tick<=200)
    {
        if(tick<=100)
        {
            qr = (100-tick)/100;
        }
        else if(tick<=200)
        {
            qr = (tick-100)/100;

        }
        else if(tick>200)
        {
            tick = 0;
            qr = 1.0f;
        }
    }
    else
    {
        tick = 0;
        timer->stop();
        timer->deleteLater();
        spawned = true;
    }
    opacity->setOpacity(qr);
    outline->setGraphicsEffect(opacity);

}


bool enemies::crashed()
{
    return bCrashed;
}

bool enemies::hasSpawned()
{
    return spawned;
}
