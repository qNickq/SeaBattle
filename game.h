#pragma once

#include <QtWidgets>
#include "field.h"

class Game : public QWidget
{
    Q_OBJECT
public:
    Game(QWidget *parent = nullptr);

private:
    QGraphicsView * v_field1;
    QGraphicsView * v_field2;

signals:

public slots:
};
