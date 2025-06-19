#include "gamewindow.h"
#include <QDebug>
//#include <enemyhandler.h>
#include <QtConcurrent/QtConcurrentRun>
#include <QSoundEffect>
#include <QGraphicsColorizeEffect>
#include <QPushButton>

gamewindow::gamewindow(QWidget *parent, QMainWindow *menu) : QMainWindow(parent), selectedTowerType(-1)
{
    //Minimize MenuWindow
//    menu->setVisible(false);
//    Menu = menu;
//    wave = 0;
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
    Rprice->setText(QString::number(RegT->towerCost));
    towerCosts[0] = RegT->towerCost;
    Rprice->move(45,70);
    Rprice->setFont(QFont("Comic Sans MS", 15));
    Rprice->setStyleSheet("color: gold; background: transparent;");

    connect(RegT, &TowerBtn::towerSelected, this, &gamewindow::onTowerButtonClicked);

    BigT = new TowerBtn(this,1);
    BigT->move(RegT->width(),0);
    BigT->show();

    Bprice = new QLabel(this);
    Bprice->setText(QString::number(BigT->towerCost));
    towerCosts[1] = BigT->towerCost;
    Bprice->move(145,70);
    Bprice->setFont(QFont("Comic Sans MS", 15));
    Bprice->setStyleSheet("color: gold; background: transparent;");

    connect(BigT, &TowerBtn::towerSelected, this, &gamewindow::onTowerButtonClicked);

    FastT = new TowerBtn(this,2);
    FastT->move(0,RegT->height());
    FastT->show();

    Fprice = new QLabel(this);
    Fprice->setText(QString::number(FastT->towerCost));
    towerCosts[2] = FastT->towerCost;
    Fprice->move(45,170);
    Fprice->setFont(QFont("Comic Sans MS", 15));
    Fprice->setStyleSheet("color: gold; background: transparent;");

    connect(FastT, &TowerBtn::towerSelected, this, &gamewindow::onTowerButtonClicked);

    MineT = new TowerBtn(this,3);
    MineT->move(RegT->width(), RegT->height());
    MineT->show();

    Mprice = new QLabel(this);
    Mprice->setText(QString::number(MineT->towerCost));
    towerCosts[3] = MineT->towerCost;
    Mprice->move(145,170);
    Mprice->setFont(QFont("Comic Sans MS", 15));
    Mprice->setStyleSheet("color: gold; background: transparent;");

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



    enemyH = new EnemyHandler(this,this);
    convertIsometric();
//    QtConcurrent::run([this]{enemyH->run();});
//    enemyH->
    enemyH->run();

    //connect(this,&gamewindow::placedBlock,enemyH,&EnemyHandler::updatePaths);
    connect(enemyH,&EnemyHandler::crash,this,&gamewindow::onCrash);
    connect(this, &gamewindow::gameover,enemyH,&EnemyHandler::endGame);
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

            //connect(gridVector[i][j], &gridBlocks::gridClicked, this, &gamewindow::onGridBlockClicked);


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
            gridVector[i][j]->setAttribute(Qt::WA_TransparentForMouseEvents);
            gridVector[i][j]->setStyleSheet("background: rgba(0,0,0,0); border-radius:50px;"); // Remove any back
            gridVector[i][j]->show();

            btnGrid[i][j] = new QPushButton(this);
            btnGrid[i][j]->move(gridVector[i][j]->get_x()+37,gridVector[i][j]->get_y()+37);
            btnGrid[i][j]->setFixedSize(40,40);
            btnGrid[i][j]->setStyleSheet("background: rgba(88,0,0,0); border-radius:12px;");
            btnGrid[i][j]->show();
            btnGrid[i][j]->setProperty("row",i);
            btnGrid[i][j]->setProperty("col",j);
            btnGrid[i][j]->raise();

            connect(btnGrid[i][j],&QPushButton::clicked,this,&gamewindow::BtnClicked);
//            connect(btnGrid[i][j],&QPushButton::clicked,gridVector[i][j],&gridBlocks::btnClicked);
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

            grassVector[i][j]->show();
            //gridVector[i][j]->raise(); // Ensure gridBlocks is above grass
//            gridVector[i][j]->setProperly();
            btnGrid[i][j]->raise();


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
    selectedTower = (TowerBtn*)QObject::sender();

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
//        selectedTower->setAttribute(Qt::WA_TranslucentBackground);
        selectedTower->setStyleSheet("background:rgba(50,74,128,0);");
//        selectedTower->deleteLater();

        newTower->raise();
        newTower->show();

        towers.push_back(newTower);

        // Deduct gold and update display
        gold -= cost;
        Gold->setText("Gold: " + QString::number(gold));

        if(selectedTowerType == 3)
            enemyH->setCell(-2,row, col);
        else
            enemyH->setCell(-1,row,col);
         enemyH->updatePaths(row,col);
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
        pHealth->setValue(0);

        QSoundEffect *effect = new QSoundEffect(this);
        effect->setSource(QUrl("qrc:/GameOver.wav"));
        effect->setVolume(1); // 0.0 to 1.0 in percentages
        effect->play();

        GameOver();
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
                            if (enemyPos.x() == row && enemyPos.y() == col) {
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

                    QGraphicsColorizeEffect *clr = new QGraphicsColorizeEffect(tower);
                    clr->setColor(Qt::red);
                    clr->setStrength(1);
                    tower->setGraphicsEffect(clr);
                    tower->setAttribute(Qt::WA_StyledBackground);
                    QTimer::singleShot(100, tower, [tower]()
                    {
                        tower->setGraphicsEffect(nullptr);
                    });
//                    tower->graphicsEffect()->deleteLater();
//                    tower->setStyleSheet("background-color: transparent;");

                    towers.removeOne(tower);
                    tower->deleteLater();
                    tower->hide();
                    enemyH->setCell(0,row,col);
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
//                                    canoneffect->deleteLater();
                                }
                                else if (tower->getTowerType() == 1)//big tower
                                {
                                    QSoundEffect *canoneffect = new QSoundEffect(this);
                                    canoneffect->setSource(QUrl("qrc:/BigTowerShot.wav"));
                                    canoneffect->setVolume(0.3); // 0.0 to 1.0
                                    canoneffect->play();
//                                    canoneffect->deleteLater();

                                }
                                else if (tower->getTowerType() == 2) //fast lazer tower
                                {
                                    QSoundEffect *canoneffect = new QSoundEffect(this);
                                    canoneffect->setSource(QUrl("qrc:/laser.wav"));
                                    canoneffect->setVolume(0.5); // 0.0 to 1.0
                                    canoneffect->play();
//                                    canoneffect->deleteLater();
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
//                                tower->setStyleSheet("background-color: red;");
//                                tower->setStyleSheet("mix-blend-mode:multiply; color:red;");

                                QGraphicsColorizeEffect *clr = new QGraphicsColorizeEffect(tower);
                                clr->setColor(Qt::red);
                                clr->setStrength(1);
                                tower->setGraphicsEffect(clr);
                                tower->setAttribute(Qt::WA_StyledBackground);
                                QTimer::singleShot(100, tower, [tower]()
                                {
                                    tower->setGraphicsEffect(nullptr);
                                });
//                                tower->setStyleSheet("background-color: transparent;");
                                //tower->setAttribute(Qt::WA_TranslucentBackground);
                                attacked = true;
                                break;
                            }
//                            if (enemy->properties.health <= 0) {
//                                QSoundEffect *effect = new QSoundEffect(this);
//                                effect->setSource(QUrl("qrc:/death.wav"));
//                                effect->setVolume(0.3); // 0.0 to 1.0 in percentages
//                                effect->play();

//                                addGold(enemy->properties.goldReward); // Reward gold
//                                qDebug() << "Enemy killed, added" << enemy->properties.goldReward << "gold";

//                            }
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

void gamewindow::GameOver()
{
    QLabel* colourobj = new QLabel(this);

    QGraphicsBlurEffect* blur = new QGraphicsBlurEffect(this);
    blur->setBlurHints(blur->PerformanceHint);
    blur->setBlurRadius(2);
    emit gameover();
    QTimer::singleShot(2500,this,[](){});

//    blur->set
//    this->setGraphicsEffect(blur);
//    colourobj->setGraphicsEffect(blur);
    colourobj->setFixedSize(this->size());
    colourobj->setStyleSheet("background-color:rgba(255,10,10,78);");
    colourobj->show();
    colourobj->raise();
    QTimer::singleShot(2500,this,[](){});

    QLabel* Game = new QLabel(this);
    Game->move(0,0);
    Game->setText("Game Over");
    Game->setAttribute(Qt::WA_TranslucentBackground);
    Game->setFixedSize(width(),height());
    Game->setFont(QFont("Comic Sans",56,5,false));
    Game->setStyleSheet("color:black;background:transparent;");
   // this->setGraphicsEffect(blur);
    Game->setAlignment(Qt::AlignCenter);
    Game->show();
    Game->raise();

    home = new QPushButton(this);
    replay = new QPushButton(this);

    home->setFixedSize(300,50);
    replay->setFixedSize(300,50);
    home->setFont(QFont("Comic Sans",15,5,false));
    replay->setFont(QFont("Comic Sans",15,5,false));

    home->move(15,height()-75);
    replay->move(width()-400,height()-75);

    home->setText("Back Home");
    home->setParent(this);
    replay->setText("Retry");
    home->show();
    replay->show();

    connect(home,&QPushButton::clicked,this,&gamewindow::backHome);
    connect(replay, &QPushButton::clicked, this, &gamewindow::retry);
}

void gamewindow::backHome()
{
    emit homingSignal();
//    this->close();
//    enemyH->deleteLater();
    this->deleteLater();
}

void gamewindow::retry()
{

//    enemyH->deleteLater();
    QTimer::singleShot(1000,this, []{});

    emit redoSignal();
    this->deleteLater();
}

void gamewindow::BtnClicked()
{
    QPushButton* btn = (QPushButton*)QObject::sender();
    int r = btn->property("row").toInt();
    int c = btn->property("col").toInt();
    qDebug() << "Clicking"<<endl;
    emit onGridBlockClicked(r, c);
}
