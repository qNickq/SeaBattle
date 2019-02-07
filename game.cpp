#include "game.h"

Game::Game(QWidget *parent) : QWidget(parent)
{
    Field * player1 = new Field;
    Field * player2 = new Field;

    BuildUI * build = new BuildUI;


    QLabel* l_pl1 = new QLabel("You");
    QLabel* l_pl2 = new QLabel("Enemy");

    view_field1 = new QGraphicsView;
    view_field2 = new QGraphicsView;

    view_field1->setScene(player1);
    view_field2->setScene(player2);

    view_field1->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view_field1->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view_field1->setRenderHint(QPainter::Antialiasing, false);
    view_field1->setFixedSize(322, 322);

    view_field2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view_field2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view_field2->setRenderHint(QPainter::Antialiasing, false);
    view_field2->setFixedSize(322, 322);

    QVBoxLayout * v_lay = new QVBoxLayout;
    QHBoxLayout * h_lay = new QHBoxLayout;
    QVBoxLayout * v_lay1 = new QVBoxLayout;
    QVBoxLayout * v_lay2 = new QVBoxLayout;

    v_lay1->addWidget(l_pl1);
    v_lay1->addWidget(view_field1);

    v_lay2->addWidget(l_pl2);
    v_lay2->addWidget(view_field2);

    h_lay->addLayout(v_lay1);
    h_lay->addLayout(v_lay2);
    connect(build, SIGNAL(building(int)), player2, SLOT(buildShip(int)));
    v_lay->addLayout(h_lay);
    v_lay->setSizeConstraint(QLayout::SetFixedSize);
    v_lay->addWidget(build);
    setLayout(v_lay);
}
