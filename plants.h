#ifndef PLANTS_H
#define PLANTS_H

#include "bullets.h"
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QTime>
#include <QGraphicsScene>

class plants : public QGraphicsPixmapItem
{
public:
    plants();
    void setLife(double);
    double getLife();
    int getPlantID();
    int getCost();
    int getDamage();
    double getSeeding();
    double getRate();

protected:
    int cost;
    double life;
    int range;
    int damage;
    double rate;
    int splash;
    int slow;
    int bomb;
    double seeding;
    int sun;
    int need;
    int plantID;
};

class PeaShooterClass  : public plants
{
public:
    PeaShooterClass();
    PeaShooterClass(int,int);
    void startBulletsTimer(int,int);
};

class SunFlowerClass : public plants
{
public:
    SunFlowerClass();
    SunFlowerClass(int,int);
};

class CherryBombClass : public plants
{
public:
    CherryBombClass();
};

class WallNutClass : public plants
{
public:
    WallNutClass();
};

class PotatoMineClass : public plants
{
public:
    PotatoMineClass();
};

class SnowPeaClass : public plants
{
public:
    SnowPeaClass();
};

class ChomperClass : public plants
{
public:
    ChomperClass();
};

class RepeaterClass : public plants
{
public:
    RepeaterClass();
};

#endif // PLANTS_H
