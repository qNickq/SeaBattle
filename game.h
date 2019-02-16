#pragma once

#include <QTcpSocket>

#include "field.h"
#include "build.h"

class Game : public QWidget
{
    Q_OBJECT
public:
    Game(const QString& strHost, int nPort, QWidget *parent = nullptr);
    void win();
    void lose();
public slots:
    void slotConnected();
    void sendFieldToServer();
    void sendPointToServer(QPointF);
    void startBattle();
    void readyServerRead();

private:
    QTcpSocket * socket;

    //Изначальный интерфейс (до боя)
    Build * build;
    QTextEdit * rules;
    QPushButton * ready;

    //Наше поле
    Field * field1;
    QLabel* leters1;
    QLabel* digits1;


    //Поле противника
    Field * field2;
    QLabel* leters2;
    QLabel* digits2;

    QPointF shot_pos;
    bool isBattle;




};
