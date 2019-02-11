#pragma once

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVector>
#include <QKeyEvent>
#include <QDebug>

#include "ship.h"
#include "cell.h"

class Field : public QGraphicsView
{
    Q_OBJECT
public:
    Field(QWidget * parent = nullptr);
    bool check();

public slots:
    void buildShip(int);
signals:
    void success(bool);
private:
    QVector<QVector<int>> map = {{0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0,0}};
    QGraphicsScene * scene;
    Ship * active;
protected:
    void keyPressEvent(QKeyEvent*);
    void mousePressEvent(QMouseEvent *event);
};
