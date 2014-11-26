#include "mainwindow.h"
#include "ui_mainwindow.h"

ReadingCSVFiles user;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->NamelineEdit->setPlaceholderText("Name");
    ui->LevellineEdit->setPlaceholderText("Level");

    sunDeleteTimer = new QTimer(this);
    connect(sunDeleteTimer,SIGNAL(timeout()),this,SLOT(deleteSun()));
    sunPointsUpdateTimer = new QTimer(this);
    connect(sunPointsUpdateTimer,SIGNAL(timeout()),this,SLOT(updateSunpoints()));
    //connect to function that iterates through all suns in a vector (or something similar) and deletes ones where
    //sun.isClicked == true;

    plant_ID = 0;
    squareSize = 75;
    sunPointsTotal = 1000;
    timeoutTime = 5000;
    sunUpdate = new sunpoints;

    QString playersFile("C://Users/User/Desktop/Plants vs Zombies files/pvz_players.csv");
    QString levelsFile("C://Users/User/Desktop/Plants vs Zombies files/pvz_levels.csv");
    user.ReadPlayers(playersFile); //Reading the pvz_players.csv
    user.ReadLevels(levelsFile); //Reading the pvz_levels.csv
    user.Sort(); //Sorting the users

    for (int i = 0; i < 5 ; i++)
    {
        if (user.getUser(i)!=NULL && user.getUser(i)!="0")
        {
            ui->UsercomboBox->addItem(user.getUser(i));
        }
    }


   //Assigning player that last played to current user
    currentUserName = user.getUser1();
    currentUserLevel = user.getLevelofUser1();
    currentUserTime = user.getTimeofUser1();

    setPictures(); //Setting pictures to appear in mainwindow.ui


    // Drawing main screen picture
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    scene->addPixmap(QPixmap("C://Users/User/Desktop/Plants vs Zombies files/plants-vs-zombies.png"));

    //Timers
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), scene, SLOT(advance()));

    sunTimer = new QTimer(this);
    connect(sunTimer,SIGNAL(timeout()),this,SLOT(createSun()));

    regularZombieTimer = new QTimer(this);
    connect(regularZombieTimer,SIGNAL(timeout()),this,SLOT(createRegularZombie()));

    seedPeaShooterTimeoutTimer = new QTimer(this);
    connect(seedPeaShooterTimeoutTimer, SIGNAL(timeout()),this,SLOT(seedPeaShooterTimeout()));

    seedPeaShooterEnableTimer = new QTimer(this);
    connect(seedPeaShooterEnableTimer, SIGNAL(timeout()),this,SLOT(seedPeaShooterEnable()));

    seedSunFlowerTimeoutTimer = new QTimer(this);
    connect(seedSunFlowerTimeoutTimer, SIGNAL(timeout()),this,SLOT(seedSunFlowerTimeout()));

    seedSunFlowerEnableTimer = new QTimer(this);
    connect(seedSunFlowerEnableTimer, SIGNAL(timeout()),this,SLOT(seedSunFlowerEnable()));

    seedCherryBombTimeoutTimer = new QTimer(this);
    connect(seedCherryBombTimeoutTimer, SIGNAL (timeout()),this,SLOT(seedCherryBombTimeout()));

    seedCherryBombEnableTimer = new QTimer(this);
    connect(seedCherryBombEnableTimer, SIGNAL (timeout()),this,SLOT(seedCherryBombEnable()));

    seedWallNutTimeoutTimer = new QTimer(this);
    connect(seedWallNutTimeoutTimer, SIGNAL (timeout()),this,SLOT(seedWallNutTimeout()));

    seedWallNutEnableTimer = new QTimer(this);
    connect(seedWallNutEnableTimer, SIGNAL (timeout()),this,SLOT(seedWallNutEnable()));

    seedPotatoMineTimeoutTimer = new QTimer(this);
    connect(seedPotatoMineTimeoutTimer, SIGNAL (timeout()),this,SLOT(seedPotatoMineTimeout()));

    seedPotatoMineEnableTimer = new QTimer(this);
    connect(seedPotatoMineEnableTimer, SIGNAL (timeout()),this,SLOT(seedPotatoMineEnable()));

    seedSnowPeaTimeoutTimer = new QTimer(this);
    connect(seedSnowPeaTimeoutTimer, SIGNAL (timeout()),this,SLOT(seedSnowPeaTimeout()));

    seedSnowPeaEnableTimer = new QTimer(this);
    connect(seedSnowPeaEnableTimer, SIGNAL (timeout()),this,SLOT(seedSnowPeaEnable()));

    seedChomperTimeoutTimer = new QTimer(this);
    connect(seedChomperTimeoutTimer, SIGNAL (timeout()),this,SLOT(seedChomperTimeout()));

    seedChomperEnableTimer = new QTimer(this);
    connect(seedChomperEnableTimer, SIGNAL (timeout()),this,SLOT(seedChomperEnable()));

    seedRepeaterTimeoutTimer = new QTimer(this);
    connect(seedRepeaterTimeoutTimer, SIGNAL (timeout()),this,SLOT(seedRepeaterTimeout()));

    seedRepeaterEnableTimer = new QTimer(this);
    connect(seedRepeaterEnableTimer, SIGNAL (timeout()),this,SLOT(seedRepeaterEnable()));

    //Allowing drawing plants on screen
    ui->graphicsView->mainwindow = this;

    //Allowing sun to be collected
    //sunUpdate->main_window = this;

    //Disabling buttons
    if (ui->UsercomboBox->count() == 0)
    {
        ui->UserpushButton->setEnabled(false);
        ui->StartpushButton->setEnabled(false);
        ui->RestartpushButton->setEnabled(false);
        ui->DeletepushButton->setEnabled(false);
    }

    ui->QuitpushButton->setEnabled(false);
    ui->PeaShooterToolButton->setEnabled(false);
    ui->SunFlowerToolButton->setEnabled(false);
    ui->CherryBombToolButton->setEnabled(false);
    ui->PotatoMineToolButton->setEnabled(false);
    ui->WalNutToolButton->setEnabled(false);
    ui->ChomperToolButton->setEnabled(false);
    ui->SnowPeaToolButton->setEnabled(false);
    ui->RepeaterToolButton->setEnabled(false);

    //Connecting
    //this->connect(sunUpdate,SIGNAL(mouse()),this,SLOT(updateSunpoints()));

    //sunUpdate = new sunpoints();
}

