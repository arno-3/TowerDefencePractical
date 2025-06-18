#ifndef ENEMIES_H
#define ENEMIES_H

#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QTimer>
#include <QProgressBar>
#include <QGraphicsOpacityEffect>
//#include <threadtimer.h>


struct enemy_properties
{
    int health = 100;
    int type = 0;
    double speed = 1000;//time(ms) per block
    int damage = 0;
    double dX, dY = 0;
    QPoint pos = QPoint(0,0);
    int gridPos[2] = {0,0};
    int goldReward;
};

class enemies : public QWidget
{
    Q_OBJECT
public:
    explicit enemies(QWidget *parent = nullptr, int enemyType=0,QPoint *spawnPos = new QPoint(0,0), int x=0,int y=0 );
    void moveTo(QPoint nexPosition, int x, int y);// Actual coordinates of enemy with respect to the window
    void moveNext();
    //void setEnemy(enemy_properties ep);
    QPoint getPos();
    void glow();
    bool isMoving();
    bool crashed();
    bool hasSpawned();
    enemy_properties properties;
    void updateHealthBar();
    void spawnStart(bool);
    void Opacity(QGraphicsOpacityEffect*);


signals:


private:
    QTimer *timer, *t, *healthTimer;
    QLabel *outline;
    QProgressBar *hBar;
//    ThreadTimer *spwnThread, *healthThread, *glowThread;

    double tick;
    int glowCount =0;
    void mousePressEvent(QMouseEvent*);
    QPoint currentHop = QPoint(0,0);
    QPoint nextHop;
    void glide(int x, int y);
    bool moving = false;
    int glideT, glideMax = 0;
    int tX, tY = 0;

    bool spawned = false;
    bool bCrashed = false;


private slots:
    void glowTick();
    void glideTick();
    void start();
    void spawn();
    void opacitySlot(QGraphicsOpacityEffect* op);
};

#endif // ENEMIES_H
