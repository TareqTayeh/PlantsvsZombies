#include "mouseclicking.h"

mouseClicking::mouseClicking(QWidget *parent) :
    QGraphicsView(parent)
{
    xPosition = 0; yPosition = 0;
}

void mouseClicking::setxPosition(int x)
{
    xPosition = x;
}

void mouseClicking::setyPosition(int y)
{
    yPosition = y;
}

int mouseClicking::getxPosition() const
{
    return xPosition;
}

int mouseClicking::getyPosition() const
{
    return yPosition;
}

void mouseClicking::mousePressEvent(QMouseEvent *mouseEvent)
{
    position = mouseEvent->pos();
    qDebug() << position.x();
    qDebug() << position.y();
    //setxPosition(position.x());
    //setyPosition(position.y());
}