MainWindow::~MainWindow()
{
    user.Write(currentUserName);
    delete ui;
}

void MainWindow::setPictures() //Setting pictures to appear in mainwindow.ui
{
    QPixmap PeaShooter("C://Users/User/Desktop/Plants vs Zombies files/Peashooter_HDD.png");
    ui->PeaShooterToolButton->setIcon(QIcon(PeaShooter));
    QString tooltip="Pea Shooter \nCost 100";
    ui->PeaShooterToolButton->setToolTip(tooltip);

    QPixmap SunFlower("C://Users/User/Desktop/Plants vs Zombies files/Sunflower_HD.png");
    ui->SunFlowerToolButton->setIcon(QIcon(SunFlower));
    QString tooltip1="Sun Flower \nCost 50";
    ui->SunFlowerToolButton->setToolTip(tooltip1);

    QPixmap CherryBomb("C://Users/User/Desktop/Plants vs Zombies files/Cherry Bomb HD.png");
    ui->CherryBombToolButton->setIcon(QIcon(CherryBomb));
    QString tooltip2="Cherry Bomb \nCost 150";
    ui->CherryBombToolButton->setToolTip(tooltip2);

    QPixmap Walnut("C://Users/User/Desktop/Plants vs Zombies files/Hd_Wall-nut.png");
    ui->WalNutToolButton->setIcon(QIcon(Walnut));
    QString tooltip3="WalNut \nCost 50";
    ui->WalNutToolButton->setToolTip(tooltip3);

    QPixmap PotatoMine("C://Users/User/Desktop/Plants vs Zombies files/Potato_Mine_HD.png");
    ui->PotatoMineToolButton->setIcon(QIcon(PotatoMine));
    QString tooltip4="Potato Mine \nCost 25";
    ui->PotatoMineToolButton->setToolTip(tooltip4);

    QPixmap SnowPea("C://Users/User/Desktop/Plants vs Zombies files/Snow_Pea_(HD_size).png");
    ui->SnowPeaToolButton->setIcon(QIcon(SnowPea));
    QString tooltip5="Snow Pea \nCost 175";
    ui->SnowPeaToolButton->setToolTip(tooltip5);

    QPixmap Chomper("C://Users/User/Desktop/Plants vs Zombies files/ChomperHD2.png");
    ui->ChomperToolButton->setIcon(QIcon(Chomper));
    QString tooltip6="Chomper \nCost 150";
    ui->ChomperToolButton->setToolTip(tooltip6);

    QPixmap Repeater("C://Users/User/Desktop/Plants vs Zombies files/Repeater_HD_HD.png");
    ui->RepeaterToolButton->setIcon(QIcon(Repeater));
    QString tooltip7="Repeater \nCost 200";
    ui->RepeaterToolButton->setToolTip(tooltip7);
}

void MainWindow::drawRect(int x, int y) //Testing
{
    scene->addRect(x,y,20,20,QPen(Qt::red),QBrush(Qt::red));
}

