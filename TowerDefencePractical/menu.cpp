#include "menu.h"
#include <QSoundEffect>
#include <QTimer>
#include <QObject>
//#include <gamewindow.h>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QGraphicsBlurEffect>

menu::menu(QWidget *parent) : QMainWindow(parent)
{

    setFixedSize(1200,800);
    setStyleSheet("background-color: #A3E3FF;");

    //Menu ITEMS

    introLabel = new QLabel(this);
    intro = new QMovie(":/SimpsonsIntro.gif");
    intro->scaledSize().scale(width()*2,height()*2,Qt::KeepAspectRatio);
    intro->setScaledSize(this->size()/1.001125);
    introLabel->setFixedSize(this->size());
    introLabel->setMovie(intro);
    introLabel->move(0,0);
    introLabel->show();
    introLabel->setAlignment(Qt::AlignCenter);
    intro->jumpToNextFrame();


    start = new MenuBtn(this,"START",0);
    start->move(width()/2 -2*start->width(),height()-4*start->height());
    connect(start, &MenuBtn::clicked, this, &menu::onStartClicked);

    online = new MenuBtn(this, "ONLINE",0);
    online->move(width()/2-2*online->width(),height()-2*start->height());
    connect(online, &MenuBtn::clicked, this, &menu::onOnlineClicked);

    exit = new MenuBtn(this,"EXIT",0);
    exit->move(width()/2+exit->width(),height()-4*exit->height());
    connect(exit, &MenuBtn::clicked, this, &menu::onExitClicked);

    homer = new MenuBtn(this,"HOMER",1);
    homer->move(width()/2+homer->width(),height()-2*homer->height());
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



//    intro->start();

//    QTimer::singleShot(1200,this,[]{});



}


void menu::onStartClicked(bool state)
{
    MenuBtn *m = (MenuBtn*)QObject::sender();
    if(!state)
    {
        //If this button is clicked:
        //Navigate to the game window
        start->hide();
        online->hide();
        exit->hide();
        homer->hide();

        menuEffect->stop();
        startEffect = new QMediaPlayer(this);
        playlist = new QMediaPlaylist(this);

        // Add media to playlist
        playlist->addMedia(QUrl("qrc:/BattleMusic.mp3")); // Ensure correct path
        playlist->setPlaybackMode(QMediaPlaylist::Loop); // Loop the music

        // Set playlist and volume
        startEffect->setPlaylist(playlist);
        startEffect->setVolume(50); // 0 to 100
        startEffect->play();

        intro->start();

        QTimer::singleShot(2400,this,[this]()
        {
            g = new gamewindow(0,this);
            g->setVisible(true);

            connect(g,&gamewindow::gameover,this,&menu::stopMusic);
            connect(g,&gamewindow::homingSignal,this,&menu::backHome);
            connect(g,&gamewindow::redoSignal,this,&menu::replay);
            this->setVisible(false);
        });
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
        homie->setAttribute(Qt::WA_TranslucentBackground);
        homie->show();

        QGraphicsBlurEffect *introBlur = new QGraphicsBlurEffect;
        introBlur->setBlurHints(introBlur->AnimationHint);
        introBlur->setBlurRadius(10);

        introLabel->setGraphicsEffect(introBlur);


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
        introLabel->setGraphicsEffect(nullptr);
    }
}

void menu::stopMusic()
{
    startEffect->stop();
}


void menu::backHome()
{
    this->setVisible(true);
    start->show();
    exit->show();
    online->show();
    homer->show();

    intro->jumpToFrame(0);
    intro->stop();
}

void menu::replay()
{
    this->setVisible(true);
    g = new gamewindow(0,this);
    QTimer::singleShot(1000,this, []{});
   // emit start->clicked(true);
    g->setVisible(true);
    this->setVisible(false);
    startEffect->play();
}
