#include "mainwindow.h"
#include <QFont>
#include <QApplication>
#include <QPixmap>
#include <QSoundEffect>
#include <QVector>
#include <QMediaPlayer>
#include <QMediaPlaylist>

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

    menuEffect = new QMediaPlayer(this);
    QMediaPlaylist *playlist = new QMediaPlaylist(this);

    // Add media to playlist
    playlist->addMedia(QUrl("qrc:/MusicMenu.mp3")); // Ensure correct path
    playlist->setPlaybackMode(QMediaPlaylist::Loop); // Loop the music

    // Set playlist and volume
    menuEffect->setPlaylist(playlist);
    menuEffect->setVolume(100); // 0 to 100
    menuEffect->play();

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


        //TowerBtn specifications:
        //image as background
        //scaledImage ~ to fit for desired grid

        //put the picture or label above for clicking purposes
        //Big tower specs
        QPixmap Btower(":/BigTower.png");
        bigT = new QLabel(this);
        bigT->move(15,0);
        int bigTScaledWidth = 100;  // Desired width
        int bigTScaledHeight = 100; // Desired height
        QPixmap scaledbTower = Btower.scaled(bigTScaledWidth, bigTScaledHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        bigT->setFixedSize(bigTScaledWidth, bigTScaledHeight);
        bigT->setPixmap(scaledbTower);
        bigT->show();


        //Regular tower specs
        QPixmap Rtower(":/RegTower.png");
        regT = new QLabel(this);
        regT->move(120,0);
        int regTScaledWidth = 100;  // Desired width
        int regTScaledHeight = 100; // Desired height
        QPixmap scaledrTower = Rtower.scaled(regTScaledWidth, regTScaledHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        regT->setFixedSize(regTScaledWidth, regTScaledHeight);
        regT->setPixmap(scaledrTower);
        regT->show();

        wall = new QLabel(this);
        wall->move(50,150);
        wall->setText("Wall");
        wall->setStyleSheet("QLabel { font-size: 15px; color: white; }");
        wall->show();

        //Fast tower specs
        QPixmap Ftower(":/FastTower.png");
        fastT = new QLabel(this);
        fastT->move(125,95);
        int fastTScaledWidth = 100;
        int fastTScaledHeight = 100;
        QPixmap scaledfTower = Ftower.scaled(fastTScaledWidth, fastTScaledHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        fastT->setFixedSize(fastTScaledWidth, fastTScaledHeight);
        fastT->setPixmap(scaledfTower);
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

        mTow = new TowerBtn(this);
        mTow->move(0,200);
        mTow->show();

        // Assuming you have a 2D vector for grass labels
        QVector<QVector<QLabel*>> grassVector(10, QVector<QLabel*>(10));

        for (int i = 0; i < 10; ++i)
        {
            for (int j = 0; j < 10; ++j)
            {
                gridVector[i][j] = new gridBlocks(this);

                // Isometric transformation
                int tileWidth = gridVector[i][j]->width();
                int tileHeight = gridVector[i][j]->height();

                // Isometric coordinates
                int x = (j - i) * tileWidth / 2;
                int y = (i + j) * (tileHeight+9) / 4;

                // Center the grid on the screen
                int xOffset = 600;
                int yOffset = 150;

                // Position gridBlocks
                gridVector[i][j]->move(x + xOffset, y + yOffset);
                gridVector[i][j]->setAttribute(Qt::WA_TranslucentBackground); // Ensure transparency
                gridVector[i][j]->setStyleSheet("background: transparent;"); // Remove any back
                gridVector[i][j]->show();

                // Create and position grass label
                QPixmap p(":/GrassTile.png");
                grassVector[i][j] = new QLabel(this);

                int scaledWidth = 500;  // Desired width
                int scaledHeight = 125; // Desired height

                QPixmap scaledPixmap = p.scaled(scaledWidth, scaledHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);

                grassVector[i][j]->setFixedSize(scaledWidth, scaledHeight);

                grassVector[i][j]->setPixmap(scaledPixmap);
                grassVector[i][j]->setAttribute(Qt::WA_TranslucentBackground); // Ensure transparency
                grassVector[i][j]->setStyleSheet("background: transparent;"); // Remove any background
                grassVector[i][j]->move(x + xOffset, y + yOffset);
                grassVector[i][j]->show();
            }
        }

        QPixmap b(":/Base.png");

        int BaseScaledWidth = 125;  // Desired width
        int BaseScaledHeight = 100; // Desired height

        QPixmap scaledBase = b.scaled(BaseScaledWidth, BaseScaledHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        base = new QLabel(this);
        base->setFixedSize(BaseScaledWidth, BaseScaledHeight);
        base->setAttribute(Qt::WA_TranslucentBackground);
        base->move(gridVector[9][9]->x(), gridVector[9][9]->y());
        base->setPixmap(scaledBase);
        base->show();
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
