#include "mainwindow.h"
#include "ui_mainwindow.h"

ReadingCSVFiles user;
int MainWindow::peaShooterCounter = 0;
int MainWindow::snowPeaCounter = 0;
int MainWindow::sunFlowerCounter = 0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->NamelineEdit->setPlaceholderText("Name");
    ui->LevellineEdit->setPlaceholderText("Level");

    //Timers
    sunDeleteTimer = new QTimer(this);
    connect(sunDeleteTimer,SIGNAL(timeout()),this,SLOT(deleteSun()));

    sunPointsUpdateTimer = new QTimer(this);
    connect(sunPointsUpdateTimer,SIGNAL(timeout()),this,SLOT(updateSunpoints()));

    peaShooterBulletsTimer1 = new QTimer(this);
    connect(peaShooterBulletsTimer1,SIGNAL(timeout()),this,SLOT(createBullet1PeaShooter()));

    peaShooterBulletsTimer2 = new QTimer(this);
    connect(peaShooterBulletsTimer2,SIGNAL(timeout()),this,SLOT(createBullet2PeaShooter()));

    peaShooterBulletsTimer3 = new QTimer(this);
    connect(peaShooterBulletsTimer3,SIGNAL(timeout()),this,SLOT(createBullet3PeaShooter()));

    snowPeaBulletsTimer1 = new QTimer(this);
    connect(snowPeaBulletsTimer1,SIGNAL(timeout()),this,SLOT(createBullet1SnowPea()));

    snowPeaBulletsTimer2 = new QTimer(this);
    connect(snowPeaBulletsTimer2,SIGNAL(timeout()),this,SLOT(createBullet2SnowPea()));

    snowPeaBulletsTimer3 = new QTimer(this);
    connect(snowPeaBulletsTimer3,SIGNAL(timeout()),this,SLOT(createBullet3SnowPea()));

    sunFlowerSunsCreateTimer1 = new QTimer(this);
    connect(sunFlowerSunsCreateTimer1,SIGNAL(timeout()),this,SLOT(createSun1SunFlower()));

    sunFlowerSunsCreateTimer2 = new QTimer(this);
    connect(sunFlowerSunsCreateTimer2,SIGNAL(timeout()),this,SLOT(createSun2SunFlower()));

    sunFlowerSunsCreateTimer3 = new QTimer(this);
    connect(sunFlowerSunsCreateTimer3,SIGNAL(timeout()),this,SLOT(createSun3SunFlower()));

    sunFlowerSunsDeleteTimer1 = new QTimer(this);
    connect(sunFlowerSunsDeleteTimer1,SIGNAL(timeout()),this,SLOT(deleteSun1SunFlower()));

    sunFlowerSunsDeleteTimer2 = new QTimer(this);
    connect(sunFlowerSunsDeleteTimer2,SIGNAL(timeout()),this,SLOT(deleteSun2SunFlower()));

    sunFlowerSunsDeleteTimer3 = new QTimer(this);
    connect(sunFlowerSunsDeleteTimer3,SIGNAL(timeout()),this,SLOT(deleteSun3SunFlower()));

    plantsCostTimer = new QTimer(this);
    connect(plantsCostTimer,SIGNAL(timeout()),this,SLOT(plantsCostt()));

    plant_ID = 0;
    squareSize = 75;
    sunPointsTotal = 2000;
    timeoutTime = 5000;
    levelOneCounter = 0;
    sunUpdate = new sunpoints;
    zombieStop = new zombies;

    QString playersFile("C://Users/User/Desktop/Plants vs Zombies files/pvz_players.csv");
    QString levelsFile("C://Users/User/Desktop/Plants vs Zombies files/pvz_levels.csv");
    user.ReadLevels(levelsFile); //Reading the pvz_levels.csv

    QFile mFile;
    mFile.setFileName("pvz_players.csv");
    QDir::setCurrent("C://Users/User/Desktop/Plants vs Zombies files/");
    if (mFile.exists() == false)
    {

    }
    else
    {
        if (user.ReadPlayers(playersFile) == true) //Reading the pvz_players.csv
{
        user.Sort(); //Sorting the users

        for (int i = 0; i < 5 ; i++)
        {
            if (user.getUser(i)!=NULL && user.getUser(i)!="0")
            {
                ui->UsercomboBox->addItem(user.getUser(i));
            }
            if (nameValidation(user.getUser(i)) == false && user.getUser(i)!="")
            {
                if (i == 0)
                    ui->UsercomboBox->removeItem(0);
                if (i == 1)
                {
                    ui->UsercomboBox->removeItem(1);
                    ui->UsercomboBox->removeItem(0);
                }
                if (i == 2)
                {
                    ui->UsercomboBox->removeItem(0);
                    ui->UsercomboBox->removeItem(1);
                    ui->UsercomboBox->removeItem(2);
                }
                if (i == 3)
                {
                    ui->UsercomboBox->removeItem(0);
                    ui->UsercomboBox->removeItem(1);
                    ui->UsercomboBox->removeItem(2);
                    ui->UsercomboBox->removeItem(3);
                }
                if (i == 4)
                {
                    ui->UsercomboBox->removeItem(0);
                    ui->UsercomboBox->removeItem(1);
                    ui->UsercomboBox->removeItem(2);
                    ui->UsercomboBox->removeItem(3);
                    ui->UsercomboBox->removeItem(4);
                }
                qDebug() << "Warning: Program starting with no users";
                break;
             }
        }

       //Assigning player that last played to current user
        currentUserName = user.getUser1();
        currentUserLevel = user.getLevelofUser1();
        currentUserTime = user.getTimeofUser1();
        }
    }

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

    flagZombieTimer = new QTimer(this);
    connect(flagZombieTimer,SIGNAL(timeout()),this,SLOT(createFlagZombie()));

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
            qDebug() << peaShooterCounter;

            if(peaShooterCounter == 0)
            {xPeaShooter1 = ((x/75)*75)+20; yPeaShooter1 = ((y/75)*75)+20;}
            if(peaShooterCounter == 1)
            {xPeaShooter2 = ((x/75)*75)+20; yPeaShooter2 = ((y/75)*75)+20;}
            if(peaShooterCounter > 1)
            {xPeaShooter3 = ((x/75)*75)+20; yPeaShooter3 = ((y/75)*75)+20;}

            QPixmap PeaShooter("C://Users/User/Desktop/Plants vs Zombies files/Peashooter_HD.png");
            QGraphicsPixmapItem *PeaShooterItem = new PeaShooterClass(xPeaShooter1,yPeaShooter1);
            PeaShooterItem->setPixmap(PeaShooter);
            scene->addItem(PeaShooterItem);

            //Removing Palette
            ui->PeaShooterToolButton->setAutoFillBackground(false);

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
            seedPeaShooterEnableTimer->start((peaShooterObject.getSeeding())*1000);

            //Setting plant_ID back to zero
            plant_ID = 0;

            //Adding bullets
            if(peaShooterCounter > 1)
            {
                peaShooterBulletsTimer3->start((peaShooterObject.getRate())*1000);
            }
            if(peaShooterCounter == 1)
            {
                peaShooterBulletsTimer2->start((peaShooterObject.getRate())*1000);
                peaShooterCounter++;
            }
            if(peaShooterCounter == 0)
            {
                peaShooterBulletsTimer1->start((peaShooterObject.getRate())*1000);
                peaShooterCounter++;
            }

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

            if(sunFlowerCounter == 0)
            {xSunFlower1 = ((x/75)*75)+20; ySunFlower1 = ((y/75)*75)+20;}
            if(sunFlowerCounter == 1)
            {xSunFlower2 = ((x/75)*75)+20; ySunFlower2 = ((y/75)*75)+20;}
            if(sunFlowerCounter > 1)
            {xSunFlower3 = ((x/75)*75)+20; ySunFlower3 = ((y/75)*75)+20;}

            QPixmap SunFlower("C://Users/User/Desktop/Plants vs Zombies files/Sunflower_HD - Copy.png");
            QGraphicsPixmapItem *SunFlowerItem = new SunFlowerClass();
            SunFlowerItem->setPixmap(SunFlower);
            scene->addItem(SunFlowerItem);

            //Removing Palette
            ui->SunFlowerToolButton->setAutoFillBackground(false);

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
            seedSunFlowerEnableTimer->start((sunFlowerObject.getSeeding())*1000);         

            //Adding Suns
            if(sunFlowerCounter > 1)
            {
                sunFlowerSunsCreateTimer3->start((sunFlowerObject.getRate())*1000);
            }
            if(sunFlowerCounter == 1)
            {
                sunFlowerSunsCreateTimer2->start((sunFlowerObject.getRate())*1000);
                sunFlowerCounter++;
            }
            if(sunFlowerCounter == 0)
            {
                sunFlowerSunsCreateTimer1->start((sunFlowerObject.getRate())*1000);
                sunFlowerCounter++;
            }
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

            //Removing Palette
            ui->CherryBombToolButton->setAutoFillBackground(false);

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
            seedCherryBombEnableTimer->start((cherryBombObject.getSeeding())*1000);
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

            //Removing Palette
            ui->WalNutToolButton->setAutoFillBackground(false);

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
            seedWallNutEnableTimer->start((wallNutObject.getSeeding())*1000);
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

            //Removing Palette
            ui->PotatoMineToolButton->setAutoFillBackground(false);

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
            seedPotatoMineEnableTimer->start((potatoMineObject.getSeeding())*1000);
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
            if(snowPeaCounter == 0)
            {xSnowPea1 = ((x/75)*75)+20; ySnowPea1 = ((y/75)*75)+20;}
            if(snowPeaCounter == 1)
            {xSnowPea2 = ((x/75)*75)+20; ySnowPea2 = ((y/75)*75)+20;}
            if(snowPeaCounter > 1)
            {xSnowPea3 = ((x/75)*75)+20; ySnowPea3 = ((y/75)*75)+20;}

            QPixmap SnowPea("C://Users/User/Desktop/Plants vs Zombies files/Snow_Pea_(HD_size) - Copy.png");
            QGraphicsPixmapItem *SnowPeaItem = new SnowPeaClass;
            SnowPeaItem->setPixmap(SnowPea);
            scene->addItem(SnowPeaItem);

            //Removing Palette
            ui->SnowPeaToolButton->setAutoFillBackground(false);

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
            seedSnowPeaEnableTimer->start((snowPeaObject.getSeeding())*1000);

            //Adding bullets
            if(snowPeaCounter > 1)
            {
                snowPeaBulletsTimer3->start((snowPeaObject.getRate())*1000);
            }
            if(snowPeaCounter == 1)
            {
                snowPeaBulletsTimer2->start((snowPeaObject.getRate())*1000);
                snowPeaCounter++;
            }
            if(snowPeaCounter == 0)
            {
                snowPeaBulletsTimer1->start((snowPeaObject.getRate())*1000);
                snowPeaCounter++;
            }
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

            //Removing Palette
            ui->ChomperToolButton->setAutoFillBackground(false);

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
            seedChomperEnableTimer->start((chomperObject.getSeeding())*1000);
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

            //Removing Palette
            ui->RepeaterToolButton->setAutoFillBackground(false);

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
            seedRepeaterEnableTimer->start((repeaterObject.getSeeding())*1000);
        }
    }
}

