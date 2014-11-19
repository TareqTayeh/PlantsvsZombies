#include "mouseclicking.h"

mouseClicking::mouseClicking(QWidget *parent) :
    QGraphicsView(parent)
{
}

void mouseClicking::mousePressEvent(QMouseEvent *mouseEvent)
{
    position = mouseEvent->pos();
    qDebug() << position;
}
