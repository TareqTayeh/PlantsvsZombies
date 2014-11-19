#ifndef MOUSECLICKING_H
#define MOUSECLICKING_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QPointF>
#include <QDebug>

class mouseClicking : public QGraphicsView
{
    Q_OBJECT
public:
    explicit mouseClicking(QWidget *parent = 0);
    void mousePressEvent(QMouseEvent *);
    QPointF position;

signals:

public slots:

};

#endif // MOUSECLICKING_H
