#include "build.h"

Build::Build(QWidget *parent)
{
    scene = new QGraphicsScene;
    setScene(scene);

    QColor color(198,219,247); //Sea color :)
    setAlignment(Qt::AlignTop|Qt::AlignLeft);
    setBackgroundBrush(QBrush(color));
    setFixedSize(320,130);
    setSizeAdjustPolicy(AdjustToContents);

    for(int i = 1; i < 5; ++i)
    {
        Ship* ship = new Ship(i);
        ship->setPos(0,(i-1)*32);
        ship->setRotation(-90);//Question!!!
        scene->addItem(ship);
    }
}

void Build::success(bool s)
{
    setEnabled(s);
}

void Build::mousePressEvent(QMouseEvent *event)
{
    if(Ship * ship = dynamic_cast<Ship*>(itemAt(event->pos())))
    {
        int type = ship->getType();

        switch (type)
        {
        case 1:
        {
            if(count[0] < 4)
            {
                emit building(type);
                ++count[0];
            }
            break;
        }
        case 2:
        {
            if(count[1] < 3)
            {
                emit building(type);
                ++count[1];
            }
            break;
        }
        case 3:
        {
            if(count[2] < 2)
            {
                emit building(type);
                ++count[2];
            }
            break;
        }
        case 4:
        {
            if(count[3] < 1)
            {
                emit building(type);
                ++count[3];
            }
            break;
        }

        }
        this->setDisabled(true);
    }
}