void MainWindow::drawPeaShooter(int x, int y) //Drawing Pea Shooter when clicked
{
    PeaShooterClass peaShooterObject;

    //Validating for plant type, where user places plant, if there is enough sunpoints and user level

    if (plant_ID == 1 && x > squareSize && grid[y/squareSize][x/squareSize] == 0 &&
            ((peaShooterObject.getCost() < sunPointsTotal) || peaShooterObject.getCost() == sunPointsTotal))
    {
        if((currentUserLevel == "1" && y > 2*squareSize && y < 3*squareSize)
                || (currentUserLevel == "2" && y > squareSize && y < 4*squareSize)
                || (currentUserLevel == "3") || (currentUserLevel == "4") || (currentUserLevel == "5") ||
                (currentUserLevel == "6") || (currentUserLevel == "7") || (currentUserLevel == "8") ||
                (currentUserLevel == "9"))
        {
            QPixmap PeaShooter("C://Users/User/Desktop/Plants vs Zombies files/Peashooter_HD.png");
            QGraphicsPixmapItem *PeaShooterItem = new PeaShooterClass();
            PeaShooterItem->setPixmap(PeaShooter);
            scene->addItem(PeaShooterItem);

            //Filling the space in the grid with a 1 indicating there is a plant there
            grid[y/squareSize][x/squareSize] = 1;

            //Drawing them in the correct place
            x = (x/squareSize);
            y = (y/squareSize);
            PeaShooterItem->setOffset((x*squareSize)+5,(y*squareSize)+5);

            //Reducing cost
            sunPointsTotal -= peaShooterObject.getCost();
            ui->Pointslabel->setText("Sun Points\n" + QString::number(sunPointsTotal));

            //Seed timeout
            seedPeaShooterTimeoutTimer->start(0);
            seedPeaShooterEnableTimer->start(timeoutTime);

            //Setting plant_ID back to zero
            plant_ID = 0;
        }

    }
}

void MainWindow::drawSunFlower(int x, int y) //Drawing Sun Flower when clicked
{
    SunFlowerClass sunFlowerObject;

    //Validating for plant type, where user places plant, if there is enough sunpoints and user level

    if (plant_ID == 2 && x > squareSize && grid[y/squareSize][x/squareSize] == 0 &&
            ((sunFlowerObject.getCost() < sunPointsTotal) || sunFlowerObject.getCost() == sunPointsTotal))
    {
        if((currentUserLevel == "1" && y > 2*squareSize && y < 3*squareSize)
                || (currentUserLevel == "2" && y > squareSize && y < 4*squareSize)
                || (currentUserLevel == "3") || (currentUserLevel == "4") || (currentUserLevel == "5") ||
                (currentUserLevel == "6") || (currentUserLevel == "7") || (currentUserLevel == "8") ||
                (currentUserLevel == "9"))
        {
            QPixmap SunFlower("C://Users/User/Desktop/Plants vs Zombies files/Sunflower_HD - Copy.png");
            QGraphicsPixmapItem *SunFlowerItem = new SunFlowerClass();
            SunFlowerItem->setPixmap(SunFlower);
            scene->addItem(SunFlowerItem);

            //Filling the space in the grid with a 1 indicating there is a plant there
            grid[y/squareSize][x/squareSize] = 1;

            //Drawing them in the correct place
            x = (x/squareSize);
            y = (y/squareSize);
            SunFlowerItem->setOffset((x*squareSize)+5,(y*squareSize));

            //Setting plant_ID back to zero
            plant_ID = 0;

            //Reducing cost
            sunPointsTotal -= sunFlowerObject.getCost();
            ui->Pointslabel->setText("Sun Points\n" + QString::number(sunPointsTotal));

            //Seed timeout
            seedSunFlowerTimeoutTimer->start(0);
            seedSunFlowerEnableTimer->start(timeoutTime);
        }
    }
}

void MainWindow::drawCherryBomb(int x, int y) //Drawing Cherry Bomb when clicked
{
    CherryBombClass cherryBombObject;

    //Validating for plant type, where user places plant, if there is enough sunpoints and user level

    if (plant_ID == 3 && x > squareSize && grid[y/squareSize][x/squareSize] == 0 &&
            ((cherryBombObject.getCost() < sunPointsTotal) || cherryBombObject.getCost() == sunPointsTotal))
    {
        if((currentUserLevel == "1" && y > 2*squareSize && y < 3*squareSize)
                || (currentUserLevel == "2" && y > squareSize && y < 4*squareSize)
                || (currentUserLevel == "3") || (currentUserLevel == "4") || (currentUserLevel == "5") ||
                (currentUserLevel == "6") || (currentUserLevel == "7") || (currentUserLevel == "8") ||
                (currentUserLevel == "9"))
        {
            QPixmap CherryBomb("C://Users/User/Desktop/Plants vs Zombies files/Cherry Bomb HD - Copy.png");
            QGraphicsPixmapItem *CherryBombItem = new CherryBombClass();
            CherryBombItem->setPixmap(CherryBomb);
            scene->addItem(CherryBombItem);

            //Filling the space in the grid with a 1 indicating there is a plant there
            grid[y/squareSize][x/squareSize] = 1;

            //Drawing them in the correct place
            x = (x/squareSize);
            y = (y/squareSize);
            CherryBombItem->setOffset((x*squareSize),(y*squareSize)+10);

            //Setting plant_ID back to zero
            plant_ID = 0;

            //Reducing cost
            sunPointsTotal -= cherryBombObject.getCost();
            ui->Pointslabel->setText("Sun Points\n" + QString::number(sunPointsTotal));

            //Seed timeout
            seedCherryBombTimeoutTimer->start(0);
            seedCherryBombEnableTimer->start(timeoutTime);
        }
    }
}

