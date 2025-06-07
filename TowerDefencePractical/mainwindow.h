#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <menubtn.h>
#include <QLabel>
#include <towerbtn.h>
#include <gridblocks.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void clicked(bool);

private:
    //Menu items
    MenuBtn *start;
    MenuBtn *online;
    MenuBtn *exit;
    MenuBtn *homer;
    //Menu labels
    QLabel *menulbl;
    QLabel *onlinelbl;
    QLabel *exitlbl;
    QLabel *homerlbl;
    QLabel *homie;

    QLabel *grass;
    QLabel *base;

    //Tower items
    TowerBtn *bTow; //big expensive tower
    TowerBtn *rTow; //regular tower
    TowerBtn *wallT; //Wall
    TowerBtn *fTow; //shoot fast tower
    TowerBtn *mTow; //mine


    //Tower or shop labels
    QLabel *bigT;  //big expensive tower
    QLabel *regT;  //regular tower
    QLabel *wall;  //Wall
    QLabel *fastT; //shoot fast tower
    QLabel *mine;

    gridBlocks *gridVector[10][10];


private slots:
    //Slots to activate when button pressed
    void onStartClicked(bool);
    void onOnlineClicked(bool);
    void onExitClicked(bool);
    void onHomerClicked(bool);
};
#endif // MAINWINDOW_H
