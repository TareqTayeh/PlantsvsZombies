#ifndef ZOMBIES_H
#define ZOMBIES_H

#include "plants.h"
#include "QTime"
#include "lawnmowers.h"
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QDebug>
#include <ctime>
#include <QPainter>
#include <QGraphicsScene>
#include <QRect>
#include <QObjectList>
#include <QTime>
#include <QPixmap>
#include <QMessageBox>
#include <QSpacerItem>
#include <QGridLayout>

class zombies : public QGraphicsItem
{
public:
    zombies();
    zombies(int);
    zombies(int,int);
    QPixmap zombie;
    QPixmap theEnd;
    void advance(int phase);
    void move(double time);
    double speed;
    void setXVelocity(double);
    int x() const;
    int y() const;
    int randomValue();
    int randomValue2();
    int stop[5][10];
    void setStopValue(int, int);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    int getLife();
    int life;
    QTime rateT;
    int restartLevel();

protected:
    int xCoordinate;
    int yCoordinate;
    int random;
    int random1;
    int random2;
    double direction;
    int restartL;
};

class flagzombies : public zombies
{
public:
    flagzombies();
    flagzombies(int);
    flagzombies(int,int);
};

class coneheadzombies : public zombies
{
public:
    coneheadzombies();
    coneheadzombies(int,int);
};

class bucketheadzombies : public zombies
{
public:
    bucketheadzombies();
};

class newspaperzombies : public zombies
{
public:
    newspaperzombies();
};

#endif // ZOMBIES_H
