#include "snowpeabullets.h"

snowpeabullets::snowpeabullets()
{
    xCoordinate = 75;
    xVelocity = 1.1;
    random = 0;
    random1 = 0;
}

snowpeabullets::snowpeabullets(int x, int y)
{
    xCoordinate = x;
    yCoordinate = y;
    xVelocity = 1.1;
    random = 0;
    random1 = 0;
}

void snowpeabullets::advance(int phase)
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

    setPos(x(), yCoordinate); // move based on velocity
}

void snowpeabullets::move(double time) // sets current position based on previous position, velocity, and time
{
    xCoordinate = xCoordinate + ( xVelocity * time);
}

void snowpeabullets::setYVelocity(double v)
{
    yVelocity = v;
}

void snowpeabullets::setXVelocity(double v)
{
    xVelocity = v;
}

int snowpeabullets::x() const
{
    return xCoordinate;
}

int snowpeabullets::y() const
{
    return yCoordinate;
}

int snowpeabullets::randomValue()
{
    srand(time(NULL));
    random = (rand()%675) + 75;
    return random;
}

void snowpeabullets::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QList<QGraphicsItem *> list = collidingItems() ;

    foreach(QGraphicsItem * i , list)
    {
        zombies * item = dynamic_cast<zombies *>(i);
        if (item)
        {
            setXVelocity(0);
            setVisible(false);
            item->life = item->getLife() - 1;
            item->speed = (item->speed)*0.5;
            if (item->life <= 0)
                delete item;
        }
    }

    QPen pen(Qt::blue, 1);
    painter->setPen(pen);
    QBrush b(QColor(102,255,255));
    painter->setBrush(b);
    painter->drawEllipse(boundingRect());
}


QRectF snowpeabullets::boundingRect() const
{
    return QRectF(0,0,20,20);
}
