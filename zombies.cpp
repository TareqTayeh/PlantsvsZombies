#include "zombies.h"

zombies::zombies()
{
    xCoordinate = 680;
    xVelocity = 1.1;
    random = 0;
    random1 = 0;
}

void zombies::advance(int phase)
{
    if(!phase) return;  // We don't do anything to prepare objects for advancing
    move(0.6);
    //QPointF p = this->pos();    // current position
    //qDebug() << p;

    // Check boundaries (0,0)-(WIDTH,WIDTH)
    if (x() < (75) || x() > (750)) // make the zombie dissapear
    {
       setPixmap(QPixmap("C://Users/User/Desktop/Plants vs Zombies files/pvz8.png"));
       setPos(150,150);
       setXVelocity(0);
    }

    setPos(x(), 120); // move based on velocity
}

void zombies::setPos(int x, int y) // sets the position (meters)
{
    setOffset(x,y);
}

void zombies::move(double time) // sets current position based on previous position, velocity, and time
{
    xCoordinate = xCoordinate - ( xVelocity * time);
}

void zombies::setYVelocity(double v)
{
    yVelocity = v;
}

void zombies::setXVelocity(double v)
{
    xVelocity = v;
}

int zombies::x() const
{
    return xCoordinate;
}

int zombies::y() const
{
    return yCoordinate;
}

int zombies::randomValue()
{
    srand(time(NULL));
    random = (rand()%675) + 75;
    return random;
}
