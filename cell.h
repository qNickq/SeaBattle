#pragma once

#include <QGraphicsObject>
#include <QPainter>

class Cell : public QGraphicsObject
{
public:
    Cell(int i, int k);

private:
    QPoint coordinate;
    QPixmap* sprite;
    bool free;
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
};
