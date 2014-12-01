#ifndef LAWNMOWERS_H
#define LAWNMOWERS_H

#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QDebug>

class lawnmowers : public QGraphicsPixmapItem
{
public:
    lawnmowers();

private:
    int xCoordinate;
    double speed;
};

#endif // LAWNMOWERS_H
