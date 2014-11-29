#ifndef SUNPOINTS_H
#define SUNPOINTS_H

#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include <QObject>
#include <cmath>
#include <iostream>
#include <QDebug>
#include <ctime>
#include <QRect>
#include <QPainter>
#include <QTimer>


class sunpoints :  public QGraphicsItem
{

public:
    sunpoints();
    //explicit sunpoints(QWidget *parent = 0);
    void advance(int phase);
    void move(double time);
    double xVelocity;
    double yVelocity;
    void setXVelocity(double);
    void setYVelocity(double);
    int x() const;
    int y() const;
    int randomValueY();
    int randomValueX();
    QRectF boundingRect() const;
    void mousePressEvent(QGraphicsSceneMouseEvent *e);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPixmap Sun;
    QPointF Position;
//    MainWindow *main_window;
    bool isClicked;
    int addSunPoints();

signals:
    void mouse();

private:
    int xCoordinate;
    int yCoordinate;
    int random;
    int random1;
    int random2;
    static int testing;
    double direction;
};

#endif // SUNPOINTS_H
