#ifndef ZOMBIES_H
#define ZOMBIES_H

#include <QGraphicsPixmapItem>
#include <QDebug>
#include <ctime>

class zombies : public QGraphicsPixmapItem
{
public:
    zombies();
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

#endif // ZOMBIES_H
