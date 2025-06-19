#ifndef MENU_H
#define MENU_H

#include <QMainWindow>
#include <menubtn.h>
#include <QSoundEffect>
#include <QMediaPlayer>
#include <gamewindow.h>
#include <QMovie>

class menu : public QMainWindow
{
    Q_OBJECT
public:
    explicit menu(QWidget *parent = nullptr);
    //void stopMusic();

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
    QMovie *intro;
    QLabel *introLabel;

    QSoundEffect *effect;
    int homieCount = 0;

    QMediaPlayer *menuEffect;
    QMediaPlayer *startEffect;
    QMediaPlaylist *playlist;

    gamewindow* g;

private slots:
    void onStartClicked(bool);
    void onOnlineClicked(bool);
    void onExitClicked(bool);
    void onHomerClicked(bool);
    void onTimerTick();
    void stopMusic();
    void backHome();
    void replay();


};

#endif // MENU_H
