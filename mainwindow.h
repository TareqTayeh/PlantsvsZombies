#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "readingcsvfiles.h"
#include "plants.h"
#include "sunpoints.h"
#include "zombies.h"
#include "bullets.h"
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
    void createBullet1();
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
    QTimer *bulletsTimer1;
    QTimer *plantsCostTimer;
    int timeoutTime;
    int squareSize;
    int plant_ID;
    QString cost;
    std::vector <sunpoints*> sunAdd;
    int sunPointsTotal;
    int grid[5][10];
    int startListSave;
    int levelOneCounter;
    int xC1;
    int yC1;
};

#endif // MAINWINDOW_H
