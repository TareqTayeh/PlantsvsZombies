#ifndef ZOMBIES_H
#define ZOMBIES_H

#include "plants.h"
#include "QTime"
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QDebug>
#include <ctime>
#include <QPainter>
#include <QGraphicsScene>
#include <QRect>
#include <QObjectList>

class zombies : public QGraphicsItem
{
public:
    zombies();
    zombies(int);
    zombies(int,int);
    QPixmap zombie;
    QPixmap zombieEating;
    void advance(int phase);
    void move(double time);
    double xVelocity;
    double yVelocity;
    void setXVelocity(double);
    void setYVelocity(double);
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

protected:
    int xCoordinate;
    int yCoordinate;
    int random;
    int random1;
    int random2;
    double direction;
};

class flagzombies : public zombies
{
public:
    flagzombies();
    flagzombies(int);
    flagzombies(int,int);
};

#endif // ZOMBIES_H
