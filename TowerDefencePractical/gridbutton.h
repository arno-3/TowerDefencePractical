#ifndef GRIDBUTTON_H
#define GRIDBUTTON_H

#include <QObject>
#include <QWidget>
#include <QLabel>

class GridButton : public QWidget
{
    Q_OBJECT
public:
    explicit GridButton(QWidget *parent = nullptr);

private:
    QLab *btn;
    void sendClick();
};

#endif // GRIDBUTTON_H
