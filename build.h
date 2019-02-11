#pragma once

#include <QtWidgets>
#include "ship.h"

class BuildUI : public QGraphicsView
{
    Q_OBJECT
public:
    BuildUI(QWidget *parent = nullptr);

signals:
    void building(int);

public slots:
    void buildShip(int);
private:
    int count;
};