bool MainWindow::nameValidation(QString userName)
{
    userName = userName.toLower();
    bool valid = false;
    if (userName.size() <=10)
    {
        for (int i = 0; i < userName.size(); i++)
        {
            if(userName[i].isLetterOrNumber())
            {
                valid = true;
            }
            else
            {
                valid = false;
                break;
            }
        }
    }

    if (valid == true)
        return true;
    else
        return false;
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
    if (currentUserLevel == user.getLevelList(0))
    {
        zombies *RegularZombie = new zombies(2);
        scene->addItem(RegularZombie);
        qDebug() << "Zombie Added";

        if (levelOneCounter == 4)
        {
            startListSave = ((user.getIntervalList(0).toInt())*1000) - ((user.getDecrementList(0).toInt())*400);
            regularZombieTimer->stop();
            flagZombieTimer->start(startListSave);
        }
        if (levelOneCounter == 3)
        {
            startListSave = ((user.getIntervalList(0).toInt())*1000) - ((user.getDecrementList(0).toInt())*300);
            regularZombieTimer->start(startListSave);
            levelOneCounter++;
        }
        if (levelOneCounter == 2)
        {
            startListSave = ((user.getIntervalList(0).toInt())*1000) - ((user.getDecrementList(0).toInt())*200);
            regularZombieTimer->start(startListSave);
            levelOneCounter++;
        }
        if (levelOneCounter == 1)
        {
            startListSave = ((user.getIntervalList(0).toInt())*1000) - ((user.getDecrementList(0).toInt())*100);
            regularZombieTimer->start(startListSave);
            levelOneCounter++;
        }
        if (levelOneCounter == 0)
        {
            startListSave = user.getIntervalList(0).toInt();
            startListSave = startListSave * 1000;
            regularZombieTimer->start(startListSave);
            levelOneCounter++;
        }
    }

    else if (currentUserLevel == user.getLevelList(1))
    {
        zombies *RegularZombie = new zombies(1,1);
        scene->addItem(RegularZombie);
        qDebug() << "Zombie Added";
    }
    else
    {
        zombies *RegularZombie = new zombies();
        scene->addItem(RegularZombie);
        qDebug() << "Zombie Added";
    }

}

