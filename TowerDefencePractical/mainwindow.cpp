#include "mainwindow.h"
#include <QFont>
#include <QApplication>
#include <QPixmap>
#include <QSoundEffect>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setFixedSize(1200, 800);
    setStyleSheet("background-color: black;");

    ///Menu items

    //Menu labels
    //label->setStyleSheet("QLabel { font-size: 20px; }");


    menulbl = new QLabel(this);
    menulbl->setText("START");
    menulbl->setStyleSheet("QLabel { font-size: 30px; color: white; }");
    menulbl->move(width()/2-menulbl->width()/2,96);

    onlinelbl = new QLabel(this);
    onlinelbl->setText("ONLINE");
    onlinelbl->setStyleSheet("QLabel { font-size: 30px; color: white; }");
    onlinelbl->move(width()/2-onlinelbl->width()/2,236);

    exitlbl = new QLabel(this);
    exitlbl->setText("EXIT");
    exitlbl->setStyleSheet("QLabel { font-size: 30px; color: white; }");
    exitlbl->move(width()/2-exitlbl->width()/2,396);

    //label->setFont(QFont("Arial", 18));

    homerlbl = new QLabel(this);
    homerlbl->setText("HOMER");
    homerlbl->setStyleSheet("color: blue;");
    homerlbl->setFont(QFont("Comic Sans MS", 15));
    homerlbl->move(width()/2-homerlbl->width()/2,556);

    //connect(label, &ClickableLabel::clicked, this, &MainWindow::onLabelClicked)
    //Create all labels for the menu items
    start = new MenuBtn(this);
    start->move(width()/2-start->width()/2,75);
    connect(start, &MenuBtn::clicked, this, &MainWindow::onStartClicked);

    online = new MenuBtn(this);
    online->move(width()/2-online->width()/2,215);
    connect(online, &MenuBtn::clicked, this, &MainWindow::onOnlineClicked);

    exit = new MenuBtn(this);
    exit->move(width()/2-exit->width()/2,375);
    connect(exit, &MenuBtn::clicked, this, &MainWindow::onExitClicked);

    homer = new MenuBtn(this);
    homer->move(width()/2-homer->width()/2,535);
    connect(homer, &MenuBtn::clicked, this, &MainWindow::onHomerClicked);

}

MainWindow::~MainWindow()
{
}

void MainWindow::onStartClicked(bool state)
{

    if (!state)
    {
        //hide all the menu buttons and labels
        start->hide();
        menulbl->hide();
        online->hide();
        onlinelbl->hide();
        exit->hide();
        exitlbl->hide();
        homer->hide();
        homerlbl->hide();

        //put the picture or label above for clicking purposes
        bigT = new QLabel(this);
        bigT->move(50,50);
        bigT->setText("Big");
        bigT->setStyleSheet("QLabel { font-size: 15px; color: white; }");
        bigT->show();

        regT = new QLabel(this);
        regT->move(150,50);
        regT->setText("Reg");
        regT->setStyleSheet("QLabel { font-size: 15px; color: white; }");
        regT->show();

        wall = new QLabel(this);
        wall->move(50,150);
        wall->setText("Wall");
        wall->setStyleSheet("QLabel { font-size: 15px; color: white; }");
        wall->show();

        fastT = new QLabel(this);
        fastT->move(150,150);
        fastT->setText("Fast");
        fastT->setStyleSheet("QLabel { font-size: 15px; color: white; }");
        fastT->show();

        //Spawn tower label blocks
        bTow = new TowerBtn(this);
        bTow->show();

        rTow = new TowerBtn(this);
        rTow->move(100,0);
        rTow->show();

        wallT = new TowerBtn(this);
        wallT->move(0,100);
        wallT->show();

        fTow = new TowerBtn(this);
        fTow->move(100,100);
        fTow->show();
    }

}

void MainWindow::onOnlineClicked(bool state)
{
    if (!state)
    {
        //hide all the menu buttons and labels
        start->hide();
        menulbl->hide();
        online->hide();
        onlinelbl->hide();
        exit->hide();
        exitlbl->hide();
        homer->hide();
        homerlbl->hide();


    }

}

void MainWindow::onExitClicked(bool state)
{
    if (!state)
    {
        QApplication::quit();
    }
}

void MainWindow::onHomerClicked(bool state)
{
    if (!state)
    {

        //hide all the menu buttons and labels
        start->hide();
        menulbl->hide();
        online->hide();
        onlinelbl->hide();
        exit->hide();
        exitlbl->hide();
        homer->hide();
        homerlbl->hide();

        QPixmap p(":/homer2.png");
        homie = new QLabel(this);
        homie->setFixedSize(p.width(), p.height());
        homie->move(width()/8, height()/4);
        homie->setPixmap(p);
        homie->show();

        // In your widget or class
        QSoundEffect *effect = new QSoundEffect(this);
        effect->setSource(QUrl("qrc:/HomerChokeSound.wav"));
        effect->setVolume(0.5); // 0.0 to 1.0
        effect->play();
    }
}
