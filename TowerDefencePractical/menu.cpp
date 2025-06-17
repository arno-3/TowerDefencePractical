#include "menu.h"
#include <QSoundEffect>
#include <QTimer>
#include <QObject>
#include <gamewindow.h>
#include <QMediaPlayer>
#include <QMediaPlaylist>

menu::menu(QWidget *parent) : QMainWindow(parent)
{

    setFixedSize(1200,800);
    setStyleSheet("background-color: #A3E3FF;");

    //Menu ITEMS

//    menulbl = new QLabel(this);
//    menulbl->setText("START");

//    menulbl->setStyleSheet("QLabel { font-size: 30px; color: white; border:1px solid white; background-color: #888888;}");
//    menulbl->move(width()/2-menulbl->width()/2,96);

//    onlinelbl = new QLabel(this);
//    onlinelbl->setText("ONLINE");
//    onlinelbl->setStyleSheet("QLabel { font-size: 30px; color: white;}");
//    onlinelbl->move(width()/2-onlinelbl->width()/2,236);

//    exitlbl = new QLabel(this);
//    exitlbl->setText("EXIT");
//    exitlbl->setStyleSheet("QLabel { font-size: 30px; color: white;}");
//    exitlbl->move(width()/2-exitlbl->width()/2,396);

//    homerlbl = new QLabel(this);
//    homerlbl->setText("HOMER");
//    homerlbl->setStyleSheet("color: #7387e4;");
//    homerlbl->setFont(QFont("Comic Sans MS", 15));
//    homerlbl->move(width()/2-homerlbl->width()/2,556);


    start = new MenuBtn(this,"START",0);
    start->move(width()/2-start->width()/2,75);
    connect(start, &MenuBtn::clicked, this, &menu::onStartClicked);

    online = new MenuBtn(this, "ONLINE",0);
    online->move(width()/2-online->width()/2,215);
    connect(online, &MenuBtn::clicked, this, &menu::onOnlineClicked);

    exit = new MenuBtn(this,"EXIT",0);
    exit->move(width()/2-exit->width()/2,375);
    connect(exit, &MenuBtn::clicked, this, &menu::onExitClicked);

    homer = new MenuBtn(this,"HOMER",1);
    homer->move(width()/2-homer->width()/2,535);
    connect(homer, &MenuBtn::clicked, this, &menu::onHomerClicked);

    menuEffect = new QMediaPlayer(this);
    QMediaPlaylist *playlist = new QMediaPlaylist(this);

    // Add media to playlist
    playlist->addMedia(QUrl("qrc:/MusicMenu.mp3")); // Ensure correct path
    playlist->setPlaybackMode(QMediaPlaylist::Loop); // Loop the music

    // Set playlist and volume
    menuEffect->setPlaylist(playlist);
    menuEffect->setVolume(50); // 0 to 100
    menuEffect->play();



}


void menu::onStartClicked(bool state)
{
    MenuBtn *m = (MenuBtn*)QObject::sender();
    if(!state)
    {
        //If this button is clicked:
        //Navigate to the game window

        gamewindow *g = new gamewindow(0,this);
        g->show();

        menuEffect->stop();
        startEffect = new QMediaPlayer(this);
        QMediaPlaylist *playlist = new QMediaPlaylist(this);

        // Add media to playlist
        playlist->addMedia(QUrl("qrc:/BattleMusic.mp3")); // Ensure correct path
        playlist->setPlaybackMode(QMediaPlaylist::Loop); // Loop the music

        // Set playlist and volume
        startEffect->setPlaylist(playlist);
        startEffect->setVolume(50); // 0 to 100
        startEffect->play();

        //this->setWindowState(Qt::WindowMinimized);
    }
     m->setState(false);
}

void menu::onExitClicked(bool state)
{
    //Todo:
    //close window (DONE)
    //quit application (DONE) ~ implemented with closing the window

    MenuBtn *m = (MenuBtn*)QObject::sender();
    if(!state)
    {
        //quit app
        this->close();
    }
    m->setState(false);
}

void menu::onOnlineClicked(bool state)
{
    MenuBtn *m = (MenuBtn*)QObject::sender();

    if(!state)
    {
        //navigate to online game settings
    }
    m->setState(false);
}



void menu::onHomerClicked(bool state)
{
    //Todo:
    //sound (DONE)
    //background (DONE)
    //backrgound-hide (DONE)
    // reset state (DONE)

    MenuBtn *m = (MenuBtn*)QObject::sender();
    menuEffect->stop();

    if(!state)
    {
        if(homieCount == 0)
        {

        start->hide();
        online->hide();
        exit->hide();
        homer->hide();

        //Homer Easter Egg
        QTimer *timer = new QTimer(this);
        connect(timer,&QTimer::timeout,this,&menu::onTimerTick);
        timer->start(500);

        effect = new QSoundEffect(this);
        effect->setSource(QUrl("qrc:/HomerChokeSound.wav"));
        effect->setVolume(0.5); // 0.0 to 1.0 in percentages
        effect->play();

        int w,h;

        QPixmap p(":/homer2.png");
        w = p.width();
        h =p.height();

        homie = new QLabel(this);
        homie->setFixedSize(w,h);
        homie->setPixmap(p);
        homie->move(width()/8,height()/4);
        homie->show();
        }
    }
    m->setState(false);
}

void menu::onTimerTick()
{
    ++homieCount;
    if(homieCount>=32 && !homie->isHidden())
    {
        homie->hide();
        effect->stop();
        homieCount = 0;
        QTimer *t = (QTimer*)QObject::sender();
        t->deleteLater();
        start->show();
        online->show();
        exit->show();
        homer->show();
        menuEffect->play();
    }
}
