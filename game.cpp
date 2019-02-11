#include "game.h"

Game::Game(QWidget *parent) : QWidget(parent)
{
    //Views for fields and Bilding UI
    Field * player1 = new Field;
    Field * player2 = new Field;
    Build * build = new Build;
    //****************************//

    QLabel* l_pl1 = new QLabel("You");
    QLabel* l_pl2 = new QLabel("Enemy");

    connect(build, SIGNAL(building(int)), player1, SLOT(buildShip(int)));
    connect(player1, SIGNAL(success(bool)), build, SLOT(success(bool)));

    //Layout settings
    QVBoxLayout * v_lay = new QVBoxLayout;
    QHBoxLayout * h_lay = new QHBoxLayout;
    QVBoxLayout * v_lay1 = new QVBoxLayout;
    QVBoxLayout * v_lay2 = new QVBoxLayout;

    v_lay1->addWidget(l_pl1);
    v_lay1->addWidget(player1);

    v_lay2->addWidget(l_pl2);
    v_lay2->addWidget(player2);

    h_lay->addLayout(v_lay1);
    h_lay->addLayout(v_lay2);

    v_lay->addLayout(h_lay);
    v_lay->setSizeConstraint(QLayout::SetFixedSize);
    v_lay->addWidget(build);
    //****************************//

    setLayout(v_lay);
}
