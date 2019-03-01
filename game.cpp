#include "game.h"

Game::Game(const QString &strHost, int nPort, QWidget *parent) : QWidget(parent)
{
    socket = new QTcpSocket(this);
    socket->connectToHost(strHost, nPort);

    connect(socket, SIGNAL(connected()), SLOT(slotConnected()));
    connect(socket, SIGNAL(readyRead()), SLOT(readyServerRead()));

    isBattle = false;

    //Views for fields and Bilding UI
    field1 = new Field;
    field2 = new Field;

    build = new Build;
    build->setEnabled(false);
    build->setFixedHeight(66);
    //****************************//

    wait = new QLabel("Ожидайте подключения соперника!");

    turn = new QLabel();
    turn->hide();

    ready = new QPushButton("Готов");
    ready->setEnabled(false);

    rules = new QTextEdit();
    rules->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    rules->setReadOnly(true);
    rules->setText("Выберете корабль из нижней части, нажав на него ЛКМ либо клавишами: '1' '2' '3' '4'.\n"
                   "Стрелками перемещайте корабль по игровому полю.\n"
                   "Нажмите R для поворота корабля.\n"
                   "Нажмите SPACE чтобы поставить корабль.\n"
                   "Нажмите ESCAPE чтобы отменить выбор.\n"
                   "Если хотите изменить положение корабля, нажмите на него ЛКМ.\n"
                   "Послу расстановки всех кораблей нажмите на кнопку ГОТОВ.");

    digits1 = new QLabel;
    digits2 = new QLabel;

    digits1->setPixmap(QPixmap(":/res/dig.png"));
    digits2->setPixmap(QPixmap(":/res/dig.png"));

    leters1 = new QLabel;
    leters2 = new QLabel;

    leters1->setPixmap(QPixmap(":/res/leters.png"));
    leters2->setPixmap(QPixmap(":/res/leters.png"));

    connect(build, SIGNAL(building(int)), field1, SLOT(buildShip(int)));
    connect(build, SIGNAL(ready_activate(bool)), ready, SLOT(setEnabled(bool)));

    connect(field1, SIGNAL(success(bool)), build, SLOT(setEnabled(bool)));
    connect(field1, SIGNAL(success(bool)), build, SLOT(setFocus()));
    connect(field1, SIGNAL(cancel(int)), build, SLOT(cancel(int)));
    connect(field2, SIGNAL(sending(QPointF)), SLOT(sendPointToServer(QPointF)));

    connect(ready, SIGNAL(clicked()), field1, SLOT(setMap()));
    connect(ready, SIGNAL(clicked()), SLOT(sendFieldToServer()));

    //Layout settings
    v_lay = new QVBoxLayout;
    v_lay1 = new QVBoxLayout;
    v_lay2 = new QVBoxLayout;

    h_lay = new QHBoxLayout;
    h_lay1 = new QHBoxLayout;
    h_lay2 = new QHBoxLayout;

    //Design field #1
    leters1->setAlignment(Qt::AlignRight);

    v_lay1->addWidget(leters1);

    h_lay1->addWidget(digits1);
    h_lay1->addWidget(field1);

    v_lay1->addLayout(h_lay1);

    //Design field #2
    leters2->setAlignment(Qt::AlignRight);

    v_lay2->addWidget(leters2);
    h_lay2->addWidget(digits2);
    h_lay2->addWidget(field2);

    v_lay2->addLayout(h_lay2);

    digits2->hide();
    leters2->hide();
    field2->hide();

    v_lay2->addWidget(rules);
    v_lay2->addWidget(build);
    v_lay2->addWidget(wait);
    v_lay2->addWidget(ready);

    h_lay->addLayout(v_lay1);
    h_lay->addLayout(v_lay2);

    v_lay->addWidget(turn);
    v_lay->addLayout(h_lay);

    v_lay->setSizeConstraint(QLayout::SetFixedSize);

    //****************************//

    setLayout(v_lay);
    build->setFocus();
}

void Game::win()
{
    QMessageBox win;
    win.setText("You are Winner!!!");
    win.exec();
    close();

}

void Game::lose()
{
    QMessageBox lose;
    lose.setText("You are Loser(");
    lose.exec();
    close();
}

void Game::slotConnected()
{
    qDebug() << "Connected!";
}

void Game::sendFieldToServer()
{
    QString f;
    for (int i = 0; i < 10; ++i)
    {
        for(int k = 0; k < 10; ++k)
        {
            f += QString::number(field1->getMap()[i][k]) + " ";
        }
    }

    socket->write(f.toUtf8());
    ready->disconnect();
    ready->setEnabled(false);
}

void Game::sendPointToServer(QPointF pos)
{
    shot_pos = pos;
    QString temp;
    temp += QString::number(pos.x()/32) + "," + QString::number(pos.y()/32);
    socket->write(temp.toUtf8());
}

void Game::startBattle()
{
    isBattle = true;

    field1->setEnabled(false);
    field2->setIsBattle(true);

    build->close();
    wait->close();
    ready->close();
    rules->close();


    turn->show();
    leters2->show();
    digits2->show();
    field2->show();
}

void Game::readyServerRead()
{
    QString str = socket->read(64);

    if(!isBattle)
    {
        if (str == "all_connected")
        {
            wait->setText("Соперник найден! Расставляйте корабли!");
            build->setEnabled(true);
        }
        if (str == "1")
        {
            field2->setEnabled(true);
            turn->setText("Ваш ход!");
        }
        if (str == "2")
        {
            field2->setEnabled(false);
            turn->setText("Ход противника!");     
        }
        if (str == "all_ready") startBattle();
    }
    else
    {
        if(str.size() == 3)
        {
            QStringList list = str.split(",");

            if(!field2->isEnabled())
            {
                if(!field1->setHit(list[0].toInt(), list[1].toInt()))
                {
                    field2->setEnabled(true);
                    turn->setText("Ваш ход!");
                }
            }
        }
        if (str == "1")
        {
            field2->setShot(1, shot_pos.x()/32, shot_pos.y()/32); //если я попал
            turn->setText("Ваш ход!");
        }
        if (str == "0")
        {
            field2->setShot(0, shot_pos.x()/32, shot_pos.y()/32);; //если я не попал
            turn->setText("Ход противника!");
        }
        if (str == "WINNER") win();
        if (str == "LOSE") lose();
        if (str.contains("KILL"))
        {

            QStringList msg = str.split(" ");
            msg.pop_front();
            msg.pop_back();

            QVector<QPointF> positions;
            for(int i = 0; i < msg.size(); ++i)
            {
                QStringList points = msg[i].split(",");
                positions.push_back(QPointF(points[0].toFloat(), points[1].toFloat()));
            }
            field2->kill(positions);
        }
    }
}