void MainWindow::drawWalNut(int x, int y) //Drawing WalNut when clicked
{
    WallNutClass wallNutObject;

    //Validating for plant type, where user places plant, if there is enough sunpoints and user level

    if (plant_ID == 4 && x > squareSize && grid[y/squareSize][x/squareSize] == 0 &&
            ((wallNutObject.getCost() < sunPointsTotal) || wallNutObject.getCost() == sunPointsTotal))
    {
        if((currentUserLevel == "1" && y > 2*squareSize && y < 3*squareSize)
                || (currentUserLevel == "2" && y > squareSize && y < 4*squareSize)
                || (currentUserLevel == "3") || (currentUserLevel == "4") || (currentUserLevel == "5") ||
                (currentUserLevel == "6") || (currentUserLevel == "7") || (currentUserLevel == "8") ||
                (currentUserLevel == "9"))
        {
            QPixmap WalNut("C://Users/User/Desktop/Plants vs Zombies files/Hd_Wall-nut - Copy.png");
            QGraphicsPixmapItem *WalNutItem = new WallNutClass;
            WalNutItem->setPixmap(WalNut);
            scene->addItem(WalNutItem);

            //Filling the space in the grid with a 1 indicating there is a plant there
            grid[y/squareSize][x/squareSize] = 1;

            //Drawing them in the correct place
            x = (x/squareSize);
            y = (y/squareSize);
            WalNutItem->setOffset((x*squareSize)+5,(y*squareSize)+5);

            //Setting plant_ID back to zero
            plant_ID = 0;

            //Reducing cost
            sunPointsTotal -= wallNutObject.getCost();
            ui->Pointslabel->setText("Sun Points\n" + QString::number(sunPointsTotal));

            //Seed timeout
            seedWallNutTimeoutTimer->start(0);
            seedWallNutEnableTimer->start(timeoutTime);
        }
    }
}

void MainWindow::drawPotatoMine(int x, int y) //Drawing PotatoMine when clicked
{
    PotatoMineClass potatoMineObject;

    //Validating for plant type, where user places plant, if there is enough sunpoints and user level

    if (plant_ID == 5 && x > squareSize && grid[y/squareSize][x/squareSize] == 0 &&
           ((potatoMineObject.getCost() < sunPointsTotal) || potatoMineObject.getCost() == sunPointsTotal))
    {
        if((currentUserLevel == "1" && y > 2*squareSize && y < 3*squareSize)
                || (currentUserLevel == "2" && y > squareSize && y < 4*squareSize)
                || (currentUserLevel == "3") || (currentUserLevel == "4") || (currentUserLevel == "5") ||
                (currentUserLevel == "6") || (currentUserLevel == "7") || (currentUserLevel == "8") ||
                (currentUserLevel == "9"))
        {
            QPixmap PotatoMine("C://Users/User/Desktop/Plants vs Zombies files/Potato_Mine_HD - Copy.png");
            QGraphicsPixmapItem *PotatoMineItem = new PotatoMineClass;
            PotatoMineItem->setPixmap(PotatoMine);
            scene->addItem(PotatoMineItem);

            //Filling the space in the grid with a 1 indicating there is a plant there
            grid[y/squareSize][x/squareSize] = 1;

            //Drawing them in the correct place
            x = (x/squareSize);
            y = (y/squareSize);
            PotatoMineItem->setOffset((x*squareSize)+1,(y*squareSize)+5);

            //Setting plant_ID back to zero
            plant_ID = 0;

            //Reducing cost
            sunPointsTotal -= potatoMineObject.getCost();
            ui->Pointslabel->setText("Sun Points\n" + QString::number(sunPointsTotal));

            //Seed timeout
            seedPotatoMineTimeoutTimer->start(0);
            seedPotatoMineEnableTimer->start(timeoutTime);
        }
    }
}

