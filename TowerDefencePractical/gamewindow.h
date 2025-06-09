#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QLabel>
#include <QVector>
#include "towerbtn.h"
#include "gridblocks.h"

class gamewindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit gamewindow(QWidget *parent = nullptr,QMainWindow *menu = nullptr);


signals:


private:
    QLabel *grass;
    QLabel *base;

    QMainWindow Menu;

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

    QVector<TowerBtn*> towers; // Store placed towers

    gridBlocks *gridVector[10][10];

    int gold;
    QLabel *Gold;
    const int towerCosts[4] = {20, 30, 25, 15}; // Costs for tower types 0-3

private slots:
    void createMap();
    void convertIsometric();
    void onExit(QMainWindow*);
    void onTowerButtonClicked(int towerType);
    void onGridBlockClicked(int row, int col);

};

#endif // GAMEWINDOW_H
