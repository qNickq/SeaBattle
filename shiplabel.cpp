#include "shiplabel.h"

ShipLabel::ShipLabel(const QString& text, QWidget* parent)
    : QLabel(parent)
{
    type = 0;
    setPixmap(QPixmap(text));
}

ShipLabel::~ShipLabel()
{
}

void ShipLabel::setType(int _type)
{
    type = _type;
}

void ShipLabel::mousePressEvent(QMouseEvent* event)
{
    emit clicked(type);
}
