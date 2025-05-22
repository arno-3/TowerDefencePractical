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
        QSoundEffect *effect = new QSoundEffect(this);
        effect->setSource(QUrl("qrc:/ClickEffect.wav"));
        effect->setVolume(0.5); // 0.0 to 1.0
        effect->play();

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

void MainWindow::onOnlineClicked(bool state)
{
    if (!state)
    {
        QSoundEffect *effect = new QSoundEffect(this);
        effect->setSource(QUrl("qrc:/ClickEffect.wav"));
        effect->setVolume(0.5); // 0.0 to 1.0
        effect->play();

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
        QSoundEffect *effect = new QSoundEffect(this);
        effect->setSource(QUrl("qrc:/ClickEffect.wav"));
        effect->setVolume(0.5); // 0.0 to 1.0
        effect->play();

        QApplication::quit();
    }
}

void MainWindow::onHomerClicked(bool state)
{
    if (!state)
    {
        QSoundEffect *Clickeffect = new QSoundEffect(this);
        Clickeffect->setSource(QUrl("qrc:/ClickEffect.wav"));
        Clickeffect->setVolume(0.5); // 0.0 to 1.0
        Clickeffect->play();

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
