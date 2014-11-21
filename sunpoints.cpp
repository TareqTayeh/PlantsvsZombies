#include "sunpoints.h"

sunpoints::sunpoints()
{
    yCoordinate = 0;
    yVelocity = 1.1;
    random = 0;
    random1 = 0;
}

void sunpoints::advance(int phase)
{
    if(!phase) return;  // We don't do anything to prepare objects for advancing
    move(1.3);
    QPointF p = this->pos();    // current position
    qDebug() << p;

    // Check boundaries (0,0)-(WIDTH,WIDTH)
    if (y() < (1) || y() > (310)) // make the sun dissapear
    {
       setYVelocity(0);
    }

    setPos(400, y()); // move based on velocity
}

void sunpoints::setPos(int x, int y) // sets the position (meters)
{
    setOffset(x,y);
}

void sunpoints::move(double time) // sets current position based on previous position, velocity, and time
{
    yCoordinate = yCoordinate + ( yVelocity * time);
}

void sunpoints::setYVelocity(double v)
{
    yVelocity = v;
}

void sunpoints::setXVelocity(double v)
{
    xVelocity = v;
}

int sunpoints::x() const
{
    return xCoordinate;
}

int sunpoints::y() const
{
    return yCoordinate;
}

int sunpoints::randomValue()
{
    srand(time(NULL));
    random = (rand()%675) + 75;
    return random;
}
