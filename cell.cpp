#include "cell.h"

Cell::Cell(int i, int k)
{
    pos = QPoint(i,k);
    sprite = new QPixmap(":/res/cell.png");
}

void Cell::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(QBrush(*sprite));
    painter->setPen(Qt::NoPen);
    painter->drawRect(0, 0, sprite->width(), sprite->height());

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QRectF Cell::boundingRect() const
{
    return QRectF(0, 0, sprite->width(), sprite->height());
}
