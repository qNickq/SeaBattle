#include "buildui.h"

BuildUI::BuildUI(QWidget *parent)
{
    QGraphicsScene * scene = new QGraphicsScene;
    setScene(scene);

    //Background
    QPalette pal;
    QColor color(198,219,247);
    pal.setBrush(this->backgroundRole(), QBrush(color));
    this->setPalette(pal);
    this->setAutoFillBackground(true);
    //

    for(int i = 4; i > 0; --i)
    {
        Ship* ship = new Ship(i);
        scene->addItem(ship);
        ship->setX(4*32-i*32);
        setAlignment(Qt::AlignLeft|Qt::AlignTop);
    }
}

void BuildUI::buildShip(int type)
{
    emit building(type);
}