void MainWindow::drawSnowPea(int x, int y) //Drawing Snow Pea when clicked
{
    SnowPeaClass snowPeaObject;

    //Validating for plant type, where user places plant, if there is enough sunpoints and user level

    if (plant_ID == 6 && x > squareSize && grid[y/squareSize][x/squareSize] == 0 &&
            ((snowPeaObject.getCost() < sunPointsTotal) || snowPeaObject.getCost() == sunPointsTotal))
    {
        if((currentUserLevel == "1" && y > 2*squareSize && y < 3*squareSize)
                || (currentUserLevel == "2" && y > squareSize && y < 4*squareSize)
                || (currentUserLevel == "3") || (currentUserLevel == "4") || (currentUserLevel == "5") ||
                (currentUserLevel == "6") || (currentUserLevel == "7") || (currentUserLevel == "8") ||
                (currentUserLevel == "9"))
        {
            QPixmap SnowPea("C://Users/User/Desktop/Plants vs Zombies files/Snow_Pea_(HD_size) - Copy.png");
            QGraphicsPixmapItem *SnowPeaItem = new SnowPeaClass;
            SnowPeaItem->setPixmap(SnowPea);
            scene->addItem(SnowPeaItem);

            //Filling the space in the grid with a 1 indicating there is a plant there
            grid[y/squareSize][x/squareSize] = 1;

            //Drawing them in the correct place
            x = (x/squareSize);
            y = (y/squareSize);
            SnowPeaItem->setOffset((x*squareSize)+1,(y*squareSize)+5);

            //Setting plant_ID back to zero
            plant_ID = 0;

            //Reducing cost
            sunPointsTotal -= snowPeaObject.getCost();
            ui->Pointslabel->setText("Sun Points\n" + QString::number(sunPointsTotal));

            //Seed timeout
            seedSnowPeaTimeoutTimer->start(0);
            seedSnowPeaEnableTimer->start(timeoutTime);
        }
    }
}

void MainWindow::drawChomper(int x, int y) //Drawing Chomper when clicked
{
    ChomperClass chomperObject;

    //Validating for plant type, where user places plant, if there is enough sunpoints and user level

    if (plant_ID == 7 && x > squareSize && grid[y/squareSize][x/squareSize] == 0 &&
            ((chomperObject.getCost() < sunPointsTotal) || chomperObject.getCost() == sunPointsTotal))
    {
        if((currentUserLevel == "1" && y > 2*squareSize && y < 3*squareSize)
                || (currentUserLevel == "2" && y > squareSize && y < 4*squareSize)
                || (currentUserLevel == "3") || (currentUserLevel == "4") || (currentUserLevel == "5") ||
                (currentUserLevel == "6") || (currentUserLevel == "7") || (currentUserLevel == "8") ||
                (currentUserLevel == "9"))
        {
            QPixmap Chomper("C://Users/User/Desktop/Plants vs Zombies files/ChomperHD2 - Copy.png");
            QGraphicsPixmapItem *ChomperItem = new ChomperClass;
            ChomperItem->setPixmap(Chomper);
            scene->addItem(ChomperItem);

            //Filling the space in the grid with a 1 indicating there is a plant there
            grid[y/squareSize][x/squareSize] = 1;

            //Drawing them in the correct place
            x = (x/squareSize);
            y = (y/squareSize);
            ChomperItem->setOffset((x*squareSize),(y*squareSize));

            //Setting plant_ID back to zero
            plant_ID = 0;

            //Reducing cost
            sunPointsTotal -= chomperObject.getCost();
            ui->Pointslabel->setText("Sun Points\n" + QString::number(sunPointsTotal));

            //Seed timeout
            seedChomperTimeoutTimer->start(0);
            seedChomperEnableTimer->start(timeoutTime);
        }
    }
}

void MainWindow::drawRepeater(int x, int y) //Drawing Repeater when clicked
{
    RepeaterClass repeaterObject;

    //Validating for plant type, where user places plant, if there is enough sunpoints and user level

    if (plant_ID == 8 && x > squareSize && grid[y/squareSize][x/squareSize] == 0 &&
            ((repeaterObject.getCost() < sunPointsTotal) || repeaterObject.getCost() == sunPointsTotal))
    {
        if((currentUserLevel == "1" && y > 2*squareSize && y < 3*squareSize)
                || (currentUserLevel == "2" && y > squareSize && y < 4*squareSize)
                || (currentUserLevel == "3") || (currentUserLevel == "4") || (currentUserLevel == "5") ||
                (currentUserLevel == "6") || (currentUserLevel == "7") || (currentUserLevel == "8") ||
                (currentUserLevel == "9"))
        {
            QPixmap Repeater("C://Users/User/Desktop/Plants vs Zombies files/Repeater_HD_HD - Copy.png");
            QGraphicsPixmapItem *RepeaterItem = new RepeaterClass;
            RepeaterItem->setPixmap(Repeater);
            scene->addItem(RepeaterItem);

            //Filling the space in the grid with a 1 indicating there is a plant there
            grid[y/squareSize][x/squareSize] = 1;

            //Drawing them in the correct place
            x = (x/squareSize);
            y = (y/squareSize);
            RepeaterItem->setOffset((x*squareSize)+2,(y*squareSize));

            //Setting plant_ID back to zero
            plant_ID = 0;

            //Reducing cost
            sunPointsTotal -= repeaterObject.getCost();
            ui->Pointslabel->setText("Sun Points\n" + QString::number(sunPointsTotal));

            //Seed timeout
            seedRepeaterTimeoutTimer->start(0);
            seedRepeaterEnableTimer->start(timeoutTime);
        }
    }
}

