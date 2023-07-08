
#include "movingsign.h"

MovingSign::MovingSign(QWidget* parent,
    const int sign_length, const int sign_height,
    const double velocity)
    : QLabel(parent)
{
    _velocity = velocity;
    _left = OperationBar_Left, _right = OperationBar_Right;
    this->setGeometry(_left, OperationBar_Frame_Y_Center - sign_height / 2,
                      sign_length, sign_height);
    _cur_x = this->pos().x();

    this->setPixmap(QPixmap(MovingSign_Address).scaled(this->size()));

    this->setVisible(true);
}

void MovingSign::move_on_bar()
{
    double x = _cur_x + _velocity * _direction;

    if (x >= _right)
    {
        _direction = -1;
        x = _right - (x - _right);
    }
    else if (x <= _left)
    {
        _direction = 1;
        x = _left + (_left - x);
    }
//    qDebug() << this->pos().x()  << " to " << x << ", velocity: " << _velocity << '\n';
    this->move(x, this->pos().y());
    _cur_x = x;
}

int MovingSign::get_pos_hit()
{
    return this->pos().x() + this->width() / 2;
}

