#pragma once

#include <QGraphicsObject>
#include <QPainter>

class Cell : public QGraphicsObject
{
public:
    Cell(int i, int k);

private:
    QPoint pos;
    QPixmap* sprite;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
};
