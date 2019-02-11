#pragma once

#include <QtWidgets>
#include "ship.h"

class Build : public QGraphicsView
{
    Q_OBJECT
public:
    Build(QWidget *parent = nullptr);
public slots:
    void success(bool);
signals:
    void building(int);
private: 
    QGraphicsScene * scene;
    int count[4] = {0,0,0,0};

protected:
    void mousePressEvent(QMouseEvent*);
};

