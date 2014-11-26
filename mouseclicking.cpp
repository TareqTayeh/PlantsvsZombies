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

    mainwindow->drawPeaShooter(position.x(),position.y());
    mainwindow->drawSunFlower(position.x(),position.y());
    mainwindow->drawCherryBomb(position.x(),position.y());
    mainwindow->drawWalNut(position.x(),position.y());
    mainwindow->drawPotatoMine(position.x(),position.y());
    mainwindow->drawSnowPea(position.x(),position.y());
    mainwindow->drawChomper(position.x(),position.y());
    mainwindow->drawRepeater(position.x(),position.y());

    qDebug() << position.x();
    qDebug() << position.y();
}
