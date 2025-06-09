#ifndef MENU_H
#define MENU_H

#include <QMainWindow>
#include <menubtn.h>
#include <QSoundEffect>

class menu : public QMainWindow
{
    Q_OBJECT
public:
    explicit menu(QWidget *parent = nullptr);

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

    QSoundEffect *effect;
    int homieCount = 0;

private slots:
    void onStartClicked(bool);
    void onOnlineClicked(bool);
    void onExitClicked(bool);
    void onHomerClicked(bool);
    void onTimerTick();
};

#endif // MENU_H
