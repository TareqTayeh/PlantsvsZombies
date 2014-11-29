#include "sunpoints.h"

int sunpoints::testing = 0;

sunpoints::sunpoints()
{
    srand(time(NULL));
    yCoordinate = 0;
    yVelocity = 1.1;
    random = 0;
    random1 = randomValueY();
    random2 = randomValueX();
    //this->setPos(0,0);

    //Adding sun(testing)
    Sun.load("C://Users/User/Desktop/Plants vs Zombies files/Sun.png");
    isClicked = false;
}

void sunpoints::advance(int phase)
{
    if(!phase) return;  // We don't do anything to prepare objects for advancing
    move(2.8);
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
    if (random > 700)
    {
        random = random - 70;
    }
    return random;
}

int sunpoints::randomValueY()
{
    random = (rand()%215);
    return random;
}

QRectF sunpoints::boundingRect() const
{
    return QRectF(0,0,Sun.width(),Sun.height());
}

void sunpoints::mousePressEvent(QGraphicsSceneMouseEvent *e)
{
    //emit mouse();
    //main_window->updateSunpoints();
    isClicked = true;
    Position = e->pos();
    testing++;
    delete this;
    qDebug() << "Sunclicked";
    qDebug() << endl << Position.x();
}

void sunpoints::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawPixmap(boundingRect(),Sun,boundingRect());
}

int sunpoints::addSunPoints()
{
    //qDebug() << testing;
    if (testing == 1)
    {
        testing = 0;
        return 25;
    }

}

