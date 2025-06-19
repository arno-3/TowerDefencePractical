#ifndef ENEMYHANDLER_H
#define ENEMYHANDLER_H

#include <QObject>
#include "gridblocks.h"
#include <enemies.h>
#include <QThread>
#include <QMainWindow>
#include <QWidget>
#include <QTimer>
#include <QLabel>

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
    void setCell(int val, int row, int col);

    void createWaves();
    int getX(QPoint p);
    int getY(QPoint p);
    // New method to access enemies
    const QVector<enemies*>& getEnemies() const { return ennemies; }
    // New method to damage enemies
    void damageEnemy(enemies* enemy, int damage);


signals:
    void crash(int damage);

private slots:
    void runGame();

public slots:
    void endGame();



private:

    QVector<enemies*> ennemies;
    QVector<QPoint*> placedCells;
    QTimer *timer;
    QLabel *waving;

    QWidget *W;

    double tick=0;
    int wave = 0;

    QPoint *flowChart[10][10];//contains the coordinates in grid space
    int mapChart[10][10];

    bool waveStarted = false;
    bool notDead = true;
};

#endif // ENEMYHANDLER_H
