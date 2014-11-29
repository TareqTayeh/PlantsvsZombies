#ifndef BULLETS_H
#define BULLETS_H

#include "zombies.h"
#include "plants.h"
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QDebug>
#include <ctime>
#include <QPainter>
#include <QGraphicsScene>
#include <QRect>
#include <ctime>

class bullets : public QGraphicsItem
{
public:
    bullets();
    bullets(int,int);
    void advance(int phase);
    void move(double time);
    double xVelocity;
    double yVelocity;
    void setXVelocity(double);
    void setYVelocity(double);
    int x() const;
    int y() const;
    int randomValue();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

private:
    int xCoordinate;
    int yCoordinate;
    int random;
    int random1;
    double direction;
};

#endif // BULLETS_H
