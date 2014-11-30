#include "zombies.h"

zombies::zombies()
{
    xCoordinate = 680;
    speed = 1.1;
    random = 0;
    random1 = (randomValue()*75);
    random2 = 0;

    zombie.load("C://Users/User/Desktop/Plants vs Zombies files/PVZ_Zombie_Suit.png");
    life = 10;
}

zombies::zombies(int x) //User Level 1 (x is 2)
{
    xCoordinate = 680;
    speed = 1.1;
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
    speed = 1.1;
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


    setPos(x(), (random1)+5); // move based on velocity
}

void zombies::move(double time) // sets current position based on previous position, velocity, and time
{
    xCoordinate = xCoordinate - ( speed * time);
}

void zombies::setXVelocity(double v)
{
    speed = v;
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
            item->setLife(item->getLife() - 1);
            qDebug() << item->getLife();
            if(item->getLife() <= 0)
            {
                //delete item;
                item->setVisible(false);
                item = NULL;
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
            item1->setLife(item1->getLife() - 0.1);
            qDebug() << item1->getLife();
            if(item1->getLife() <= 0)
            {
                //delete item1;
                item1->setVisible(false);
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
            item2->setLife(item2->getLife() - 2);
            qDebug() << item2->getLife();
            if(item2->getLife() <= 0)
            {
                item2->setVisible(false);
                //delete item2;
                setXVelocity(1.1);
            }
        }
    }

    foreach(QGraphicsItem * k , list)
    {
        PotatoMineClass * item3 = dynamic_cast<PotatoMineClass *>(k);
        if (item3)
        {
            setXVelocity(0);
            item3->setLife(item3->getLife() - 1);
            qDebug() << item3->getLife();
            //delete item3;
            setVisible(false);
            item3->setVisible(false);
        }
    }

    foreach(QGraphicsItem * l , list)
    {
        WallNutClass * item4 = dynamic_cast<WallNutClass *>(l);
        if (item4)
        {
            setXVelocity(0);
            item4->setLife(item4->getLife() - 1);
            qDebug() << item4->getLife();
            if(item4->getLife() <= 0)
            {
                item4->setVisible(false);
                //delete item4;
                setXVelocity(1.1);
            }
        }
    }

    foreach(QGraphicsItem * m , list)
    {
        RepeaterClass * item5 = dynamic_cast<RepeaterClass *>(m);
        if (item5)
        {
            setXVelocity(0);
            item5->setLife(item5->getLife() - 1);
            qDebug() << item5->getLife();
            if(item5->getLife() <= 0)
            {
                item5->setVisible(false);
                //delete item5;
                setXVelocity(1.1);
            }
        }
    }

    foreach(QGraphicsItem * n , list)
    {
        ChomperClass * item6 = dynamic_cast<ChomperClass *>(n);
        if (item6)
        {
            setVisible(false);
            setXVelocity(0);
            item6->setLife(item6->getLife() - 1);
            qDebug() << item6->getLife();
            if(item6->getLife() <= 0)
            {
                item6->setVisible(false);    
                //delete item6;
            }
        }
    }

    foreach(QGraphicsItem * o , list)
    {
        CherryBombClass * item7 = dynamic_cast<CherryBombClass *>(o);
        if (item7)
        {
            setXVelocity(0);
            //item7->setLife(item7->getLife() - 1);
            //qDebug() << item7->getLife();
            item7->setVisible(false);
            //delete item6;
            setVisible(false);
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

flagzombies::flagzombies(int x) // User level 1
{
    xCoordinate = 680;
    speed = 0.9;
    random = 0;
    random1 = x*75;
    random2 = 0;

    zombie.load("C://Users/User/Desktop/Plants vs Zombies files/zombie2.png");
    this->setPos(680,160);
    life = 10;
}

flagzombies::flagzombies(int x, int y)
{

}


coneheadzombies::coneheadzombies()
{
    xCoordinate = 680;
    speed = 1.1;
    random = 0;
    random1 = (randomValue()*75);
    random2 = 0;
    this->setPos(680,130);

    zombie.load("C://Users/User/Desktop/Plants vs Zombies files/zombie3.png");
    life = 15; //28 is too high for my game so I chose 15
}

coneheadzombies::coneheadzombies(int x, int y)
{
    xCoordinate = 680;
    speed = 1.1;
    random = 0;
    random1 = (randomValue2()*75);
    random2 = 0;
    this->setPos(680,130);

    zombie.load("C://Users/User/Desktop/Plants vs Zombies files/zombie3.png");
    life = 15; //28 is too high for my game so I chose 15
}


bucketheadzombies::bucketheadzombies()
{
    xCoordinate = 680;
    speed = 1.1;
    random = 0;
    random1 = (randomValue()*75);
    random2 = 0;

    zombie.load("C://Users/User/Desktop/Plants vs Zombies files/zombie4.png");
    life = 20; //65 is too high for my game so I chose 20
}


newspaperzombies::newspaperzombies()
{
    xCoordinate = 680;
    speed = 1.1;
    random = 0;
    random1 = (randomValue()*75);
    random2 = 0;

    zombie.load("C://Users/User/Desktop/Plants vs Zombies files/zombie5.png");
    life = 12; //16 is high for my game so I chose 12
}