void MainWindow::updateSunpoints()
{
    sunPointsTotal +=  (sunUpdate->addSunPoints());
    ui->Pointslabel->setText("Sun Points\n" + QString::number(sunPointsTotal));
}

void MainWindow::createSun()
{
    //Adding sun (testing)
    sunpoints *sun = new sunpoints();
    sunAdd.push_back(sun);
    scene->addItem(sunAdd[0]);
    sunDeleteTimer->start(7500);
    qDebug() << "Sun Added";
}

void MainWindow::deleteSun()
{
    scene->removeItem(sunAdd[0]);
    sunAdd.pop_back();
    //sunUpdate->isClicked = true;
    qDebug() << "Sun Deleted";
    //sunUpdate->deleteSUN();
    sunDeleteTimer->stop();
}

void MainWindow::createRegularZombie()
{
    //Adding zombie(testing)
    if (currentUserLevel == "1")
    {
        QPixmap regularzombie("C://Users/User/Desktop/Plants vs Zombies files/PVZ_Zombie_Suit.png");
        QGraphicsPixmapItem *zombieItem = new zombies(2);
        zombieItem->setPixmap(regularzombie);
        scene->addItem(zombieItem);
        zombieItem->setOffset(680,120);
    }

    else if (currentUserLevel == "2")
    {
        QPixmap regularzombie("C://Users/User/Desktop/Plants vs Zombies files/PVZ_Zombie_Suit.png");
        QGraphicsPixmapItem *zombieItem = new zombies(1,1);
        zombieItem->setPixmap(regularzombie);
        scene->addItem(zombieItem);
        zombieItem->setOffset(680,120);
    }
    else
    {
        QPixmap regularzombie("C://Users/User/Desktop/Plants vs Zombies files/PVZ_Zombie_Suit.png");
        QGraphicsPixmapItem *zombieItem = new zombies();
        zombieItem->setPixmap(regularzombie);
        scene->addItem(zombieItem);
        zombieItem->setOffset(680,120);
    }
}

void MainWindow::seedPeaShooterTimeout()
{
    ui->PeaShooterToolButton->setEnabled(false);
}

void MainWindow::seedPeaShooterEnable()
{
    seedPeaShooterTimeoutTimer->stop();
    ui->PeaShooterToolButton->setEnabled(true);
}

void MainWindow::seedSunFlowerTimeout()
{
    ui->SunFlowerToolButton->setEnabled(false);
}

void MainWindow::seedSunFlowerEnable()
{
    seedSunFlowerTimeoutTimer->stop();
    ui->SunFlowerToolButton->setEnabled(true);
}

void MainWindow::seedCherryBombTimeout()
{
     ui->CherryBombToolButton->setEnabled(false);
}

void MainWindow::seedCherryBombEnable()
{
    seedCherryBombTimeoutTimer->stop();
    ui->CherryBombToolButton->setEnabled(true);
}

void MainWindow::seedWallNutTimeout()
{
    ui->WalNutToolButton->setEnabled(false);
}

void MainWindow::seedWallNutEnable()
{
    seedWallNutTimeoutTimer->stop();
    ui->WalNutToolButton->setEnabled(true);
}

void MainWindow::seedPotatoMineTimeout()
{
    ui->PotatoMineToolButton->setEnabled(false);
}

void MainWindow::seedPotatoMineEnable()
{
    seedPotatoMineTimeoutTimer->stop();
    ui->PotatoMineToolButton->setEnabled(true);
}

void MainWindow::seedSnowPeaTimeout()
{
    ui->SnowPeaToolButton->setEnabled(false);
}

void MainWindow::seedSnowPeaEnable()
{
    seedSnowPeaTimeoutTimer->stop();
    ui->SnowPeaToolButton->setEnabled(true);
}

void MainWindow::seedChomperTimeout()
{
    ui->ChomperToolButton->setEnabled(false);
}

void MainWindow::seedChomperEnable()
{
    seedChomperTimeoutTimer->stop();
    ui->ChomperToolButton->setEnabled(true);
}

