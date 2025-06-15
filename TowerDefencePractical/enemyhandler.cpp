#include "enemyhandler.h"
#include <enemies.h>
#include <QDebug>
#include <QRandomGenerator64>

EnemyHandler::EnemyHandler(QObject *parent, QMainWindow *p) : QObject(parent)
{
    //this->W = p;
    this->W = p;

    for(int i=0;i<10;++i)
    {
        for(int j=0;j<10;++j)
        {
            grid[i][j] = new QPoint(i,j);
            flowChart[i][j] = new QPoint(i,j);
        }
    }
    setPaths();

}

void EnemyHandler::setGrid(int x, int y, int i, int j)
{
    grid[i][j]->setX(x);
    grid[i][j]->setY(y);
}


void EnemyHandler::run()
{
    //Run Wave Algorithm
    /* After completeion of one wave, clear vector array of all enemies
     * determine enemies that spawn with "algorithm"
     * populate vector array
     * randomise spawn pattern
     * let each enemy spawned retrieve its path to the base
     */
    timer = new QTimer();
    connect(timer,&QTimer::timeout,this,&EnemyHandler::runGame);
    timer->setInterval(100);
    ++wave;

//    enemies *e = new enemies(W,0, new QPoint(0,0),getX(0,0),getY(0,0));
////    enemies *en = new enemies(W,1,new QPoint(1,0),getX(1,0),getY(1,0));
////    enemies *enn = new enemies(W,2, new QPoint(0,5),getX(0,5),getY(0,5));
//////    en->mo
//////    enn->move(getX(0,0),getY(0,0));
//////    en->move(getX(3,4),getY(3,4));
//////    en->raise();
//////    en->show();
//    ennemies.append(e);
//    ennemies.append(en);
//    ennemies.append(enn);
//    e->raise();
//    en->raise();
//    enn->raise();
    timer->start();
    createWaves();
}


void EnemyHandler::createWaves()
{
    int max_wave_size = wave*QRandomGenerator64::global()->bounded(1,5);
    int numSmalls = QRandomGenerator64::global()->bounded(1,2*wave);
    int numBiggies, numSpaceships = 0;

    if((max_wave_size-numSmalls)>0)
        numBiggies = QRandomGenerator64::global()->bounded(1,max_wave_size-numSmalls);
//    if((max_wave_size-numSmalls-numBiggies)>0)
//        numSpaceships = (wave>=3)?(0):(QRandomGenerator64::global()->bounded(1,max_wave_size-numSmalls-numBiggies));

    for(int i = 0;i<numSmalls;++i)
    {
        int R_or_C = QRandomGenerator64::global()->bounded(1,10)%2;
        QPoint *point = new QPoint(0,0);
        if(R_or_C)
            point->setX(QRandomGenerator64::global()->bounded(1,8));
        else
            point->setY(QRandomGenerator64::global()->bounded(1,8));
        enemies *e = new enemies(W,0,point,getX(point->x(),point->y()),getY(point->x(),point->y()));
        ennemies.append(e);
        point->~QPoint();
    }
    if(numBiggies>0)
    {
        for(int i = 0;i<numBiggies;++i)
    {
        int R_or_C = QRandomGenerator64::global()->bounded(1,10)%2;
        QPoint *point = new QPoint(0,0);
        if(R_or_C)
            point->setX(QRandomGenerator64::global()->bounded(1,8));
        else
            point->setY(QRandomGenerator64::global()->bounded(1,8));
        enemies *e = new enemies(W,1,point,getX(point->x(),point->y()),getY(point->x(),point->y()));
        ennemies.append(e);
        point->~QPoint();
    }
    }
    waveStarted = true;
//    for(int i = 0;i<numSpaceships;++i)
//    {
//        int R_or_C = QRandomGenerator64::global()->bounded(1,10)%2;
//        QPoint *point = new QPoint(0,0);
//        if(R_or_C)
//            point->setX(QRandomGenerator64::global()->bounded(1,8));
//        else
//            point->setY(QRandomGenerator64::global()->bounded(1,8));
//        enemies *e = new enemies(W,2,point,getX(point->x(),point->y()),getY(point->x(),point->y()));
//        ennemies.append(e);
//        point->~QPoint();
//    }
}

int EnemyHandler::getX(int x, int y)
{
    return (int)(grid[x][y]->x()+10);
}

int EnemyHandler::getY(int x, int y)
{
    return (int)(grid[x][y]->y()-20);
}

void EnemyHandler::runGame()
{
    ++tick;
    int enCount = ennemies.size();

    if(ennemies.size()>0 && waveStarted)
    {
    for(int e=0;e<ennemies.size();++e)
    {
        if(!ennemies[e]->isMoving() && !ennemies[e]->crashed() && ennemies[e]->hasSpawned())
        {
            QPoint pos = ennemies[e]->getPos();
            QPoint next = *flowChart[pos.x()][pos.y()];
            ennemies[e]->moveTo(next, getX(next.x(),next.y()),getY(next.x(),next.y()));
            pos.~QPoint();
            next.~QPoint();
            qDebug()<<"Tick: "<<tick<<endl;
            ennemies[e]->raise();

            if(pos.x() == 9 ||pos.y()== 9)
            {
//                ennemies[e]->glow();
                qDebug() << "CRASH and Burn!!!" << endl;
                ennemies[e]->setFixedSize(150,150);
                emit crash(ennemies[e]->properties.damage);
                ennemies[e]->deleteLater();
                ennemies.removeAt(e);

            }
        }

    }
    }
    else if(ennemies.size()==0)
    {
        waveStarted = false;
        qDebug()<<"####  NEW WAVE ####"<<endl;
        ++wave;
        createWaves();
        tick = 0;

    }

}

void EnemyHandler::updatePaths(int r, int c)
{
    if(flowChart[r-1][c]->x() == r && flowChart[r-1][c]->y() == c)
    {
        if(r!=9)
        {
            flowChart[r-1][c]->setX(r-1);
            flowChart[r-1][c]->setY(c+1);
        }
        else if(r==9)
        {
            flowChart[r-1][c]->setX(r-1);
            flowChart[r-1][c]->setY(c+1);
        }
    }
    //L++;
    if(flowChart[r][c-1]->x() == r && flowChart[r][c-1]->y() == c)
    {
        if(c!=9)
        {
            flowChart[r][c-1]->setY(c-1);
            flowChart[r][c-1]->setX(r+1);
        }
        else if(c==9)
        {
            flowChart[r][c-1]->setY(c-1);
            flowChart[r][c-1]->setX(r-1);
        }
    }
    qDebug()<<"PLACEMENT!!!"<<endl;
}

void EnemyHandler::setPaths()
{
    for(int r=0;r<9;++r)
    {
        for(int c=0;c<9;++c)
        {
            if((9-c)>=(9-r))
            {
                flowChart[r][c] = new QPoint(r,c+1);
            }
            else
            {
                flowChart[r][c] = new QPoint(r+1,c);
            }
        }
    }
//    connect(,&gamewindow::placedBlock,this,&EnemyHandler::updatePaths);
}
