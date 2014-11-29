#include "zombies.h"

zombies::zombies()
{
    xCoordinate = 680;
    xVelocity = 1.1;
    random = 0;
    random1 = (randomValue()*75);
    random2 = 0;

    zombie.load("C://Users/User/Desktop/Plants vs Zombies files/PVZ_Zombie_Suit.png");
    life = 10;
}

zombies::zombies(int x) //User Level 1 (x is 2)
{
    xCoordinate = 680;
    xVelocity = 1.1;
    random = 0;
    random1 = x*75;
    random2 = 0;

    zombie.load("C://Users/User/Desktop/Plants vs Zombies files/PVZ_Zombie_Suit.png");
    zombieEating.load("C://Users/User/Desktop/Plants vs Zombies files/zombie3.png");
    this->setPos(680,180);
    life = 10;
}

zombies::zombies(int x, int y) // User Level 2 (x is 1,2 or 3)
{
    xCoordinate = 680;
    xVelocity = 1.1;
    random = 0;
    random1 = (randomValue2()*75);
    random2 = 0;

    zombie.load("C://Users/User/Desktop/Plants vs Zombies files/PVZ_Zombie_Suit.png");
    life = 10;
}

void zombies::advance(int phase)
{
    if(!phase) return;  // We don't do anything to prepare objects for advancing
    move(1);

    // Check boundaries (0,0)-(WIDTH,WIDTH)
    if (x() < (75) || x() > (750)) // make the zombie dissapear
    {
       setXVelocity(0);
    }
    //Check boundaries of zombies when plants are placed


    setPos(x(), random1); // move based on velocity
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
    random = (rand()%5);
    return random;
}

int zombies::randomValue2()
{
    srand(time(NULL));
    random = (rand()%3)+1;
    return random;
}

void zombies::setStopValue(int a, int b)
{
    stop[a][b] = 1;
}

void zombies::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QList<QGraphicsItem *> list = collidingItems() ;

    foreach(QGraphicsItem * i , list)
    {
        PeaShooterClass * item= dynamic_cast<PeaShooterClass *>(i);
        if (item)
        {
            setXVelocity(0);
            //item->setLife(item->getLife() - 1);
            qDebug() << item->getLife();
            if(item->getLife() == 0)
            {
                delete item;
                setXVelocity(1.1);
            }
        }
    }

    foreach(QGraphicsItem * j , list)
    {
        SnowPeaClass * item1 = dynamic_cast<SnowPeaClass *>(j);
        if (item1)
        {
            setXVelocity(0);
            //item->setLife(item->getLife() - 1);
            qDebug() << item1->getLife();
            if(item1->getLife() == 0)
            {
                delete item1;
                setXVelocity(1.1);
            }
        }
    }

    foreach(QGraphicsItem * h , list)
    {
        SunFlowerClass * item2 = dynamic_cast<SunFlowerClass *>(h);
        if (item2)
        {
            setXVelocity(0);
            //item->setLife(item->getLife() - 1);
            qDebug() << item2->getLife();
            if(item2->getLife() == 0)
            {
                delete item2;
                setXVelocity(1.1);
            }
        }
    }

    painter->drawPixmap(boundingRect(),zombie,boundingRect());
}

QRectF zombies::boundingRect() const
{
    return QRectF(0,0,zombie.width(),zombie.height());
}

int zombies::getLife()
{
    return life;
}


flagzombies::flagzombies()
{

}

flagzombies::flagzombies(int x)
{
    xCoordinate = 680;
    xVelocity = 1.1;
    random = 0;
    random1 = x*75;
    random2 = 0;

    zombie.load("C://Users/User/Desktop/Plants vs Zombies files/zombie2.png");
    this->setPos(680,180);
    life = 10;
}

flagzombies::flagzombies(int x, int y)
{

}