void MainWindow::seedRepeaterTimeout()
{
    ui->RepeaterToolButton->setEnabled(false);
}

void MainWindow::seedRepeaterEnable()
{
    seedRepeaterTimeoutTimer->stop();
    ui->RepeaterToolButton->setEnabled(true);
}


void MainWindow::on_DeletepushButton_clicked()
{
    textSearch = ui->UsercomboBox->currentText();

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Delete User", "Are you sure you want to delete user '"
                                  + ui->UsercomboBox->currentText() + "' ?",
                                    QMessageBox::Yes|QMessageBox::No);
      if (reply == QMessageBox::Yes) {
        qDebug() << "Yes delete was clicked";
        user.deleteUser(textSearch); //Deletes User
        ui->UsercomboBox->clear(); //Clears combobox before readding non NULL users
        for (int i = 0; i < 5 ; i++)
        {
            if (user.getUser(i)!=NULL && user.getUser(i)!="0")
            {
                 ui->UsercomboBox->addItem(user.getUser(i));
            }
        }
        if (user.getTotal() == 0)
        {
            ui->UserpushButton->setEnabled(false);
            ui->StartpushButton->setEnabled(false);
            ui->RestartpushButton->setEnabled(false);
            ui->DeletepushButton->setEnabled(false);
        }
      }
      else {
        qDebug() << "Yes delete was *not* clicked";
      }
}


void MainWindow::on_NewpushButton_clicked()
{
    //Validate name
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this,"New User",ui->NamelineEdit->text()+ "?", QMessageBox::Ok|QMessageBox::Cancel);
    QString userName = (ui->NamelineEdit->text());
    if (reply == QMessageBox::Ok)
    {
//        if (user.getTotal()< 5)
//        {
            ui->UsercomboBox->addItem(userName);
            QString time = QString::number(QDateTime::currentDateTime().toTime_t());
            user.addLists(time,userName,"1");
            user.ReadPlayers("C://Users/User/Desktop/Plants vs Zombies files/pvz_players.csv");
            user.Sort();
            ui->UserpushButton->setEnabled(true);
            ui->StartpushButton->setEnabled(true);
            ui->RestartpushButton->setEnabled(true);
            ui->DeletepushButton->setEnabled(true);
//        }
//        else
//            QMessageBox::question(this,"Max 5 Users", "Maximum users reached. Delete a user before creating a new one.",
//                                  QMessageBox::Ok|QMessageBox::Cancel); //Max 5 users in csv
    } 
}

void MainWindow::on_StartpushButton_clicked()
{
    //Showing sun points
    ui->Pointslabel->setText("Sun Points\n" + QString::number(sunPointsTotal));

    //Showing current user level on screen
    ui->LevellineEdit->setText(currentUserLevel);

    //Drawing 10x5 lawn grid
    scene->clear();
    QBrush darkGreenBrush(Qt::darkGreen);
    QBrush brown (QColor(102,51,0));
    QBrush pale (QColor(255,229,204));
    QPen blackPen(Qt::black);
    scene->setBackgroundBrush(QBrush(darkGreenBrush));
    scene->addRect(0,0,75,375,blackPen,pale); //adding pale tile, the home coloumn

    //Adding lawn mowers in the home column
    QPixmap LawnMower("C://Users/User/Desktop/Plants vs Zombies files/Lawn_Mower.png");

    //Adding brown tiles according to level
    if(currentUserLevel.toInt() == 1) //Only 1 green row and lawnmower will be shown
    {
        scene->addRect(75,0,675,75,blackPen,brown);
        scene->addRect(75,75,675,75,blackPen,brown);
        scene->addRect(75,225,675,75,blackPen,brown);
        scene->addRect(75,300,675,75,blackPen,brown);
        scene->addPixmap(LawnMower)->setOffset(0,160);
    }

    else if(currentUserLevel.toInt() == 2) //Only 3 green rows and lawnmowers will be shown
    {
        scene->addRect(75,0,675,75,blackPen,brown);
        scene->addRect(75,300,675,75,blackPen,brown);
        scene->addPixmap(LawnMower)->setOffset(0,85);
        scene->addPixmap(LawnMower)->setOffset(0,160);
        scene->addPixmap(LawnMower)->setOffset(0,235);
    }
    else
    {
        scene->addPixmap(LawnMower)->setOffset(0,10);
        scene->addPixmap(LawnMower)->setOffset(0,85);
        scene->addPixmap(LawnMower)->setOffset(0,160);
        scene->addPixmap(LawnMower)->setOffset(0,235);
        scene->addPixmap(LawnMower)->setOffset(0,310);
    }

    //Adding lines vertically

    for(int i=0; i<751; i+=squareSize)
    {
        scene->addLine(i,0,i,375,blackPen);
    }

    //Adding lines horizontally
    for(int i=0; i <376; i+=squareSize)
    {
        scene->addLine(0,i,750,i,blackPen);
    }

    //Adjusting graphicsview size
    ui->graphicsView->adjustSize();

    //Starting timer
    timer->start(58);
    sunTimer->start(10000);
    regularZombieTimer->start(5000);
    sunPointsUpdateTimer->start(0);

    //Adding bullet(testing)
//    QPixmap Bullets("C://Users/User/Desktop/Plants vs Zombies files/Bullets.png");
//    QGraphicsPixmapItem *BulletsItem = new bullets();
//    BulletsItem->setPixmap(Bullets);
//    scene->addItem(BulletsItem);
//    BulletsItem->setOffset(75,150);

    //Filling grid with 0s meaning there is no plant anywhere
    for (int n=0; n < 5; n++)
        for (int m=0; m < 10; m++)
        {
          grid[n][m]=0;
        }

    ui->QuitpushButton->setEnabled(true);
    ui->PeaShooterToolButton->setEnabled(true);
    ui->SunFlowerToolButton->setEnabled(true);
    ui->CherryBombToolButton->setEnabled(true);
    ui->PotatoMineToolButton->setEnabled(true);
    ui->WalNutToolButton->setEnabled(true);
    ui->ChomperToolButton->setEnabled(true);
    ui->SnowPeaToolButton->setEnabled(true);
    ui->RepeaterToolButton->setEnabled(true);
}