void MainWindow::createFlagZombie()
{
    flagzombies *FlagZombie = new flagzombies(2);
    scene->addItem(FlagZombie);
    qDebug() << " Flag Zombie Added";
    flagZombieTimer->stop();
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

void MainWindow::createBullet1PeaShooter()
{
    bullets *pBullets = new bullets(xPeaShooter1,yPeaShooter1);
    scene->addItem(pBullets);
    qDebug() << "Pea Shooter Bullets Added";
}

void MainWindow::createBullet2PeaShooter()
{
    bullets *aBullets = new bullets(xPeaShooter2,yPeaShooter2);
    scene->addItem(aBullets);
    qDebug() << "Pea Shooter Bullets Added";
}

void MainWindow::createBullet3PeaShooter()
{
    bullets *bBullets = new bullets(xPeaShooter3,yPeaShooter3);
    scene->addItem(bBullets);
    qDebug() << "Pea Shooter Bullets Added";
}

void MainWindow::createBullet1SnowPea()
{
    snowpeabullets *cBullets = new snowpeabullets(xSnowPea1,ySnowPea1);
    scene->addItem(cBullets);
    qDebug() << "Snow Pea Bullets Added";
}

void MainWindow::createBullet2SnowPea()
{
    snowpeabullets *dBullets = new snowpeabullets(xSnowPea2,ySnowPea2);
    scene->addItem(dBullets);
    qDebug() << "Snow Pea Bullets Added";
}

void MainWindow::createBullet3SnowPea()
{
    snowpeabullets *eBullets = new snowpeabullets(xSnowPea3,ySnowPea3);
    scene->addItem(eBullets);
    qDebug() << "Snow Pea Bullets Added";
}

void MainWindow::createSun1SunFlower()
{
    sunFlowerSuns *sun1 = new sunFlowerSuns();
    sunAdd1.push_back(sun1);
    scene->addItem(sunAdd1[0]);
    sun1->setPos(xSunFlower1,ySunFlower1);
    sunFlowerSunsDeleteTimer1->start(7500);
}

void MainWindow::createSun2SunFlower()
{
    sunFlowerSuns *sun2 = new sunFlowerSuns();
    sunAdd2.push_back(sun2);
    scene->addItem(sunAdd2[0]);
    sun2->setPos(xSunFlower2,ySunFlower2);
    sunFlowerSunsDeleteTimer2->start(7500);
}

void MainWindow::createSun3SunFlower()
{
    sunFlowerSuns *sun3 = new sunFlowerSuns();
    sunAdd3.push_back(sun3);
    scene->addItem(sunAdd3[0]);
    sun3->setPos(xSunFlower3,ySunFlower3);
    sunFlowerSunsDeleteTimer3->start(7500);
}

void MainWindow::deleteSun1SunFlower()
{
    scene->removeItem(sunAdd1[0]);
    sunAdd1.pop_back();
    qDebug() << "Sun Deleted";
    sunFlowerSunsDeleteTimer1->stop();
}

void MainWindow::deleteSun2SunFlower()
{
    scene->removeItem(sunAdd2[0]);
    sunAdd2.pop_back();
    qDebug() << "Sun Deleted";
    sunFlowerSunsDeleteTimer2->stop();
}

void MainWindow::deleteSun3SunFlower()
{
    scene->removeItem(sunAdd3[0]);
    sunAdd3.pop_back();
    qDebug() << "Sun Deleted";
    sunFlowerSunsDeleteTimer3->stop();
}

void MainWindow::plantsCostt()
{
    if (sunPointsTotal > 200 && seedRepeaterTimeoutTimer->isActive() == false)
        ui->RepeaterToolButton->setEnabled(true);

    if (sunPointsTotal < 200)
    {
        ui->RepeaterToolButton->setEnabled(false);
        if(seedSnowPeaTimeoutTimer->isActive() == false)
            ui->SnowPeaToolButton->setEnabled(true);
    }

    if (sunPointsTotal < 175)
    {
        ui->SnowPeaToolButton->setEnabled(false);
        if (seedCherryBombTimeoutTimer->isActive() == false)
            ui->CherryBombToolButton->setEnabled(true);
        if (seedChomperTimeoutTimer->isActive() == false)
            ui->ChomperToolButton->setEnabled(true);
    }

    if(sunPointsTotal < 150)
    {
        ui->CherryBombToolButton->setEnabled(false);
        ui->ChomperToolButton->setEnabled(false);
        if (seedPeaShooterTimeoutTimer->isActive() == false)
            ui->PeaShooterToolButton->setEnabled(true);
    }

    if(sunPointsTotal < 100)
    {
        ui->PeaShooterToolButton->setEnabled(false);
        if (seedSunFlowerTimeoutTimer->isActive() == false)
            ui->SunFlowerToolButton->setEnabled(true);
        if(seedWallNutTimeoutTimer->isActive() == false)
            ui->WalNutToolButton->setEnabled(true);
    }

    if(sunPointsTotal < 50)
    {
        ui->WalNutToolButton->setEnabled(false);
        ui->SunFlowerToolButton->setEnabled(false);
        if (seedPotatoMineTimeoutTimer->isActive() == false)
            ui->PotatoMineToolButton->setEnabled(true);
    }

    if(sunPointsTotal < 25)
        ui->PotatoMineToolButton->setEnabled(false);
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
    QString userNamee = (ui->NamelineEdit->text());
    if (reply == QMessageBox::Ok)
    {
//        if (user.getTotal()< 5)
//        {
        if (nameValidation(userNamee) == true)
        {
            ui->UsercomboBox->addItem(userNamee);
            QString time = QString::number(QDateTime::currentDateTime().toTime_t());
            user.addLists(time,userNamee,"1");
            user.ReadPlayers("C://Users/User/Desktop/Plants vs Zombies files/pvz_players.csv");
            user.Sort();
            ui->UserpushButton->setEnabled(true);
            ui->StartpushButton->setEnabled(true);
            ui->RestartpushButton->setEnabled(true);
            ui->DeletepushButton->setEnabled(true);
        }
//        }
//        else
//            QMessageBox::question(this,"Max 5 Users", "Maximum users reached. Delete a user before creating a new one.",
//                                  QMessageBox::Ok|QMessageBox::Cancel); //Max 5 users in csv
    } 
}

void MainWindow::on_StartpushButton_clicked()
{
    //Showing sun points
    sunPointsTotal = 2000;
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
    if(currentUserLevel == user.getLevelList(0)) //Only 1 green row and lawnmower will be shown
    {
        scene->addRect(75,0,675,75,blackPen,brown);
        scene->addRect(75,75,675,75,blackPen,brown);
        scene->addRect(75,225,675,75,blackPen,brown);
        scene->addRect(75,300,675,75,blackPen,brown);
        scene->addPixmap(LawnMower)->setOffset(0,160);
    }

    else if(currentUserLevel == user.getLevelList(1)) //Only 3 green rows and lawnmowers will be shown
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

    plantsCostTimer->start(0);

    if (currentUserLevel == user.getLevelList(0))
    {
        startListSave = user.getStartList(0).toInt();
        startListSave = startListSave*1000;
        timer->start(58);
        sunTimer->start(10000);
        regularZombieTimer->start(startListSave);
        sunPointsUpdateTimer->start(0);
    }
    else if (currentUserLevel == user.getLevelList(1))
    {
        timer->start(58);
        sunTimer->start(10000);
        regularZombieTimer->start(5000);
        sunPointsUpdateTimer->start(0);
    }
    else
    {
        timer->start(58);
        sunTimer->start(10000);
        regularZombieTimer->start(5000);
        sunPointsUpdateTimer->start(0);
    }

    //Filling grid with 0s meaning there is no plant anywhere
    for (int n=0; n < 5; n++)
        for (int m=0; m < 10; m++)
        {
          grid[n][m]=0;
        }

    //Disabling and Enabling buttons
    ui->QuitpushButton->setEnabled(true);
    ui->PeaShooterToolButton->setEnabled(true);
    ui->SunFlowerToolButton->setEnabled(true);
    ui->CherryBombToolButton->setEnabled(true);
    ui->PotatoMineToolButton->setEnabled(true);
    ui->WalNutToolButton->setEnabled(true);
    ui->ChomperToolButton->setEnabled(true);
    ui->SnowPeaToolButton->setEnabled(true);
    ui->RepeaterToolButton->setEnabled(true);
    ui->NewpushButton->setEnabled(false);
    ui->DeletepushButton->setEnabled(false);
    ui->UserpushButton->setEnabled(false);
    ui->UsercomboBox->setEnabled(false);
    ui->StartpushButton->setEnabled(false);
}

void MainWindow::on_RestartpushButton_clicked() //Game restarts
{
    if (timer->isActive() == true)
    {
        timer->stop();
        restartTimerCounters.push_back(1);
    }
    else
        restartTimerCounters.push_back(0);

    if (regularZombieTimer->isActive() == true)
    {
        regularZombieTimer->stop();
        restartTimerCounters.push_back(1);
    }
    else
        restartTimerCounters.push_back(0);

    if (flagZombieTimer->isActive() == true)
    {
        flagZombieTimer->stop();
        restartTimerCounters.push_back(1);
    }
    else
        restartTimerCounters.push_back(0);

    if (sunTimer->isActive() == true)
    {
        sunTimer->stop();
        restartTimerCounters.push_back(1);
    }
    else
        restartTimerCounters.push_back(0);

    if (peaShooterBulletsTimer1->isActive() == true)
    {
        peaShooterBulletsTimer1->stop();
        restartTimerCounters.push_back(1);
    }
    else
        restartTimerCounters.push_back(0);

    if (peaShooterBulletsTimer2->isActive() == true)
    {
        peaShooterBulletsTimer2->stop();
        restartTimerCounters.push_back(1);
    }
    else
        restartTimerCounters.push_back(0);

    if (peaShooterBulletsTimer3->isActive() == true)
    {
        peaShooterBulletsTimer3->stop();
        restartTimerCounters.push_back(1);
    }
    else
        restartTimerCounters.push_back(0);

    if (snowPeaBulletsTimer1->isActive() == true)
    {
        snowPeaBulletsTimer1->stop();
        restartTimerCounters.push_back(1);
    }
    else
        restartTimerCounters.push_back(0);

    if (snowPeaBulletsTimer2->isActive() == true)
    {
        snowPeaBulletsTimer2->stop();
        restartTimerCounters.push_back(1);
    }
    else
        restartTimerCounters.push_back(0);

    if (snowPeaBulletsTimer3->isActive() == true)
    {
        snowPeaBulletsTimer3->stop();
        restartTimerCounters.push_back(1);
    }
    else
        restartTimerCounters.push_back(0);

    if (sunFlowerSunsCreateTimer1->isActive() == true)
    {
        sunFlowerSunsCreateTimer1->stop();
        restartTimerCounters.push_back(1);
    }
    else
        restartTimerCounters.push_back(0);

    if (sunFlowerSunsCreateTimer2->isActive() == true)
    {
        sunFlowerSunsCreateTimer2->stop();
        restartTimerCounters.push_back(1);
    }
    else
        restartTimerCounters.push_back(0);

    if (sunFlowerSunsCreateTimer3->isActive() == true)
    {
        sunFlowerSunsCreateTimer3->stop();
        restartTimerCounters.push_back(1);
    }
    else
        restartTimerCounters.push_back(0);


//    QMessageBox::StandardButton reply;
//    reply = QMessageBox::question(this, "Restart", "Are you sure you want to restart this level?",
//                                    QMessageBox::Yes|QMessageBox::Cancel);
//      if (reply == QMessageBox::Yes) {

    QMessageBox msg(this);
    msg.setIconPixmap(QPixmap(":/error.svg"));
    msg.setText("Restart");
    msg.setInformativeText("Are you sure you want to restart this level?");
    msg.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msg.move((msg.width())*5,(msg.height())*10);
    QSpacerItem* horizontalSpacer = new QSpacerItem(330, 60, QSizePolicy::Minimum, QSizePolicy::Expanding);
    QGridLayout* layout = (QGridLayout*)msg.layout();
    layout->addItem(horizontalSpacer, layout->rowCount(), 5, 2, layout->columnCount());
    if(msg.exec() == QMessageBox::Ok){
        qDebug() << "Yes restart was clicked";
        {
            //Set default sun points
            sunPointsTotal = 2000;

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

            for (int i = 0; i < 13; i++)
            {
                restartTimerCounters.pop_back();
            }
        }
      } else {
        qDebug() << "Restart was *not* clicked";

        if (restartTimerCounters[0] == 1)
            timer->start();
        if (restartTimerCounters[1] == 1)
            regularZombieTimer->start();
        if (restartTimerCounters[2] == 1)
            flagZombieTimer->start();
        if (restartTimerCounters[3] == 1)
            sunTimer->start();
        if (restartTimerCounters[4] == 1)
            peaShooterBulletsTimer1->start();
        if (restartTimerCounters[5] == 1)
            peaShooterBulletsTimer2->start();
        if (restartTimerCounters[6] == 1)
            peaShooterBulletsTimer3->start();
        if (restartTimerCounters[7] == 1)
            snowPeaBulletsTimer1->start();
        if (restartTimerCounters[8] == 1)
            snowPeaBulletsTimer2->start();
        if (restartTimerCounters[9] == 1)
            snowPeaBulletsTimer3->start();
        if (restartTimerCounters[10] == 1)
            sunFlowerSunsCreateTimer1->start();
        if (restartTimerCounters[11] == 1)
            sunFlowerSunsCreateTimer2->start();
        if (restartTimerCounters[12] == 1)
            sunFlowerSunsCreateTimer3->start();

        for (int i = 0; i < 13; i++)
        {
            restartTimerCounters.pop_back();
        }
      }
}

void MainWindow::on_QuitpushButton_clicked() //Level closes when user presses Yes
{
    if (timer->isActive() == true)
    {
        timer->stop();
        restartTimerCounters.push_back(1);
    }
    else
        restartTimerCounters.push_back(0);

    if (regularZombieTimer->isActive() == true)
    {
        regularZombieTimer->stop();
        restartTimerCounters.push_back(1);
    }
    else
        restartTimerCounters.push_back(0);

    if (flagZombieTimer->isActive() == true)
    {
        flagZombieTimer->stop();
        restartTimerCounters.push_back(1);
    }
    else
        restartTimerCounters.push_back(0);

    if (sunTimer->isActive() == true)
    {
        sunTimer->stop();
        restartTimerCounters.push_back(1);
    }
    else
        restartTimerCounters.push_back(0);

    if (peaShooterBulletsTimer1->isActive() == true)
    {
        peaShooterBulletsTimer1->stop();
        restartTimerCounters.push_back(1);
    }
    else
        restartTimerCounters.push_back(0);

    if (peaShooterBulletsTimer2->isActive() == true)
    {
        peaShooterBulletsTimer2->stop();
        restartTimerCounters.push_back(1);
    }
    else
        restartTimerCounters.push_back(0);

    if (peaShooterBulletsTimer3->isActive() == true)
    {
        peaShooterBulletsTimer3->stop();
        restartTimerCounters.push_back(1);
    }
    else
        restartTimerCounters.push_back(0);

    if (snowPeaBulletsTimer1->isActive() == true)
    {
        snowPeaBulletsTimer1->stop();
        restartTimerCounters.push_back(1);
    }
    else
        restartTimerCounters.push_back(0);

    if (snowPeaBulletsTimer2->isActive() == true)
    {
        snowPeaBulletsTimer2->stop();
        restartTimerCounters.push_back(1);
    }
    else
        restartTimerCounters.push_back(0);

    if (snowPeaBulletsTimer3->isActive() == true)
    {
        snowPeaBulletsTimer3->stop();
        restartTimerCounters.push_back(1);
    }
    else
        restartTimerCounters.push_back(0);

    if (sunFlowerSunsCreateTimer1->isActive() == true)
    {
        sunFlowerSunsCreateTimer1->stop();
        restartTimerCounters.push_back(1);
    }
    else
        restartTimerCounters.push_back(0);

    if (sunFlowerSunsCreateTimer2->isActive() == true)
    {
        sunFlowerSunsCreateTimer2->stop();
        restartTimerCounters.push_back(1);
    }
    else
        restartTimerCounters.push_back(0);

    if (sunFlowerSunsCreateTimer3->isActive() == true)
    {
        sunFlowerSunsCreateTimer3->stop();
        restartTimerCounters.push_back(1);
    }
    else
        restartTimerCounters.push_back(0);

//    QMessageBox::StandardButton reply;
//    reply = QMessageBox::question(this, "Quit", "Are you sure you want to leave this level?",
//                                    QMessageBox::Yes|QMessageBox::Cancel);
//      if (reply == QMessageBox::Yes) {
//        qDebug() << "Yes quit was clicked";
//        {
//            scene->setBackgroundBrush(QBrush(Qt::white));
//            scene->clear();
//            scene->addPixmap(QPixmap("C://Users/User/Desktop/Plants vs Zombies files/plants-vs-zombies.png"))->setPos(30,0);

//            //Disabling buttons
//            ui->QuitpushButton->setEnabled(false);
//            ui->PeaShooterToolButton->setEnabled(false);
//            ui->SunFlowerToolButton->setEnabled(false);
//            ui->CherryBombToolButton->setEnabled(false);
//            ui->PotatoMineToolButton->setEnabled(false);
//            ui->WalNutToolButton->setEnabled(false);
//            ui->ChomperToolButton->setEnabled(false);
//            ui->SnowPeaToolButton->setEnabled(false);
//            ui->RepeaterToolButton->setEnabled(false);
//            ui->NewpushButton->setEnabled(true);
//            ui->DeletepushButton->setEnabled(true);
//            ui->UserpushButton->setEnabled(true);
//            ui->UsercomboBox->setEnabled(true);
//            ui->StartpushButton->setEnabled(true);

//            //Setting sun points back to 0
//            sunPointsTotal = 2000;
//            ui->Pointslabel->setText("Sun Points");

//            timer->stop();
//            sunTimer->stop();
//            regularZombieTimer->stop();
//            sunPointsUpdateTimer->stop();
//            flagZombieTimer->stop();
//            peaShooterBulletsTimer1->stop();
//            peaShooterBulletsTimer2->stop();
//            peaShooterBulletsTimer3->stop();
//            snowPeaBulletsTimer1->stop();
//            snowPeaBulletsTimer2->stop();
//            snowPeaBulletsTimer3->stop();
//            sunFlowerSunsCreateTimer1->stop();
//            sunFlowerSunsCreateTimer2->stop();
//            sunFlowerSunsCreateTimer3->stop();
//        }
//      } else {
//        qDebug() << "Yes quit was *not* clicked";
//        timer->start(58);
//        regularZombieTimer->start();
//        flagZombieTimer->start();
//        sunTimer->start();
//        peaShooterBulletsTimer1->start();
//        peaShooterBulletsTimer2->start();
//        peaShooterBulletsTimer3->start();
//        snowPeaBulletsTimer1->start();
//        snowPeaBulletsTimer2->start();
//        snowPeaBulletsTimer3->start();
//        sunFlowerSunsCreateTimer1->start();
//        sunFlowerSunsCreateTimer2->start();
//        sunFlowerSunsCreateTimer3->start();
//      }

    QMessageBox msg(this);
    msg.setIconPixmap(QPixmap(":/error.svg"));
    msg.setText("Quit");
    msg.setInformativeText("Are you sure you want to quit this level?");
    msg.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msg.move((msg.width())*5,(msg.height())*10);
    QSpacerItem* horizontalSpacer = new QSpacerItem(330, 60, QSizePolicy::Minimum, QSizePolicy::Expanding);
    QGridLayout* layout = (QGridLayout*)msg.layout();
    layout->addItem(horizontalSpacer, layout->rowCount(), 5, 2, layout->columnCount());
    if(msg.exec() == QMessageBox::Ok){
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
        ui->NewpushButton->setEnabled(true);
        ui->DeletepushButton->setEnabled(true);
        ui->UserpushButton->setEnabled(true);
        ui->UsercomboBox->setEnabled(true);
        ui->StartpushButton->setEnabled(true);

        //Setting sun points back to 0
        sunPointsTotal = 0;
        ui->Pointslabel->setText("Sun Points");

        timer->stop();
        sunTimer->stop();
        regularZombieTimer->stop();
        sunPointsUpdateTimer->stop();
        flagZombieTimer->stop();
        peaShooterBulletsTimer1->stop();
        peaShooterBulletsTimer2->stop();
        peaShooterBulletsTimer3->stop();
        snowPeaBulletsTimer1->stop();
        snowPeaBulletsTimer2->stop();
        snowPeaBulletsTimer3->stop();
        sunFlowerSunsCreateTimer1->stop();
        sunFlowerSunsCreateTimer2->stop();
        sunFlowerSunsCreateTimer3->stop();

        for (int i = 0; i < 13; i++)
        {
            restartTimerCounters.pop_back();
        }
    }

    else{
        qDebug() << "Yes quit was *not* clicked";
        if (restartTimerCounters[0] == 1)
            timer->start();
        if (restartTimerCounters[1] == 1)
            regularZombieTimer->start();
        if (restartTimerCounters[2] == 1)
            flagZombieTimer->start();
        if (restartTimerCounters[3] == 1)
            sunTimer->start();
        if (restartTimerCounters[4] == 1)
            peaShooterBulletsTimer1->start();
        if (restartTimerCounters[5] == 1)
            peaShooterBulletsTimer2->start();
        if (restartTimerCounters[6] == 1)
            peaShooterBulletsTimer3->start();
        if (restartTimerCounters[7] == 1)
            snowPeaBulletsTimer1->start();
        if (restartTimerCounters[8] == 1)
            snowPeaBulletsTimer2->start();
        if (restartTimerCounters[9] == 1)
            snowPeaBulletsTimer3->start();
        if (restartTimerCounters[10] == 1)
            sunFlowerSunsCreateTimer1->start();
        if (restartTimerCounters[11] == 1)
            sunFlowerSunsCreateTimer2->start();
        if (restartTimerCounters[12] == 1)
            sunFlowerSunsCreateTimer3->start();

        for (int i = 0; i < 13; i++)
        {
            restartTimerCounters.pop_back();
        }
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

    //Making buttons look selected/unselected
    ui->PeaShooterToolButton->setPalette(QPalette(Qt::blue));
    ui->PeaShooterToolButton->setAutoFillBackground(true);

    ui->SunFlowerToolButton->setAutoFillBackground(false);
    ui->CherryBombToolButton->setAutoFillBackground(false);
    ui->WalNutToolButton->setAutoFillBackground(false);
    ui->PotatoMineToolButton->setAutoFillBackground(false);
    ui->SnowPeaToolButton->setAutoFillBackground(false);
    ui->ChomperToolButton->setAutoFillBackground(false);
    ui->RepeaterToolButton->setAutoFillBackground(false);
}

void MainWindow::on_SunFlowerToolButton_clicked()
{
    plant_ID = 2;

    //Making buttons look selected/unselected
    ui->SunFlowerToolButton->setPalette(QPalette(Qt::blue));
    ui->SunFlowerToolButton->setAutoFillBackground(true);

    ui->PeaShooterToolButton->setAutoFillBackground(false);
    ui->CherryBombToolButton->setAutoFillBackground(false);
    ui->WalNutToolButton->setAutoFillBackground(false);
    ui->PotatoMineToolButton->setAutoFillBackground(false);
    ui->SnowPeaToolButton->setAutoFillBackground(false);
    ui->ChomperToolButton->setAutoFillBackground(false);
    ui->RepeaterToolButton->setAutoFillBackground(false);

}

void MainWindow::on_CherryBombToolButton_clicked()
{
    plant_ID = 3;

    //Making buttons look selected/unselected
    ui->CherryBombToolButton->setPalette(QPalette(Qt::blue));
    ui->CherryBombToolButton->setAutoFillBackground(true);

    ui->SunFlowerToolButton->setAutoFillBackground(false);
    ui->PeaShooterToolButton->setAutoFillBackground(false);
    ui->WalNutToolButton->setAutoFillBackground(false);
    ui->PotatoMineToolButton->setAutoFillBackground(false);
    ui->SnowPeaToolButton->setAutoFillBackground(false);
    ui->ChomperToolButton->setAutoFillBackground(false);
    ui->RepeaterToolButton->setAutoFillBackground(false);
}

void MainWindow::on_WalNutToolButton_clicked()
{
    plant_ID = 4;

    //Making buttons look selected/unselected
    ui->WalNutToolButton->setPalette(QPalette(Qt::blue));
    ui->WalNutToolButton->setAutoFillBackground(true);

    ui->SunFlowerToolButton->setAutoFillBackground(false);
    ui->PeaShooterToolButton->setAutoFillBackground(false);
    ui->CherryBombToolButton->setAutoFillBackground(false);
    ui->PotatoMineToolButton->setAutoFillBackground(false);
    ui->SnowPeaToolButton->setAutoFillBackground(false);
    ui->ChomperToolButton->setAutoFillBackground(false);
    ui->RepeaterToolButton->setAutoFillBackground(false);
}

void MainWindow::on_PotatoMineToolButton_clicked()
{
    plant_ID = 5;

    //Making buttons look selected/unselected
    ui->PotatoMineToolButton->setPalette(QPalette(Qt::blue));
    ui->PotatoMineToolButton->setAutoFillBackground(true);

    ui->SunFlowerToolButton->setAutoFillBackground(false);
    ui->PeaShooterToolButton->setAutoFillBackground(false);
    ui->CherryBombToolButton->setAutoFillBackground(false);
    ui->WalNutToolButton->setAutoFillBackground(false);
    ui->SnowPeaToolButton->setAutoFillBackground(false);
    ui->ChomperToolButton->setAutoFillBackground(false);
    ui->RepeaterToolButton->setAutoFillBackground(false);

}

void MainWindow::on_SnowPeaToolButton_clicked()
{
    plant_ID = 6;

    //Making buttons look selected/unselected
    ui->SnowPeaToolButton->setPalette(QPalette(Qt::blue));
    ui->SnowPeaToolButton->setAutoFillBackground(true);

    ui->SunFlowerToolButton->setAutoFillBackground(false);
    ui->PeaShooterToolButton->setAutoFillBackground(false);
    ui->CherryBombToolButton->setAutoFillBackground(false);
    ui->WalNutToolButton->setAutoFillBackground(false);
    ui->PotatoMineToolButton->setAutoFillBackground(false);
    ui->ChomperToolButton->setAutoFillBackground(false);
    ui->RepeaterToolButton->setAutoFillBackground(false);
}

void MainWindow::on_ChomperToolButton_clicked()
{
    plant_ID = 7;

    //Making buttons look selected/unselected
    ui->ChomperToolButton->setPalette(QPalette(Qt::blue));
    ui->ChomperToolButton->setAutoFillBackground(true);

    ui->SunFlowerToolButton->setAutoFillBackground(false);
    ui->PeaShooterToolButton->setAutoFillBackground(false);
    ui->CherryBombToolButton->setAutoFillBackground(false);
    ui->WalNutToolButton->setAutoFillBackground(false);
    ui->PotatoMineToolButton->setAutoFillBackground(false);
    ui->SnowPeaToolButton->setAutoFillBackground(false);
    ui->RepeaterToolButton->setAutoFillBackground(false);
}

void MainWindow::on_RepeaterToolButton_clicked()
{
    plant_ID = 8;

    //Making buttons look selected/unselected
    ui->RepeaterToolButton->setPalette(QPalette(Qt::blue));
    ui->RepeaterToolButton->setAutoFillBackground(true);

    ui->SunFlowerToolButton->setAutoFillBackground(false);
    ui->PeaShooterToolButton->setAutoFillBackground(false);
    ui->CherryBombToolButton->setAutoFillBackground(false);
    ui->WalNutToolButton->setAutoFillBackground(false);
    ui->PotatoMineToolButton->setAutoFillBackground(false);
    ui->SnowPeaToolButton->setAutoFillBackground(false);
    ui->ChomperToolButton->setAutoFillBackground(false);
}
