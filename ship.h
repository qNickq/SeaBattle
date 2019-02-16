#pragma once

#include <QGraphicsObject>
#include <QPainter>

class Ship : public QGraphicsObject
{
public:
    Ship(int);
    int getType();

    ~Ship();

private:
    int type;
    QPixmap sprite;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
};
