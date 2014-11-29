#ifndef SNOWPEABULLETS_H
#define SNOWPEABULLETS_H

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
#include <QColor>

class snowpeabullets : public QGraphicsItem
{
public:
    snowpeabullets();
    snowpeabullets(int,int);
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

#endif // SNOWPEABULLETS_H
