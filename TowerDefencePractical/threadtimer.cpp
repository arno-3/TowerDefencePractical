#include "threadtimer.h"
#include <QGraphicsOpacityEffect>

ThreadTimer::ThreadTimer()
{

}

//ThreadTimer::~ThreadTimer()
//{

//}

void ThreadTimer::run()
{
    timer = new QTimer();
    connect(timer, &QTimer::timeout,this,&ThreadTimer::Timeout);
    timer->start(10);

}

void ThreadTimer::Timeout()
{
    if(timerType == 0) //spawning
        spawn(++spawnT);
    else if(timerType == 1)
        health(++healthT);
}

void ThreadTimer::spawn(int tick)
{
    double qr = (tick<100)?(100-tick)/100:(tick>=100 && tick < 200)?(tick-100)/100:-1;
    bool spawned = (qr>=0)?false:true;
    QGraphicsOpacityEffect *opacity = new QGraphicsOpacityEffect();
    opacity->setOpacity(qr);
    emit opacify(opacity);
    if(spawned)
    {
        timer->stop();
        timer->deleteLater();
        emit finish();
    }
//    parent->
}

void ThreadTimer::health(int tick)
{
//
}
