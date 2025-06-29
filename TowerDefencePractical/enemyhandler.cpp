#include "enemyhandler.h"
#include <enemies.h>
#include <QDebug>
#include <QRandomGenerator64>
#include <QSoundEffect>
#include <QGraphicsBlurEffect>

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
            mapChart[i][j] = 0;//nothing there
        }
    }
    setPaths();
    wave = 0;
    waving = new QLabel(W);
    waving->setText("Wave: "+ QString::number(wave));
    waving->setFixedSize(200, 50);
    waving->setFont(QFont("Comic Sans",15,2,false));
    waving->move(1000,100);
    waving->setStyleSheet("color: gold; background:transparent;");
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
    timer->start();
    createWaves();
}


void EnemyHandler::createWaves()
{
    QGraphicsBlurEffect* blur = new QGraphicsBlurEffect(W);
    blur->setBlurHints(QGraphicsBlurEffect::PerformanceHint);
    W->setGraphicsEffect(blur);
    QTimer::singleShot(1000,this,[this]()
    {
        W->setGraphicsEffect(nullptr);
    });

    int max_wave_size = wave*QRandomGenerator64::global()->bounded(3,6);
    if(max_wave_size<3)
        max_wave_size = wave*QRandomGenerator64::global()->bounded(3,8);

    int numSmalls = QRandomGenerator64::global()->bounded(0,2*wave)-1;
    int numBiggies, numSpaceships = 0;
    waving->setText("Wave: "+ QString::number(wave));
    ennemies.clear();
    placedCells.clear();

    if((max_wave_size-numSmalls)>0)
        numBiggies = QRandomGenerator64::global()->bounded(0,max_wave_size-numSmalls);

    if((max_wave_size-numSmalls-numBiggies)>0)
        numSpaceships = (wave<=3)?(0):(QRandomGenerator64::global()->bounded(0,max_wave_size-numSmalls-numBiggies));

//    placedCells->resize(numBiggies+numSmalls+numSpaceships);


    for(int i = 0;i<numSmalls;++i)
    {
        int R_or_C = QRandomGenerator64::global()->bounded(1,10)%2;

        QPoint *point = new QPoint(0,0);
        do
        {
        if(R_or_C)
            point->setX(QRandomGenerator64::global()->bounded(1,8));
        else
            point->setY(QRandomGenerator64::global()->bounded(1,8));
        }while(placedCells.count(point)>1);

        enemies *e = new enemies(W,0,point,getX(*point),getY(*point), wave);
        e->show();
        e->raise();
        ennemies.append(e);
        placedCells.append(point);
//        point->~QPoint();
//        QThread::msleep(25);
        QTimer::singleShot(50,this,[](){});
    }
    if(numBiggies>0)
    {
        for(int i = 0;i<numBiggies;++i)
        {
            int R_or_C = QRandomGenerator64::global()->bounded(1,10)%2;
            QPoint *point = new QPoint(0,0);
            do
            {
            if(R_or_C)
                point->setX(QRandomGenerator64::global()->bounded(1,8));
            else
                point->setY(QRandomGenerator64::global()->bounded(1,8));
            }while(placedCells.count(point)>1);

            enemies *e = new enemies(W,1,point,getX(*point),getY(*point), wave);
            e->show();
            e->raise();
            ennemies.append(e);
            placedCells.append(point);
//            point->~QPoint();
//            QThread::msleep(75);
            QTimer::singleShot(100,this,[](){});
        }
    }

    if(numSpaceships>0)
    {
        for(int i = 0;i<numSpaceships;++i)
        {
            int R_or_C = QRandomGenerator64::global()->bounded(1,10)%2;
            QPoint *point = new QPoint(0,0);
            do
            {
            if(R_or_C)
                point->setX(QRandomGenerator64::global()->bounded(1,8));
            else
                point->setY(QRandomGenerator64::global()->bounded(1,8));
            }while(placedCells.count(point)>1);

            enemies *e = new enemies(W,2,point,getX(*point),getY(*point), wave);
            e->show();
            e->raise();
            ennemies.append(e);
            placedCells.append(point);
//            point->~QPoint();
//            QThread::msleep(100);
            QTimer::singleShot(500,this,[]{});
        }
    }
    waveStarted = true;
}

