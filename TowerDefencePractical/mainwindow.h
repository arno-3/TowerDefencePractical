#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <menubtn.h>
#include <QLabel>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void clicked(bool);

private:
    MenuBtn *start;
    MenuBtn *online;
    MenuBtn *exit;
    MenuBtn *homer;

    QLabel *menulbl;
    QLabel *onlinelbl;
    QLabel *exitlbl;
    QLabel *homerlbl;
    QLabel *homie;

private slots:
    void onStartClicked(bool);
    void onOnlineClicked(bool);
    void onExitClicked(bool);
    void onHomerClicked(bool);
};
#endif // MAINWINDOW_H
