#pragma once
#include <QGraphicsScene>
#include <QGraphicsObject>
#include <QVector>

class Cell : public QGraphicsObject
{
public:
    Cell(int i, int k);
private:
    QPoint pos;
    QPixmap sprite;
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
};

class Field : public QGraphicsScene
{
public:
    Field();
private:
    QVector<QVector<int>> map = {{0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0}};

};
