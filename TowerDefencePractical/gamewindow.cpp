#include "gamewindow.h"
#include <QDebug>
//#include <enemyhandler.h>
#include <QtConcurrent/QtConcurrentRun>
#include <QSoundEffect>
#include <QMediaPlayer>
#include <QMediaPlaylist>

gamewindow::gamewindow(QWidget *parent, QMainWindow *menu) : QMainWindow(parent), selectedTowerType(-1)
{
    //Minimize MenuWindow
    menu->setVisible(false);

    gameTimer = new QTimer(this);
    connect(gameTimer, &QTimer::timeout, this, &gamewindow::updateGame);
    gameTimer->start(16); // ~60 FPS (16ms per frame)


    //Create background and initial state of GameWindow
    setFixedSize(1200,800);
    setStyleSheet("background-color: #5598BF;");

    RegT = new TowerBtn(this,0);
    RegT->move(0,0);
    RegT->show();

    Rprice = new QLabel(this);
    Rprice->setText("20");
    Rprice->move(45,70);
    Rprice->setFont(QFont("Comic Sans MS", 15));
    Rprice->setStyleSheet("color: gold; background: transparent;");

    connect(RegT, &TowerBtn::towerSelected, this, &gamewindow::onTowerButtonClicked);

    BigT = new TowerBtn(this,1);
    BigT->move(RegT->width(),0);
    BigT->show();

    Bprice = new QLabel(this);
    Bprice->setText("30");
    Bprice->move(145,70);
    Bprice->setFont(QFont("Comic Sans MS", 15));
    Bprice->setStyleSheet("color: gold; background: transparent;");

    connect(BigT, &TowerBtn::towerSelected, this, &gamewindow::onTowerButtonClicked);

    FastT = new TowerBtn(this,2);
    FastT->move(0,RegT->height());
    FastT->show();

    Fprice = new QLabel(this);
    Fprice->setText("25");
    Fprice->move(45,170);
    Fprice->setFont(QFont("Comic Sans MS", 15));
    Fprice->setStyleSheet("color: gold; background: transparent;");

    connect(FastT, &TowerBtn::towerSelected, this, &gamewindow::onTowerButtonClicked);

    MineT = new TowerBtn(this,3);
    MineT->move(RegT->width(), RegT->height());
    MineT->show();

    Bprice = new QLabel(this);
    Bprice->setText("15");
    Bprice->move(145,170);
    Bprice->setFont(QFont("Comic Sans MS", 15));
    Bprice->setStyleSheet("color: gold; background: transparent;");

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
    pHealth->move(450,50);
    pHealth->setFixedSize(400,25);
    pHealth->setTextVisible(false);
    pHealth->setOrientation(Qt::Horizontal);
    pHealth->show();
    pHealth->setValue(base_specs.health);

    bHealth = new QLabel(this);
    bHealth->move(450,25);
    bHealth->setFixedSize(400,25);
    bHealth->setText("BASE HEALTH: " + QString::number(pHealth->value()));
    bHealth->setFont(QFont("Comic Sans MS", 15));


    thread = new QThread();
    enemyH = new EnemyHandler(this,this, thread);
    enemyH->run();
    convertIsometric();
//    QtConcurrent::run([this]{enemyH->run();});
//    enemyH->

//    enemyH->moveToThread(thread);

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
    TowerBtn *btn = (TowerBtn*)QObject::sender();
    btn->setStyleSheet("background:rgba(5,5,16,58);");
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
        if (gold < cost) {
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
        gold -= cost;
        Gold->setText("Gold: " + QString::number(gold));
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
    bHealth->setText("BASE HEALTH: " + QString::number(pHealth->value()));

    if (base_specs.health <= 0)
    {
         bHealth->setText("BASE HEALTH: 0");

         QSoundEffect *effect = new QSoundEffect(this);
         effect->setSource(QUrl("qrc:/GameOver.wav"));
         effect->setVolume(1); // 0.0 to 1.0 in percentages
         effect->play();
    }
}

void gamewindow::updateGame() {
    for (TowerBtn* tower : towers) {
        tower->updateCooldown(16);
        if (tower->canAttack()) {
            int row = tower->property("row").toInt();
            int col = tower->property("col").toInt();
            int adjacent[8][2] = {
                {row-1, col},
                {row+1, col},
                {row, col-1},
                {row, col+1},
                {row-1, col-1},
                {row-1, col+1},
                {row+1, col-1},
                {row+1, col+1}
            };
            bool attacked = false;
            if (tower->getTowerType() == 3) { // Mine Tower: Damage all enemies in adjacent cells
                for (const auto& pos : adjacent) {
                    int r = pos[0];
                    int c = pos[1];
                    if (r >= 0 && r < 10 && c >= 0 && c < 10) {
                        for (enemies* enemy : enemyH->getEnemies()) {
                            QPoint enemyPos = enemy->getPos();
                            if (enemyPos.x() == r && enemyPos.y() == c) {
                                enemyH->damageEnemy(enemy, tower->getDamage());
                                if (enemy->properties.health <= 0) {
                                    addGold(enemy->properties.goldReward); // Reward gold
                                    qDebug() << "Enemy killed, added" << enemy->properties.goldReward << "gold";

                                    QSoundEffect *effect = new QSoundEffect(this);
                                    effect->setSource(QUrl("qrc:/death.wav"));
                                    effect->setVolume(0.2); // 0.0 to 1.0 in percentages
                                    effect->play();
                                }
                                attacked = true;
                            }
                        }
                    }
                }
                if (attacked) {
                    towers.removeOne(tower);
                    tower->deleteLater();
                    tower->hide();
                    QSoundEffect *effect = new QSoundEffect(this);
                    effect->setSource(QUrl("qrc:/explosion.wav"));
                    effect->setVolume(0.5); // 0.0 to 1.0
                    effect->play();
                }
            } else { // Other towers: Attack one enemy
                for (const auto& pos : adjacent) {
                    int r = pos[0];
                    int c = pos[1];
                    if (r >= 0 && r < 10 && c >= 0 && c < 10) {
                        for (enemies* enemy : enemyH->getEnemies()) {
                            QPoint enemyPos = enemy->getPos();
                            if (enemyPos.x() == r && enemyPos.y() == c) {
                                enemyH->damageEnemy(enemy, tower->getDamage());
                                if (tower->getTowerType() == 0) //regular tower
                                {
                                    QSoundEffect *canoneffect = new QSoundEffect(this);
                                    canoneffect->setSource(QUrl("qrc:/cannon.wav"));
                                    canoneffect->setVolume(0.5); // 0.0 to 1.0
                                    canoneffect->play();
                                }
                                else if (tower->getTowerType() == 1)//big tower
                                {
                                    QSoundEffect *canoneffect = new QSoundEffect(this);
                                    canoneffect->setSource(QUrl("qrc:/BigTowerShot.wav"));
                                    canoneffect->setVolume(0.3); // 0.0 to 1.0
                                    canoneffect->play();

                                }
                                else if (tower->getTowerType() == 2) //fast lazer tower
                                {
                                    QSoundEffect *canoneffect = new QSoundEffect(this);
                                    canoneffect->setSource(QUrl("qrc:/laser.wav"));
                                    canoneffect->setVolume(0.5); // 0.0 to 1.0
                                    canoneffect->play();
                                }

                                if (enemy->properties.health <= 0) {
                                    QSoundEffect *effect = new QSoundEffect(this);
                                    effect->setSource(QUrl("qrc:/death.wav"));
                                    effect->setVolume(0.3); // 0.0 to 1.0 in percentages
                                    effect->play();

                                    addGold(enemy->properties.goldReward); // Reward gold
                                    qDebug() << "Enemy killed, added" << enemy->properties.goldReward << "gold";
                                }
                                tower->resetCooldown();
                                tower->setStyleSheet("background-color: red;");
                                QTimer::singleShot(100, tower, [tower]() {
                                    tower->setStyleSheet("");
                                });
                                attacked = true;
                                break;
                            }
                        }
                        if (attacked) break;
                    }
                }
            }
        }
    }
}

void gamewindow::addGold(int amount) {
    gold += amount;
    Gold->setText("Gold: " + QString::number(gold));
}
