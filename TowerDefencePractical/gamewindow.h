#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QLabel>
#include <QVector>
#include "towerbtn.h"
#include "gridblocks.h"
#include <enemyhandler.h>
#include <QProgressBar>
#include <QTimer>
#include <QPushButton>


class gamewindow : public QMainWindow
{
    Q_OBJECT

    struct bBase
    {
        int health = 100;
        int gold = 100;
    };

public:
    explicit gamewindow(QWidget *parent = nullptr,QMainWindow *menu = nullptr);
    void addGold(int amount);


private:
    QLabel *grass;
    QLabel *base;

    QTimer *gameTimer;

    QMainWindow *Menu;
    EnemyHandler *enemyH;

    //Tower items
    TowerBtn *BigT; //big expensive tower
    TowerBtn *RegT; //regular tower
    TowerBtn *Wall; //Wall
    TowerBtn *FastT; //shoot fast tower
    TowerBtn *MineT; //landmine


    //Tower or shop labels
    QLabel *bigT;  //big expensive tower
    QLabel *regT;  //regular tower
    QLabel *wall;  //Wall
    QLabel *fastT; //shoot fast tower
    QLabel *mine; // landmine
    int selectedTowerType;
    TowerBtn* selectedTower;

    QVector<TowerBtn*> towers; // Store placed towers

    gridBlocks *gridVector[10][10];
    QPushButton *btnGrid[10][10];

    int gold;
    bBase base_specs;
    QLabel *Gold;
    QProgressBar *pHealth;
    QLabel *bHealth;
    int towerCosts[4];// = {20, 30, 25, 15}; // Costs for tower types 0-3
    QLabel *Rprice, *Fprice, *Bprice, *Mprice;

    QPushButton *home, *replay;

    void GameOver();

signals:
    void gameover();
    void homingSignal();
    void redoSignal();





private slots:
    void createMap();
    void convertIsometric();
    void onExit(QMainWindow*);
    void onTowerButtonClicked(int towerType);
    void onGridBlockClicked(int row, int col);
    void onCrash(int damage);
    void updateGame();
    void backHome();
    void retry();
    void BtnClicked();

};

#endif // GAMEWINDOW_H
