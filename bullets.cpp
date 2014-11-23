#include "bullets.h"

bullets::bullets()
{
    xCoordinate = 75;
    xVelocity = 1.1;
    random = 0;
    random1 = 0;
}

void bullets::advance(int phase)
{
    if(!phase) return;  // We don't do anything to prepare objects for advancing
    move(6.5);
    //QPointF p = this->pos();    // current position
    //qDebug() << p;

    // Check boundaries (0,0)-(WIDTH,WIDTH)
    if (x() < (50) || x() > (670)) // make the bullet dissapear
    {
       setPos(150,150);
       setXVelocity(0);
       setVisible(false);
    }

    setPos(x(), 150); // move based on velocity
}

void bullets::setPos(int x, int y) // sets the position (meters)
{
    setOffset(x,y);
}

void bullets::move(double time) // sets current position based on previous position, velocity, and time
{
    xCoordinate = xCoordinate + ( xVelocity * time);
}

void bullets::setYVelocity(double v)
{
    yVelocity = v;
}

void bullets::setXVelocity(double v)
{
    xVelocity = v;
}

int bullets::x() const
{
    return xCoordinate;
}

int bullets::y() const
{
    return yCoordinate;
}

int bullets::randomValue()
{
    srand(time(NULL));
    random = (rand()%675) + 75;
    return random;
}
