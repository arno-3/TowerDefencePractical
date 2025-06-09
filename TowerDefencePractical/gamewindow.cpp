#include "gamewindow.h"

gamewindow::gamewindow(QWidget *parent, QMainWindow *menu) : QMainWindow(parent)
{
    //Minimize MenuWindow
    menu->setVisible(false);


    //Create background and initial state of GameWindow
    setFixedSize(1200,800);
    setStyleSheet("background-color: #5598BF;");

    RegT = new TowerBtn(this,0);
    RegT->move(0,0);
    RegT->show();

    BigT = new TowerBtn(this,1);
    BigT->move(RegT->width(),0);
    BigT->show();

    FastT = new TowerBtn(this,2);
    FastT->move(0,RegT->height());
    FastT->show();

    convertIsometric();

}

void gamewindow::onExit(QMainWindow *m)
{
    m->setVisible(true);
}


void gamewindow::createMap()
{

}

void gamewindow::convertIsometric()
{
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

}
