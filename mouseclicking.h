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
    QPointF position;

signals:

public slots:
    void mousePressEvent(QMouseEvent *);

};

#endif // MOUSECLICKING_H
