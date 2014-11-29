#include "plants.h"

plants::plants()
{
    cost = 0;
    life = 0;
    range = 0;
    damage = 0;
    rate = 0;
    splash = 0;
    slow = 0;
    bomb = 0;
    seeding = 0;
    sun = 0;
    need = 0;
    plantID = 0;
}

void plants::setLife(double x)
{
    life = x;
}

double plants::getLife()
{
    return life;
}

int plants::getPlantID()
{
    return plantID;
}

int plants::getCost()
{
    return cost;
}

int plants::getDamage()
{
    return damage;
}

double plants::getSeeding()
{
    return seeding;
}

double plants::getRate()
{
    return rate;
}

PeaShooterClass::PeaShooterClass()
{
    cost = 100;
    life = 4;
    range = 9999;
    damage = 1;
    rate = 1.5;
    splash = 0;
    bomb = 0;
    seeding = 7.5;
    sun = 0;
    need = 0;
    plantID = 1;
}

PeaShooterClass::PeaShooterClass(int xC1, int yC1)
{
    cost = 100;
    life = 4;
    range = 9999;
    damage = 5;
    rate = 1.5;
    splash = 0;
    bomb = 0;
    seeding = 7.5;
    sun = 0;
    need = 0;
    plantID = 1;

    //bullets *pBullets = new bullets(xC1,yC1);
    //scene()->addItem(pBullets);
    //qDebug() << "Bullets Added";

    //startBulletsTimer(xC1,yC1);
}

void PeaShooterClass::startBulletsTimer(int xC1, int yC1)
{
    QTime t;
    t.start();
    if (t.elapsed() >= 0)
    {
        bullets *pBullets = new bullets(xC1,yC1);
        scene()->addItem(pBullets);
        qDebug() << "Bullets Added";
        t.restart();
    }
}


SunFlowerClass::SunFlowerClass()
{
    cost = 50;
    life = 4;
    range = 0;
    damage = 0;
    rate = 24;
    splash = 0;
    slow = 0;
    bomb = 0;
    seeding = 7.5;
    sun = 1;
    need = 0;
    plantID = 2;
}

CherryBombClass::CherryBombClass()
{
    cost = 150;
    life = 9999;
    range = 1;
    damage = 90;
    rate = 1;
    splash = 3;
    slow = 0;
    bomb = 1;
    seeding = 50;
    sun = 0;
    need = 0;
    plantID = 3;
}

WallNutClass::WallNutClass()
{
    cost = 50;
    life = 72;
    range = 0;
    damage = 0;
    rate = 0;
    splash = 0;
    slow = 0;
    bomb = 0;
    seeding = 30;
    sun = 0;
    need = 0;
    plantID = 4;
}

PotatoMineClass::PotatoMineClass()
{
    cost = 25;
    life = 4;
    range = 1;
    damage = 90;
    rate = 15;
    splash = 0;
    slow = 0;
    bomb = 1;
    seeding = 30;
    sun = 0;
    need = 0;
    plantID = 5;
}

SnowPeaClass::SnowPeaClass()
{
    cost = 175;
    life = 4;
    range = 9999;
    damage = 1;
    rate = 1.5;
    splash = 0;
    slow = 1;
    bomb = 0;
    seeding = 7.5;
    sun = 0;
    need = 0;
    plantID = 6;
}

ChomperClass::ChomperClass()
{
    cost = 150;
    life = 4;
    range = 1;
    damage = 150;
    rate = 42;
    splash = 0;
    slow = 0;
    bomb = 0;
    seeding = 7.5;
    sun = 0;
    need = 0;
    plantID = 7;
}

RepeaterClass::RepeaterClass()
{
    cost = 200;
    life = 4;
    range = 9999;
    damage = 2;
    rate = 1.5;
    splash = 0;
    slow = 0;
    bomb = 0;
    seeding = 7.5;
    sun = 0;
    need = 1;
    plantID = 8;
}
