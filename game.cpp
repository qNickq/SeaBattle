#include "game.h"

Game::Game(QWidget *parent) : QWidget(parent)
{
    Field * player1 = new Field;
    Field * player2 = new Field;

    QHBoxLayout * h_lay = new QHBoxLayout;
    setLayout(h_lay);

    v_field1 = new QGraphicsView;
    v_field2 = new QGraphicsView;

    v_field1->setScene(player1);
    v_field2->setScene(player2);

    h_lay->addWidget(v_field1);
    h_lay->addWidget(v_field2);
}
