#pragma once

#include <QtWidgets>
#include "field.h"
#include "build.h"

class Game : public QWidget
{
    Q_OBJECT
public:
    Game(QWidget *parent = nullptr);

private:
   Field * player1;
   Field * player2;
   Build * build;
};
