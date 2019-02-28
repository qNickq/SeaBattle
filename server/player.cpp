#include "player.h"
#include <QDebug>
Player::Player(QTcpSocket *socket)
{
    this->sock = socket;
    this->ready = false;
    this->ships_count = 10;
    this->map = QVector<QVector<int>>(10,QVector<int>(10,0));
}

bool Player::check_point(QPoint p)
{
    if (this->map[p.x()][p.y()] == 0){
        this->map[p.x()][p.y()] = -2; // мимо
        return false;
    }
    else {
        this->map[p.x()][p.y()] = -1; //в цель
        return true;
    }
}

void Player::set_ready(bool isReady)
{
    this->ready = isReady;
}

void Player::set_map(QVector<QVector<int>> new_map)
{
    this->map = new_map;
}

void Player::show_map()
{
    for (auto v : map)
    {
        for (auto d : v)
            cout << d << " ";
        cout << endl;
    }
}

bool Player::isFirst() const
{
    return first_step;
}

bool Player::isReady() const
{
    return ready;
}

bool Player::isEmpty() const
{
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            if (map[i][j] > 0)
                return false;

    return true;
}

bool Player::isDied(int x, int y,int prev_x,int prev_y, QVector<QPoint> &ship) const
{
    if (this->map[x][y] == -1)
        ship.push_back(QPoint(x,y));


    bool died = true;
    if (y+1 < 10)
    {
        if (this->map[x][y+1] == 1)
            return false;
        if (this->map[x][y+1] == -1 && (x != prev_x || y+1 != prev_y))
        {

            died = this->isDied(x,y+1,x,y,ship);
        }
    }
    if (y-1 >= 0)
    {
        if (this->map[x][y-1] == 1)
            return false;
        if (this->map[x][y-1] == -1 && (x != prev_x || y-1 != prev_y))
            died = this->isDied(x,y-1,x,y,ship);
    }
    if (x+1 < 10)
    {
        if (this->map[x+1][y] == 1)
            return false;
        if (this->map[x+1][y] == -1 && (x+1 != prev_x || y != prev_y))
            died = this->isDied(x+1,y,x,y,ship);
    }
    if (x-1 >= 0)
    {
        if (this->map[x-1][y] == 1)
            return false;
        if (this->map[x-1][y] == -1 && (x-1 != prev_x || y != prev_y))
            died = this->isDied(x-1,y,x,y,ship);
    }
    return died;
}

int Player::descriptor() const
{
    return sock->socketDescriptor();
}

QTcpSocket *Player::socket()
{
    return sock;
}

void Player::set_first_step(bool isFirst)
{
    this->first_step = isFirst;
    if (isFirst)
        sock->write("1");
    else
        sock->write("2");

}
