#include "menu.h"

Menu::Menu(QWidget *parent) : QWidget(parent)
{
    QLabel* lb_ip = new QLabel("&IP:");
    QLabel* lb_port = new QLabel("&Port:");

    QLineEdit* l_ip = new QLineEdit;
    QLineEdit* l_port = new QLineEdit;

    lb_ip->setBuddy(l_ip);
    lb_port->setBuddy(l_port);

    l_port->setValidator(new QIntValidator);

    QPushButton * start = new QPushButton("Connect to server");

    connect(start, SIGNAL(clicked()), SLOT(startGame()));
    connect(l_ip, SIGNAL(textChanged(const QString&)), SLOT(setIP(const QString&)));
    connect(l_port, SIGNAL(textChanged(const QString&)), SLOT(setPort(const QString&)));

    l_ip->setText("localhost");
    l_port->setText("2019");

    //Layout settings
    QVBoxLayout* v_lay = new QVBoxLayout;

    v_lay->addWidget(lb_ip);
    v_lay->addWidget(l_ip);

    v_lay->addWidget(lb_port);
    v_lay->addWidget(l_port);

    v_lay->addWidget(start);

    setLayout(v_lay);
}

void Menu::startGame()
{
    Game * game = new Game(ip, port);
    game->show();
    this->close();

}

void Menu::setIP(const QString & _ip)
{
    ip = _ip;
}

void Menu::setPort(const QString& _port)
{
    port = _port.toInt();
}
