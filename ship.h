#pragma once

#include <QGraphicsObject>
#include <QPainter>

class Ship : public QGraphicsObject
{
public:
    Ship(int);

private:
    int size;
    QPixmap* sprite;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
};
