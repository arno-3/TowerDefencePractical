#include "enemies.h"
#include <QTimer>
#include <QGraphicsOpacityEffect>
#include <QDebug>
#include <cmath>
#include <QThread>

enemies::enemies(QWidget *parent, int enemyType, QPoint *spawnPos, int x, int y, int wave) : QWidget(parent)
{
    setFixedSize(100, 100);
    setStyleSheet("background: transparent;"); // Ensure widget background is transparent

    outline = new QLabel(this);
    outline->setGeometry(0,0,width(),height());

//    outline->setAttribute(Qt::WA_TranslucentBackground);

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
    case 0: // Small
        properties.maxHealth = 20 * (1 + wave / 5);
        properties.health = properties.maxHealth;
        properties.damage = 5; // percentage
        properties.speed = 100; // 100 pixels per second
        properties.type = 0;
        properties.goldReward = 15;
        outline->setStyleSheet("image: url(:/SmallAlien.png);");
        hBar->setMaximum(properties.maxHealth);
        hBar->setValue(properties.health);
        break;
    case 1: // Big
        properties.maxHealth = 50 * (1 + wave / 5);
        properties.health = properties.maxHealth;
        properties.damage = 25; // percentage
        properties.speed = 50; // 50 pixels per second
        properties.type = 1;
        properties.goldReward = 25;
        outline->setStyleSheet("image: url(:/BigAlien.png); background:rgba(0,0,0,0);");
        hBar->setMaximum(properties.maxHealth);
        hBar->setValue(properties.health);
        break;
    case 2: // Spaceship
        properties.maxHealth = 100 * (1 + wave / 5);
        properties.health = properties.maxHealth;
        properties.damage = 30; // percentage
        properties.speed = 25; // 25 pixels per second
        properties.goldReward = 45;
        properties.type = 2;
        outline->setStyleSheet("image: url(:/Spaceship.png);");
        hBar->setMaximum(properties.maxHealth);
        hBar->setValue(properties.health);
        break;
    default:
        properties.damage = 20; // percentage
        properties.speed = 25; // Default speed
        properties.type = 2;
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
//    QTimer::singleShot(2000,this,[]{})

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
    //qr = (tick<100)?(100-tick)/100:(tick<200)?(tick-100)/100:-1;

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

}

void enemies::glide(int x, int y)
{
    int dX = (x - this->x());
    int dY = (y - this->y());

    tX = this->x();
    tY = this->y();

    int tickInterval = 10; // 10ms
    double distance = std::sqrt(dX * dX + dY * dY); // Euclidean distance
    double speed = properties.speed; // Pixels per second
    double timeInSeconds = distance / speed; // Time to cover the distance
    double tickpermovement = (timeInSeconds * 1000) / tickInterval; // Convert to ticks

    if (tickpermovement < 1) tickpermovement = 1; // Ensure at least 1 tick

    properties.dX = dX / tickpermovement;
    properties.dY = dY / tickpermovement;

    glideMax = tickpermovement;
    glideT = 0;
    qDebug() << "Distance =" << distance << ", tickpermovement =" << tickpermovement;

    t = new QTimer();
    t->setInterval(tickInterval);

    connect(t, &QTimer::timeout, this, &enemies::glideTick);
    t->start();
}

void enemies::start()
{
    ++tick;
    QGraphicsOpacityEffect *opacity = new QGraphicsOpacityEffect;
    double qr = (tick<100)?(100-tick)/100:(tick<200)?(tick-100)/100:-1;
    opacity->setOpacity(qr);
    outline->setGraphicsEffect(opacity);

    if(qr<0)
    {
        tick = 0;
        timer->stop();
        timer->deleteLater();
        opacity->setOpacity(1);
        outline->setGraphicsEffect(opacity);
        spawned = true;
    }

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
        QString color = properties.health >= properties.maxHealth * 0.5 ? "green" :
                        properties.health >= properties.maxHealth * 0.25 ? "yellow" : "red";
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
