#include "field.h"

Field::Field()
{
    for(int i = 0; i < 10; ++i)
        for(int k = 0; k < 10; ++k){
            Cell * cell = new Cell(i,k);
            cell->setPos(32*i, 32*k);
            this->addItem(cell);
        }
}
