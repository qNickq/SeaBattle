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

    Ship* ship1 = new Ship(1);
    ship1->setPos(0,-32);
    scene->addItem(ship1);

    Ship* ship2 = new Ship(2);
    ship2->setPos(0,33);
    ship2->setRotation(-90);
    scene->addItem(ship2);

    Ship* ship3 = new Ship(3);
    ship3->setPos(65,33);
    ship3->setRotation(-90);
    scene->addItem(ship3);

    Ship* ship4 = new Ship(4);
    ship4->setPos(33,0);
    ship4->setRotation(-90);
    scene->addItem(ship4);

}

void Build::cancel(int type)
{
    --count[type-1];
     emit ready_activate(false);
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
                this->setDisabled(true);
            }
            break;
        }
        case 2:
        {
            if(count[1] < 3)
            {
                emit building(type);
                ++count[1];
                this->setDisabled(true);
            }
            break;
        }
        case 3:
        {
            if(count[2] < 2)
            {
                emit building(type);
                ++count[2];
                this->setDisabled(true);
            }
            break;
        }
        case 4:
        {
            if(count[3] < 1)
            {
                emit building(type);
                ++count[3];
                this->setDisabled(true);
            }
            break;
        }
        }

        int sum = 0;
        for(int i = 0; i < 4; ++i)
        {
            sum +=count[i];
        }
        if (sum == 10) emit ready_activate(true);

    }

}

void Build::keyPressEvent(QKeyEvent * event)
{
    switch (event->key())
    {
    case Qt::Key_1:
    {
        if(count[0] < 4)
        {
            emit building(1);
            ++count[0];
            this->setDisabled(true);
        }
        break;
    }
    case Qt::Key_2:
    {
        if(count[1] < 3)
        {
            emit building(2);
            ++count[1];
            this->setDisabled(true);
        }
        break;
    }
    case Qt::Key_3:
    {
        if(count[2] < 2)
        {
            emit building(3);
            ++count[2];
            this->setDisabled(true);
        }
        break;
    }
    case Qt::Key_4:
    {
        if(count[3] < 1)
        {
            emit building(4);
            ++count[3];
            this->setDisabled(true);
        }
        break;
    }
    }
    int sum = 0;
    for(int i = 0; i < 4; ++i)
    {
        sum +=count[i];
    }
    if (sum == 10) emit ready_activate(true);
}

