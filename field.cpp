#include "field.h"

Field::Field()
{
    for(int i = 0; i < 10; ++i)
        for(int k = 0; k < 10; ++k){
            Cell * cell = new Cell(i,k);
            this->addItem(cell);
        }
}

Cell::Cell(int i, int k)
{
    pos = QPoint(i,k);
}

void Cell::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}

QRectF Cell::boundingRect() const
{
    return QRectF(0, 0, sprite.width(), sprite.height());
}
