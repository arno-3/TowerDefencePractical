#include "enemies.h"
#include <QTimer>
//#include <QGraphicsOpacityEffect>
#include <QDebug>
#include <cmath>
#include <QThread>


class SpawnControl : public QObject
{
    Q_OBJECT

public slots:
    explicit SpawnControl(QObject *p = nullptr)
    {
        E =(enemies*)p;
        timer->setInterval(10);
        connect(timer,&QTimer::timeout,this,&SpawnControl::spawnSlot);
        timer->start();
        tick = 0;
    };
    void spawnSlot()
    {
        ++tick;
        QGraphicsOpacityEffect *opacity = new QGraphicsOpacityEffect;
        double qr = 1.0f;
        qDebug()<<"|"<< E->properties.type <<"| SPAWNING |"<< tick <<endl;
        qr = (tick<100)?(100-tick)/100:(tick>=100 && tick < 200)?(tick-100)/100:-1;
        bool spawned = (qr>=0)?false:true;
        E->spawnStart(spawned);
        opacity->setOpacity(qr);
        E->Opacity(opacity);

        if(spawned)
            this->deleteLater();

    };
private:
    enemies *E;
    QTimer *timer = new QTimer;
    QThread *thread = new QThread;
    int tick = 0;
};















enemies::enemies(QWidget *parent, int enemyType, QPoint *spawnPos, int x, int y) : QWidget(parent)
{
    setFixedSize(100, 100);
    setStyleSheet("background: transparent;"); // Ensure widget background is transparent

    outline = new QLabel(this);
    outline->setGeometry(0,0,width(),height());


    hBar = new QProgressBar(this);
    hBar->setGeometry(0,0,100,10);
    hBar->setTextVisible(false);
    hBar->setStyleSheet(
        "QProgressBar {"
        "   border: 1px solid black;"
        "   background: transparent;"
        "}"
        "QProgressBar::chunk {"
        "   background-color: green;" // Green when healthy
        "}"
    );


    switch(enemyType)
    {
    case 0://Small
        properties.health = 20;
        properties.damage = 5;//percentage
        properties.speed = 1000;
        properties.type = 0;//store type
        properties.goldReward = 10;
        outline->setStyleSheet("image: url(:/SmallAlien.png);");
        hBar->setMaximum(20);
        hBar->setValue(properties.health);
        break;
    case 1://Big
        properties.health = 50;
        properties.damage = 25;//percentage
        properties.speed = 1500;
        properties.type = 1;//store type
        properties.goldReward = 20;
        outline->setStyleSheet("image: url(:/BigAlien.png); background:rgba(0,0,0,0);");
        hBar->setMaximum(50);
        hBar->setValue(properties.health);
        break;
    case 2://Spaceship
        properties.health = 20;
        properties.damage = 30;//percentage
        properties.speed = 2000;
        properties.goldReward = 30;
        properties.type = 2;//store type
        outline->setStyleSheet("image: url(:/Spaceship.png);");
        hBar->setMaximum(100);
        hBar->setValue(properties.health);
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
    hBar->show();

    currentHop = *spawnPos;
    move(x, y);

    timer = new QTimer();
    connect(timer,&QTimer::timeout,this,&enemies::start);
    tick = 0;
    timer->setInterval(10);
    timer->start();

//    spwnThread = new ThreadTimer();
//    QThread *threadSpawn =new QThread;
//    spwnThread->moveToThread(threadSpawn);
//    connect(threadSpawn,&QThread::started,spwnThread,&ThreadTimer::run);

//    connect(spwnThread, &ThreadTimer::opacify,this,&enemies::opacitySlot);
//    connect(spwnThread,&ThreadTimer::finish,this,&enemies::spawn);
//    connect(spwnThread,&ThreadTimer::finish,threadSpawn,&QThread::quit);
//    connect(threadSpawn,&QThread::finished,threadSpawn,&QThread::deleteLater);

//    threadSpawn->start();

    healthTimer = new QTimer(this);
    connect(healthTimer, &QTimer::timeout, this, &enemies::updateHealthBar);
    healthTimer->start(100);
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

void enemies::updateHealthBar() {
    hBar->setValue(properties.health);
    if (properties.health <= 0) {
        hBar->hide();
    } else {
        // Change color based on health
        QString color = properties.health > 100 * 0.5 ? "green" :
                        properties.health > 100 * 0.25 ? "yellow" : "red";
        hBar->setStyleSheet(
            QString(
                "QProgressBar {"
                "   border: 1px solid black;"
                "   background: transparent;"
                "}"
                "QProgressBar::chunk {"
                "   background-color: %1;"
                "}"
            ).arg(color)
        );
    }
}


void enemies::spawnStart(bool spwn)
{
    spawned = spwn;
}

void enemies::Opacity(QGraphicsOpacityEffect* opacity)
{
    this->setGraphicsEffect(opacity);
}

void enemies::spawn()
{
    spawned = true;
}


void enemies::opacitySlot(QGraphicsOpacityEffect *op)
{

}
