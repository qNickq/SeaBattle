#pragma once

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVector>
#include <QKeyEvent>

#include "ship.h"
#include "cell.h"

class Field : public QGraphicsView
{
    Q_OBJECT
public:
    Field(QWidget * parent = nullptr);
    bool check();

    QVector<QVector<int> > getMap() const;

    void setIsBattle(bool value);
    bool setHit(int, int);
    void setShot(bool hit, int, int);

public slots:
    void buildShip(int);
    void setMap();

signals:
    void success(bool);
    void cancel(int);
    void sending(QPointF);

private:
    QVector<QVector<int>> map = QVector<QVector<int>>(10,QVector<int>(10,0));
    QGraphicsScene * scene;
    Ship * active;
    bool isBattle;

protected:
    void keyPressEvent(QKeyEvent*);
    void mousePressEvent(QMouseEvent *event);
};