int EnemyHandler::getX(QPoint p)
{
    return (int)(grid[p.x()][p.y()]->x()+10);
}

int EnemyHandler::getY(QPoint p)
{
    return (int)(grid[p.x()][p.y()]->y()-20);
}

void EnemyHandler::runGame()
{
    ++tick;
    int enCount = ennemies.size();

    if(ennemies.size()>0 && waveStarted)
    {
    for(enemies* e:ennemies)
    {
        if(!e->isMoving() && !e->crashed() && e->hasSpawned())
        {
            QPoint pos = e->getPos();

            mapChart[pos.x()][pos.y()] = 0;
            QPoint next = *flowChart[pos.x()][pos.y()];

            if(mapChart[next.x()][next.y()] == 1)
                QTimer::singleShot(1000,e,[]{});
            mapChart[next.x()][next.y()] = 1;

            e->moveTo(next, getX(next),getY(next));
            pos.~QPoint();
            next.~QPoint();
            qDebug()<<"Tick: "<<tick<<endl;
            e->raise();

            if(((pos == QPoint(9,8))||(pos == QPoint(8,9))))
            {
//                e->glow();
                qDebug() << "CRASH and Burn!!!" << endl;


                QSoundEffect *effect = new QSoundEffect(this);
                effect->setSource(QUrl("qrc:/Pain.wav"));
                effect->setVolume(0.5); // 0.0 to 1.0 in percentages
                effect->play();


               // e->setFixedSize(150,150);
                emit crash(e->properties.damage);

                ennemies.removeOne(e);
                e->deleteLater();

//                ennemies.resize(enCount-1);
                QThread::msleep(5);
            }
        }

    }
    }
    else if(ennemies.size()<=0)
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
    int value = mapChart[r][c];
    // Generic update (done)
    // Is bottom-right? || Has bottom-right? (done)
    // Top of Hull? || Left of Hull? || Bottom of Hull? (not done)
    // Bottom row? || Bottom column? (not done)

    bool bottom_row = (r==9)?true:false;
    bool bottom_col = (c==9)?true:false;

    bool isBottomRight = false;
    bool hasBottomRight = false;
    bool hasTopTop = false;
    bool isTopTop = false;

    // Generic update, see that r>0 && c>0
    if(value!=-2)
    {
    if(r>0 && c>0)
    {
        //Top cell
        flowChart[r][c-1]->setX(r+1);
        flowChart[r][c-1]->setY(c-1);

        //Right cell
        flowChart[r-1][c]->setX(r-1);
        flowChart[r-1][c]->setY(c+1);
    }

    if(mapChart[r+1][c-1] == -1)// Is Bottom-Right
    {
        isBottomRight = true;

        if(!bottom_col)
        {
            flowChart[r][c-2]->setX(r+1); flowChart[r][c-2]->setY(c-2);// Top-Top remapping
            flowChart[r-1][c-1]->setX(r-1); flowChart[r-1][c-1]->setY(c+1);// Top-Right remapping
            flowChart[r][c-1]->setX(r); flowChart[r][c-1]->setY(c-2);// Top remapping (safety)
            flowChart[r-1][c]->setX(r); flowChart[r-1][c]->setY(c+1);//Right remapping
        }
        else
        {
            flowChart[r][c-2]->setX(r+1); flowChart[r][c-2]->setY(c-2);// Top-Top remapping
            flowChart[r-1][c-1]->setX(r); flowChart[r-1][c-1]->setY(c-1);// Top-Right remapping
            flowChart[r][c-1]->setX(r); flowChart[r][c-1]->setY(c-2);// Top remapping (safety)
            flowChart[r-1][c]->setX(r); flowChart[r-1][c]->setY(c-1);//Right remapping
        }
    }
    else if(mapChart[r-1][c+1] == -1)//Has Bottom-Right
    {
        hasBottomRight = true;

        if(!bottom_row)
        {
            flowChart[r-1][c-1]->setX(r); flowChart[r-1][c-1]->setY(c-1);// Top-Top remapping (r-1)(c-1)
            flowChart[r-2][c]->setX(r-2); flowChart[r-2][c]->setY(c+1);// Top-Right remapping
            flowChart[r-1][c]->setX(r); flowChart[r-1][c]->setY(c-1);// Top remapping (safety)
//            flowChart[r-1][c]->setX(r); flowChart[r-1][c]->setY(c+1);//Right remapping
        }
        else
        {
            flowChart[r][c-1]->setX(r-1); flowChart[r][c-1]->setY(c-1);// Top-Top remapping (r-1)(c-1)
            flowChart[r-1][c-1]->setX(r-1); flowChart[r-1][c-1]->setY(c);// Top-Right remapping
            flowChart[r-1][c]->setX(r-2); flowChart[r-1][c]->setY(c);// Top remapping (safety)
            flowChart[r-2][c]->setX(r-2); flowChart[r-2][c]->setY(c+1);//This-Top remapping
        }
    }

    if((mapChart[r+1][c+1]+mapChart[r][c+2]) == -2)// Is Top of Hull
    {
        flowChart[r][c+1]->setX(r-1); flowChart[r][c+1]->setY(c+1); // Middle Cell || Hull
        flowChart[r-1][c+1]->setX(r-1); flowChart[r-1][c+1]->setY(c+2);//Next to Hull
    }
    else if((mapChart[r-1][c-1]+mapChart[r-1][c+1]) == -2)//Is Left of Hull
    {
        flowChart[r-1][c]->setX(r-2); flowChart[r-1][c]->setY(c); // Middle Cell || Hull
        flowChart[r-2][c]->setX(r-2); flowChart[r-2][c]->setY(c+1);//Next to Hull
    }
    else if((mapChart[r+1][c-1]+mapChart[r][c-2]) == -2) //Is Bottom of Hull
    {
        flowChart[r][c-1]->setX(r-1); flowChart[r][c-1]->setY(c-1); // Middle Cell || Hull
        flowChart[r-1][c-1]->setX(r-1); flowChart[r-1][c-1]->setY(c);//Next to Hull
    }

}
    qDebug()<<"PLACEMENT!!!"<<endl;
}

