#pragma once
#include <QtWidgets>

class ShipLabel : public QLabel
{
    Q_OBJECT
public:
    ShipLabel( const QString& text="", QWidget* parent=nullptr );
    ~ShipLabel();

    void setType(int);

signals:
    void clicked(int);

protected:
    void mousePressEvent(QMouseEvent* event);

private:
    int type;
    int count;
};
