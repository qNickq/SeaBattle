#pragma once

#include <QGraphicsObject>
#include <QPainter>

class Ship : public QGraphicsObject
{
public:
    Ship(int);

private:
    int type; //Type of ship (1, 2, 3, 4).
    QPixmap* sprite;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

    void mousePressEvent(QGraphicsSceneMouseEvent *);
};
