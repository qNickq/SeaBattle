#include "ship.h"
#include <QDebug>


Ship::Ship(int _type) : type(_type)
{
    switch (type)
    {
    case 1:
    {
        sprite = new QPixmap(":/res/1.png");
        break;
    }
    case 2:
    {
        sprite = new QPixmap(":/res/2.png");
        break;
    }
    case 3:
    {
        sprite = new QPixmap(":/res/3.png");
        break;
    }
    case 4:
    {
        sprite = new QPixmap(":/res/4.png");
        break;
    }
    default:
    {
        break;
    }
    }
}

int Ship::getType()
{
    return type;
}

QPixmap *Ship::getSprite()
{
    return sprite;
}

Ship::~Ship()
{
    delete sprite;
}


void Ship::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(QBrush(*sprite));
    painter->setPen(Qt::NoPen);
    painter->drawRect(0, 0, sprite->width(), sprite->height());

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QRectF Ship::boundingRect() const
{
    return QRectF(0, 0, sprite->width(), sprite->height());
}

