#ifndef BULLETS_H
#define BULLETS_H

#include <QGraphicsPixmapItem>
#include <ctime>

class bullets : public QGraphicsPixmapItem
{
public:
    bullets();
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

#endif // BULLETS_H
