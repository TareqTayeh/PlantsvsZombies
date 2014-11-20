#ifndef MOUSECLICKING_H
#define MOUSECLICKING_H

#include "plants.h"
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QPointF>
#include <QDebug>

class mouseClicking : public QGraphicsView
{
    Q_OBJECT
public:
    explicit mouseClicking(QWidget *parent = 0);
    QPointF position;
    void setxPosition(int);
    void setyPosition(int);
    int getxPosition() const;
    int getyPosition() const;

signals:

public slots:
    void mousePressEvent(QMouseEvent *);

private:
    int xPosition;
    int yPosition;
};

#endif // MOUSECLICKING_H
