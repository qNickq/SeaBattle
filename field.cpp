#include "field.h"

Field::Field(QWidget *parent)
{
    scene = new QGraphicsScene;
    setScene(scene);

    isBattle = false;
    active = nullptr;

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(322, 322);

    for(int i = 0; i < 10; ++i)
    {
        for(int k = 0; k < 10; ++k)
        {
            Cell * cell = new Cell(i,k);
            cell->setPos(32*i, 32*k);
            scene->addItem(cell);
        }
    }
}

bool Field::check()
{
    for(auto obj : active->collidingItems())
    {
        if(Ship * temp = dynamic_cast<Ship*>(obj))
        {
            return false;
        }
    }

    if(active->rotation() == 0)
    {
        int _x = active->pos().x()-32;
        int _y = active->pos().y()-32;

        for(int k = 0; k < 3; ++k)
        {
            for(int i = 0; i < active->getType()+2; ++i)
            {
                if(Ship* temp = dynamic_cast<Ship*>(itemAt(_x+k*32, _y+i*32)))
                {
                    if(temp != active)
                        return false;
                }
            }
        }
    }
    else if (active->rotation() > 0)
    {
        int _x = active->pos().x() - active->getType()*32;
        int _y = active->pos().y() - 32;

        for(int k = 0; k < 3; ++k)
        {
            for(int i = 0; i < active->getType()+2; ++i)
            {
                if(Ship* temp = dynamic_cast<Ship*>(itemAt(_x+i*32, _y+k*32)))
                {
                    if(temp != active)
                        return false;
                }
            }
        }
    }
    return true;
}

void Field::buildShip(int type)
{
    Ship * ship = new Ship(type);
    active = ship;
    scene->addItem(ship);
}

QVector<QVector<int>> Field::getMap() const
{
    return map;
}

void Field::setMap()
{
    for (int i = 0; i < 10; ++i)
    {
        for (int k = 0; k < 10; ++k)
        {
            if(items(i*32, k*32).size() > 1)
            {
                map[i][k]= 1;
            }
        }
    }
}

void Field::setIsBattle(bool value)
{
    isBattle = value;
}

bool Field::setHit(int x, int y)
{
    QGraphicsPixmapItem *hit = new QGraphicsPixmapItem;

    if(map[x][y] == 1)
    {
        hit->setPixmap(QPixmap(":/res/hit.png"));
        hit->setPos(x*32, y*32);
        scene->addItem(hit);

        return true;
    }
    if(map[x][y] == 0)
    {
        hit->setPixmap(QPixmap(":/res/miss.png"));
        hit->setPos(x*32, y*32);

        scene->addItem(hit);

        return false;
    }
}

void Field::setShot(bool hit,int x, int y)
{
    if(hit)
    {
        map[x][y] = 1;

        QGraphicsPixmapItem *hit = new QGraphicsPixmapItem;
        hit->setPixmap(QPixmap(":/res/hit.png"));
        hit->setPos(x*32, y*32);

        scene->addItem(hit);
        setEnabled(true);
    }
    else
    {
        map[x][y] = -1;

        QGraphicsPixmapItem *hit = new QGraphicsPixmapItem;
        hit->setPixmap(QPixmap(":/res/miss.png"));
        hit->setPos(x*32, y*32);

        scene->addItem(hit);
        setEnabled(false);
    }
}

void Field::keyPressEvent(QKeyEvent * event)
{
    if(active)
    {
        int _x = active->pos().x();
        int _y = active->pos().y();
        int angle = active->rotation();

        switch (event->key()) {
        case Qt::Key_R:
        {
            active->setTransformOriginPoint(16,16);

            if(angle == 0 && (_x-(active->getType()-1)*32) >= 0)
            {
                active->setRotation(angle+90);
                check();
            }
            else if(angle > 0 && (_y+(active->getType()-1)*32) < 320)
            {
                active->setRotation(angle-90);
                check();
            }
            break;
        }

        case Qt::Key_Up:
        {
            if(_y-32 >= 0)
            {
                active->moveBy(0,-32);
                check();
            }
            break;
        }
        case Qt::Key_Down:
        {
            if((angle == 0) && (_y+32 < 320-(active->getType()-1)*32))
            {
                active->moveBy(0,32);
                check();
            }
            else if ((angle > 0) && (_y+32 < 320))
            {
                active->moveBy(0,32);
                check();
            }
            break;
        }
        case Qt::Key_Left:
        {
            if((angle == 0) && (_x-32 >= 0))
            {
                active->moveBy(-32,0);
                check();
            }
            else if ((angle > 0) && (_x-32-(active->getType()-1)*32) >= 0)
            {
                active->moveBy(-32,0);
                check();
            }

            break;
        }
        case Qt::Key_Right:
        {
            if(_x+32 < 320)
            {
                active->moveBy(32,0);
                check();
            }
            break;
        }
        case Qt::Key_Space:
        {
            if(check())
            {
                emit success(true);
                active = nullptr;
            }
            break;
        }
        case Qt::Key_Escape:
        {
            if(active != nullptr)
            {
                emit cancel(active->getType());
                scene->removeItem(active);
            }
            active = nullptr;
            break;
        }
        }
    }
}

void Field::mousePressEvent(QMouseEvent * event)
{
    if(!isBattle)
    {
        if (Ship * ship = dynamic_cast<Ship*>(itemAt(event->pos())))
        {
            if (active == nullptr)  active = ship;
        }
    }
    else
    {
        if(Cell * cell = dynamic_cast<Cell*>(items(event->pos()).last()))
        {
            emit sending(cell->pos());
            setEnabled(false);
        }
    }
}
