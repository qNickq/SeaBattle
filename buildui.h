#pragma once

#include <QtWidgets>
#include "shiplabel.h"

class BuildUI : public QWidget
{
    Q_OBJECT
public:
    BuildUI(QWidget *parent = nullptr);

signals:
    void building(int);

public slots:
    void buildShip(int);
};

