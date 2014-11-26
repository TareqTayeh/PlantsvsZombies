#ifndef ZOMBIES_H
#define ZOMBIES_H

#include <QGraphicsPixmapItem>
#include <QDebug>
#include <ctime>

class zombies : public QGraphicsPixmapItem
{
public:
    zombies();
    zombies(int);
    zombies(int,int);
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
    int randomValue2();

private:
    int xCoordinate;
    int yCoordinate;
    int random;
    int random1;
    int random2;
    double direction;
};

#endif // ZOMBIES_H
