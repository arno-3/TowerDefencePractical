#include "mainwindow.h"
#include "menu.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
    menu m;
    m.show();
    return a.exec();
}
