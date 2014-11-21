#ifndef SUNPOINTS_H
#define SUNPOINTS_H

#include <QGraphicsPixmapItem>
#include <cmath>
#include <iostream>
#include <QDebug>
#include <ctime>

class sunpoints : public QGraphicsPixmapItem
{
public:
    sunpoints();
    void advance(int phase);
    void move(double time);
    void setPos(int,int);
    double xVelocity;
    double yVelocity;
    void setXVelocity(double);
    void setYVelocity(double);
    int x() const;
    int y() const;
    int randomValue();

private:
    int xCoordinate;
    int yCoordinate;
    int random;
    int random1;
    double direction;
};

#endif // SUNPOINTS_H
