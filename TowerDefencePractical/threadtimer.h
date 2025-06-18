#ifndef THREADTIMER_H
#define THREADTIMER_H

#include <QTimer>
#include <QObject>
#include <QGraphicsOpacityEffect>

class ThreadTimer : public QObject
{
    Q_OBJECT
public:
    explicit ThreadTimer();
    //~ThreadTimer();

signals:
    void finish();
    void opacify(QGraphicsOpacityEffect *op);

public slots:
    void Timeout();
    void run();

private:
    QTimer *timer;
    int timerType = 0;
    void spawn(int);
    void health(int);
    int spawnT = 0;
    int healthT = 0;
};

#endif // THREADTIMER_H
