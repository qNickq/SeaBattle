#pragma once

#include <QtWidgets>
#include "ship.h"

class Build : public QGraphicsView
{
    Q_OBJECT
public:
    Build(QWidget *parent = nullptr);

public slots:
    void cancel(int);

signals:
    void building(int);
    void ready_activate(bool);

private:  
    QGraphicsScene * scene;
    int count[4] = {0,0,0,0};

protected:
    void mousePressEvent(QMouseEvent*);
    void keyPressEvent(QKeyEvent*event);
};

