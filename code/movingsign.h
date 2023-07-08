
#ifndef MOVINGSIGN_H
#define MOVINGSIGN_H

#include "config.h"
#include <QLabel>
#include <QPoint>


class MovingSign : public QLabel
{
    friend class OperationBar;
private:

    int _direction = 1;
    double _velocity;
    int _right, _left;
    double _cur_x;

public:
    MovingSign(QWidget *parent, 
               const int sign_length = MovingSign_Width, const int sign_height = MovingSign_Height,
               const double velocity = Base_Sign_Velocity);
    ~MovingSign() { qDebug() << "moving sign deleted\n"; }

    // 在bar上的移动
    void move_on_bar();

    // 获取浮标对应的坐标
    int get_pos_hit();
};

#endif // MOVINGSIGN_H
