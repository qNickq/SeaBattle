#pragma once

#include "game.h"

class Menu : public QWidget
{
    Q_OBJECT
public:
    Menu(QWidget *parent = nullptr);

public slots:
    void startGame();
    void setIP(const QString&);
    void setPort(const QString &);

private:
    QString ip = "";
    int port = -1;

};
