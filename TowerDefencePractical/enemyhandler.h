#ifndef ENEMYHANDLER_H
#define ENEMYHANDLER_H

#include <QObject>
#include "gridblocks.h"
#include <enemies.h>
#include <QThread>
#include <QMainWindow>
#include <QWidget>
#include <QTimer>

class EnemyHandler : public QObject
{
    Q_OBJECT
    QThread thread;
public:
    explicit EnemyHandler(QObject *pareQMainWindownt = nullptr, QMainWindow *p = nullptr);

    void setPaths();
   // void updatePaths();
    /*
     * Note that it is only needed to compute the shortest paths from the outer edges
     * as they are composed of the path towards the base and blocks in between
    */
    QPoint *grid[10][10];// contains the coordinates in windowsapce
    void setGrid(int x, int y, int i, int j);
    void run();
    void updatePaths(int r, int c);

signals:
    void crash(int damage);

private slots:
    void runGame();



private:

    QVector<enemies*> ennemies;
    QTimer *timer;

    QWidget *W;

    double tick=0;
    int wave = 0;
    int getX(int x, int y);
    int getY(int x, int y);
    QPoint *flowChart[10][10];//contains the coordinates in grid space

    void createWaves();
    bool waveStarted = false;
};

#endif // ENEMYHANDLER_H