void EnemyHandler::setPaths()
{
    for(int r=0;r<=9;++r)
    {
        for(int c=0;c<=9;++c)
        {

            if((9-c)>=(9-r))
            {
                flowChart[r][c] = new QPoint(r,c+1);
            }
            else if((9-c)<=(9-r))
            {
                flowChart[r][c] = new QPoint(r+1,c);
            }
            else if(c==9 && r<9)
            {
                flowChart[r][c] = new QPoint(r+1,c);
            }
            else if(r==9 && c<9)
            {
                flowChart[r][c] = new QPoint(r,c+1);
            }
        }
    }
//    connect(,&gamewindow::placedBlock,this,&EnemyHandler::updatePaths);
}


void EnemyHandler::setCell(int val, int row, int col)
{
    mapChart[row][col] = val;
}

void EnemyHandler::damageEnemy(enemies* enemy, int damage) {
    enemy->properties.health -= damage;
    enemy->updateHealthBar();
    if(enemy->properties.type == 2 || enemy->properties.type == 1)
        enemy->properties.speed *=0.55;
    if (enemy->properties.health <= 0) {
        ennemies.removeOne(enemy);
        enemy->deleteLater();
    }
}

void EnemyHandler::endGame()
{
    for(enemies* en:ennemies)
    {
        en->hide();
        ennemies.removeOne(en);
        en->deleteLater();
    }
    ennemies.clear();
    timer->stop();
    timer->deleteLater();

}
