#include "buildui.h"

BuildUI::BuildUI(QWidget *parent) : QWidget(parent)
{
    //Background
    QPalette pal;
    QColor color(198,219,247);
    pal.setBrush(this->backgroundRole(), QBrush(color));
    this->setPalette(pal);
    this->setAutoFillBackground(true);
    //

    QHBoxLayout * ships = new QHBoxLayout;

    for(int i = 4; i > 0; --i)
    {
        QString s = QString(":/res/%1.png").arg(i) ;
        ShipLabel* ship = new ShipLabel(s);
        ship->setType(i);
        ship->setMaximumSize(ship->pixmap()->size());
        ship->setAlignment(Qt::AlignTop);
        ships->addWidget(ship);
        connect(ship, SIGNAL(clicked(int)), this, SLOT(buildShip(int)));
    }

    ships->setAlignment(Qt::AlignLeft);

    setLayout(ships);
}

void BuildUI::buildShip(int type)
{
    emit building(type);
}

