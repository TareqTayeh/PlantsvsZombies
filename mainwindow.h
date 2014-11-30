#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "readingcsvfiles.h"
#include "plants.h"
#include "sunpoints.h"
#include "zombies.h"
#include "bullets.h"
#include "snowpeabullets.h"
#include "sunflowersuns.h"
#include <QGraphicsItem>
#include <QMainWindow>
#include <QMessageBox>
#include <QDebug>
#include <QFile>
#include <QPixmap>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QIcon>
#include <QToolButton>
#include <QToolTip>
#include <string>
#include <QGraphicsPixmapItem>
#include <ctime>
#include <QTimer>
#include <QValidator>
#include <QVector>
#include <QFile>
#include <QDir>
#include <QSpacerItem>
#include <QGridLayout>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setPictures();
    QString textSearch;
    void drawRect(int,int);
    void drawPeaShooter(int,int);
    void drawSunFlower(int,int);
    void drawCherryBomb(int,int);
    void drawWalNut(int,int);
    void drawPotatoMine(int,int);
    void drawSnowPea(int,int);
    void drawChomper(int,int);
    void drawRepeater(int,int); 
    sunpoints *sunUpdate;
    zombies *zombieStop;
    bool nameValidation(QString);

public slots:
    void updateSunpoints();
    void createSun();
    void deleteSun();
    void createRegularZombie();
    void createFlagZombie();
    void seedPeaShooterTimeout();
    void seedPeaShooterEnable();
    void seedSunFlowerTimeout();
    void seedSunFlowerEnable();
    void seedCherryBombTimeout();
    void seedCherryBombEnable();
    void seedWallNutTimeout();
    void seedWallNutEnable();
    void seedPotatoMineTimeout();
    void seedPotatoMineEnable();
    void seedSnowPeaTimeout();
    void seedSnowPeaEnable();
    void seedChomperTimeout();
    void seedChomperEnable();
    void seedRepeaterTimeout();
    void seedRepeaterEnable();
    void createBullet1PeaShooter();
    void createBullet2PeaShooter();
    void createBullet3PeaShooter();
    void createBullet1SnowPea();
    void createBullet2SnowPea();
    void createBullet3SnowPea();
    void createSun1SunFlower();
    void createSun2SunFlower();
    void createSun3SunFlower();
    void deleteSun1SunFlower();
    void deleteSun2SunFlower();
    void deleteSun3SunFlower();
    void plantsCostt();

private slots:
    void on_DeletepushButton_clicked();

    void on_NewpushButton_clicked();

    void on_StartpushButton_clicked();

    void on_RestartpushButton_clicked();

    void on_QuitpushButton_clicked();

    void on_UserpushButton_clicked();

    void on_PeaShooterToolButton_clicked();

    void on_SunFlowerToolButton_clicked();

    void on_CherryBombToolButton_clicked();

    void on_WalNutToolButton_clicked();

    void on_PotatoMineToolButton_clicked();

    void on_SnowPeaToolButton_clicked();

    void on_ChomperToolButton_clicked();

    void on_RepeaterToolButton_clicked();

private:
    Ui::MainWindow *ui;
    QString currentUserName;
    QString currentUserTime;
    QString currentUserLevel;
    QGraphicsScene *scene;
    QTimer *timer;
    QTimer *regularZombieTimer;
    QTimer *flagZombieTimer;
    QTimer *sunTimer;
    QTimer *seedPeaShooterTimeoutTimer;
    QTimer *seedPeaShooterEnableTimer;
    QTimer *seedSunFlowerTimeoutTimer;
    QTimer *seedSunFlowerEnableTimer;
    QTimer *seedCherryBombTimeoutTimer;
    QTimer *seedCherryBombEnableTimer;
    QTimer *seedWallNutTimeoutTimer;
    QTimer *seedWallNutEnableTimer;
    QTimer *seedPotatoMineTimeoutTimer;
    QTimer *seedPotatoMineEnableTimer;
    QTimer *seedSnowPeaTimeoutTimer;
    QTimer *seedSnowPeaEnableTimer;
    QTimer *seedChomperTimeoutTimer;
    QTimer *seedChomperEnableTimer;
    QTimer *seedRepeaterTimeoutTimer;
    QTimer *seedRepeaterEnableTimer;
    QTimer *sunDeleteTimer;
    QTimer *sunPointsUpdateTimer;
    QTimer *peaShooterBulletsTimer1;
    QTimer *peaShooterBulletsTimer2;
    QTimer *peaShooterBulletsTimer3;
    QTimer *snowPeaBulletsTimer1;
    QTimer *snowPeaBulletsTimer2;
    QTimer *snowPeaBulletsTimer3;
    QTimer *sunFlowerSunsCreateTimer1;
    QTimer *sunFlowerSunsCreateTimer2;
    QTimer *sunFlowerSunsCreateTimer3;
    QTimer *sunFlowerSunsDeleteTimer1;
    QTimer *sunFlowerSunsDeleteTimer2;
    QTimer *sunFlowerSunsDeleteTimer3;
    QTimer *plantsCostTimer;
    int timeoutTime;
    int squareSize;
    int plant_ID;
    QString cost;
    std::vector <sunpoints*> sunAdd;
    std::vector <sunFlowerSuns*> sunAdd1;
    std::vector <sunFlowerSuns*> sunAdd2;
    std::vector <sunFlowerSuns*> sunAdd3;
    std::vector <int> restartTimerCounters;
    int sunPointsTotal;
    int grid[5][10];
    int startListSave;
    int levelOneCounter;
    int xPeaShooter1;
    int yPeaShooter1;
    int xPeaShooter2;
    int yPeaShooter2;
    int xPeaShooter3;
    int yPeaShooter3;
    int xSnowPea1;
    int ySnowPea1;
    int xSnowPea2;
    int ySnowPea2;
    int xSnowPea3;
    int ySnowPea3;
    int xSunFlower1;
    int ySunFlower1;
    int xSunFlower2;
    int ySunFlower2;
    int xSunFlower3;
    int ySunFlower3;
    static int peaShooterCounter;
    static int snowPeaCounter;
    static int sunFlowerCounter;
};

#endif // MAINWINDOW_H