void MainWindow::on_RestartpushButton_clicked() //Game restarts
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Restart", "Are you sure you want to restart this level?",
                                    QMessageBox::Yes|QMessageBox::No);
      if (reply == QMessageBox::Yes) {
        qDebug() << "Yes restart was clicked";
        {
            //Set default sun points
            sunPointsTotal = 1000;

            //Start
            on_StartpushButton_clicked();

            //Enabling tool buttons
            seedPeaShooterEnable();
            seedSunFlowerEnable();
            seedCherryBombEnable();
            seedWallNutEnable();
            seedPotatoMineEnable();
            seedSnowPeaEnable();
            seedChomperEnable();
            seedRepeaterEnable();
        }
      } else {
        qDebug() << "Restart was *not* clicked";
      }
}

void MainWindow::on_QuitpushButton_clicked() //Level closes when user presses Yes
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Quit", "Are you sure you want to leave this level?",
                                    QMessageBox::Yes|QMessageBox::No);
      if (reply == QMessageBox::Yes) {
        qDebug() << "Yes quit was clicked";
        {
            scene->setBackgroundBrush(QBrush(Qt::white));
            scene->clear();
            scene->addPixmap(QPixmap("C://Users/User/Desktop/Plants vs Zombies files/plants-vs-zombies.png"))->setPos(30,0);

            //Disabling buttons
            ui->QuitpushButton->setEnabled(false);
            ui->PeaShooterToolButton->setEnabled(false);
            ui->SunFlowerToolButton->setEnabled(false);
            ui->CherryBombToolButton->setEnabled(false);
            ui->PotatoMineToolButton->setEnabled(false);
            ui->WalNutToolButton->setEnabled(false);
            ui->ChomperToolButton->setEnabled(false);
            ui->SnowPeaToolButton->setEnabled(false);
            ui->RepeaterToolButton->setEnabled(false);

        }
      } else {
        qDebug() << "Yes quit was *not* clicked";
      }
}

void MainWindow::on_UserpushButton_clicked()
{
    QMessageBox::information(this,"Title",ui->UsercomboBox->currentText());
    textSearch = ui->UsercomboBox->currentText();
    QString name,time,level;

    //Searches for username in csv
    name = user.SearchName(textSearch);
    time = user.SearchTime(textSearch);
    level = user.SearchLevel(textSearch);
    currentUserName = name;
    currentUserTime = time;
    currentUserLevel = level;
    qDebug() << name << time << level;

    //Showing current user level on screen
    ui->LevellineEdit->setText(currentUserLevel);
}

void MainWindow::on_PeaShooterToolButton_clicked()
{
    plant_ID = 1;
}

void MainWindow::on_SunFlowerToolButton_clicked()
{
    plant_ID = 2;
}

void MainWindow::on_CherryBombToolButton_clicked()
{
    plant_ID = 3;
}

void MainWindow::on_WalNutToolButton_clicked()
{
    plant_ID = 4;
}

void MainWindow::on_PotatoMineToolButton_clicked()
{
    plant_ID = 5;
}

void MainWindow::on_SnowPeaToolButton_clicked()
{
    plant_ID = 6;
}

void MainWindow::on_ChomperToolButton_clicked()
{
    plant_ID = 7;
}

void MainWindow::on_RepeaterToolButton_clicked()
{
    plant_ID = 8;
}
