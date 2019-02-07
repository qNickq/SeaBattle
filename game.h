#pragma once

#include <QtWidgets>
#include "field.h"
#include "buildui.h"

class Game : public QWidget
{
    Q_OBJECT
public:
    Game(QWidget *parent = nullptr);

private:
    QGraphicsView * view_field1;
    QGraphicsView * view_field2;
};
