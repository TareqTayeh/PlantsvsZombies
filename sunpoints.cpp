#include "sunpoints.h"

sunpoints::sunpoints()
{
    srand(time(NULL));
    yCoordinate = 0;
    yVelocity = 1.1;
    random = 0;
    random1 = randomValueY();
    random2 = randomValueX();
    this->setPos(0,0);

    //Adding sun(testing)
    Sun.load("C://Users/User/Desktop/Plants vs Zombies files/Sun.png");
}

void sunpoints::advance(int phase)
{
    if(!phase) return;  // We don't do anything to prepare objects for advancing
    move(1.3);
    //QPointF p = this->pos();    // current position
    //qDebug() << p;

    // Check boundaries (0,0)-(WIDTH,WIDTH)
    if (y() > ((random1))) // make the sun stop
    {
       setYVelocity(0);
    }

    setPos(random2, y()); // move based on velocity
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

int sunpoints::randomValueX()
{
    random = (rand()%675) + 75;
    return random;
}

int sunpoints::randomValueY()
{
    random = (rand()%315);
    return random;
}

QRectF sunpoints::boundingRect() const
{
    return QRectF(0,0,Sun.width(),Sun.height());
}

void sunpoints::mousePressEvent(QGraphicsSceneMouseEvent *e)
{
    //emit mouse();
    Position = e->pos();
    delete this;
    qDebug() << "Sunclicked";
    qDebug() << endl << Position.x();
}

void sunpoints::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawPixmap(boundingRect(),Sun,boundingRect());
}
