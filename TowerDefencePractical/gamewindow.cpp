#include "gamewindow.h"
#include <QDebug>
//#include <enemyhandler.h>
#include <QtConcurrent/QtConcurrentRun>


gamewindow::gamewindow(QWidget *parent, QMainWindow *menu) : QMainWindow(parent), selectedTowerType(-1)
{
    //Minimize MenuWindow
    menu->setVisible(false);


    //Create background and initial state of GameWindow
    setFixedSize(1200,800);
    setStyleSheet("background-color: #5598BF;");

    RegT = new TowerBtn(this,0);
    RegT->move(0,0);
    RegT->show();
    connect(RegT, &TowerBtn::towerSelected, this, &gamewindow::onTowerButtonClicked);

    BigT = new TowerBtn(this,1);
    BigT->move(RegT->width(),0);
    BigT->show();
    connect(BigT, &TowerBtn::towerSelected, this, &gamewindow::onTowerButtonClicked);

    FastT = new TowerBtn(this,2);
    FastT->move(0,RegT->height());
    FastT->show();
    connect(FastT, &TowerBtn::towerSelected, this, &gamewindow::onTowerButtonClicked);

    MineT = new TowerBtn(this,3);
    MineT->move(RegT->width(), RegT->height());
    MineT->show();
    connect(MineT, &TowerBtn::towerSelected, this, &gamewindow::onTowerButtonClicked);

    // Initialize gold display
    Gold = new QLabel(this);
    gold = 100;
    Gold->setText("Gold: " + QString::number(gold));
    Gold->setFixedSize(200, 100);
    Gold->setFont(QFont("Comic Sans MS", 15));
    Gold->setStyleSheet("color: gold; background: transparent;");
    Gold->move(1000, 0);
    Gold->show();

    pHealth = new QProgressBar(this);
    pHealth->move(600,50);
    pHealth->setFixedSize(400,25);
    pHealth->setTextVisible(false);
    pHealth->setOrientation(Qt::Horizontal);
    pHealth->show();
    pHealth->setValue(base_specs.health);


    enemyH = new EnemyHandler(this,this);
    convertIsometric();
//    QtConcurrent::run([this]{enemyH->run();});
//    enemyH->
    enemyH->run();

    //connect(this,&gamewindow::placedBlock,enemyH,&EnemyHandler::updatePaths);
    connect(enemyH,&EnemyHandler::crash,this,&gamewindow::onCrash);
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

            gridVector[i][j]->setGridPosition(i, j); // Set row and col for click handling

            connect(gridVector[i][j], &gridBlocks::gridClicked, this, &gamewindow::onGridBlockClicked);


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
            gridVector[i][j]->setStyleSheet("background: rgba(0,0,0,0); border-radius:50px;"); // Remove any back
            gridVector[i][j]->show();

            enemyH->setGrid(gridVector[i][j]->x(),gridVector[i][j]->y(),i,j);

            // Create and position grass label
            QPixmap p(":/GrassTile.png");
            grassVector[i][j] = new QLabel(this);

            int scaledWidth = 500;  // Desired width
            int scaledHeight = 125; // Desired height

            QPixmap scaledPixmap = p.scaled(scaledWidth, scaledHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);

            grassVector[i][j]->setFixedSize(scaledWidth, scaledHeight);

            grassVector[i][j]->setPixmap(scaledPixmap);
            grassVector[i][j]->setAttribute(Qt::WA_TranslucentBackground); // Ensure transparency
            grassVector[i][j]->setStyleSheet("background: rgba(0,0,0,0);"); // Remove any background
            grassVector[i][j]->setAttribute(Qt::WA_TransparentForMouseEvents); // Ignore mouse events
            grassVector[i][j]->move(x + xOffset, y + yOffset);
            gridVector[i][j]->raise(); // Ensure gridBlocks is above grass
            grassVector[i][j]->show();

            // Add grid to the vectorgrid in EnemyHAndler

            //enemyH->grid
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
    base->setAttribute(Qt::WA_TransparentForMouseEvents); // Ignore mouse events
    base->show();


 }

void gamewindow::onTowerButtonClicked(int towerType)
{
    selectedTowerType = towerType;
    qDebug() << "Tower selected:" << towerType;
}

void gamewindow::onGridBlockClicked(int row, int col)
{
    qDebug() << "Grid clicked at row:" << row << "col:" << col;
    if (selectedTowerType != -1) {
        // Prevent placing tower on base
        if (row == 9 && col == 9) {
            qDebug() << "Cannot place tower on base";
            return;
        }
        if(row == 0 || col == 0)
        {
            qDebug() << "Cannot place tower out of range";
            return;
        }

        // Check if a tower already exists at this position
        for (TowerBtn* tower : towers)
        {
            if (tower->property("row").toInt() == row && tower->property("col").toInt() == col) {
                qDebug() << "Tower already exists at row:" << row << "col:" << col;
                return;
            }
        }

        // Check if player has enough gold
        int cost = towerCosts[selectedTowerType];
        if (base_specs.gold < cost) {
            qDebug() << "Not enough gold to place tower. Required:" << cost << "Available:" << base_specs.gold;
            return;
        }

        // Create new tower
        TowerBtn* newTower = new TowerBtn(this, selectedTowerType);
        newTower->setInteractive(false);
        newTower->setProperty("row", row);
        newTower->setProperty("col", col);
        newTower->move(gridVector[row][col]->x() + (gridVector[row][col]->width() - newTower->width()) / 2 + 15,
                       gridVector[row][col]->y() + (gridVector[row][col]->height() - newTower->height()) / 2 - 20);

        if (selectedTowerType == 3) // LandMine special positioning
        {
            newTower->move(gridVector[row][col]->x() + (gridVector[row][col]->width() - newTower->width()) / 2 + 15,
                           gridVector[row][col]->y() + (gridVector[row][col]->height() - newTower->height()) / 2 + 5);
        }

        newTower->raise();
        newTower->show();

        towers.push_back(newTower);

        // Deduct gold and update display
        base_specs.gold -= cost;
        Gold->setText("Gold: " + QString::number(base_specs.gold));
        enemyH->updatePaths(row,col);
        enemyH->setCell(-1,row,col);
        qDebug() << "Tower placed at row:" << row << "col:" << col << "type:" << selectedTowerType << "cost:" << cost;
        selectedTowerType = -1;
    }
}

void gamewindow::onCrash(int damage)
{
    base_specs.health -= damage;
    pHealth->setValue(base_specs.health);
}
