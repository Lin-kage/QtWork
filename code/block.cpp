
#include "block.h"
#include "config.h"

Block::Block(QWidget *parent, int x_center, int y_center, int length, int height,
             double velocity, int direction, int hit_count, int hit_count_bound, 
             const QString & path)
    : QLabel(parent),_max_velocity(velocity), _velocity(velocity), _hit_count(hit_count), _hit_count_bound(hit_count_bound), _direction(direction), _path(path)
{
    this->setGeometry(x_center - length / 2, y_center - height / 2, length, height);
    _cur_x_center = x_center;
    _width = length;

    this->setScaledContents(true);
    this->setPixmap(QPixmap(path));

}

void Block::move_on_bar()
{

    _velocity = _velocity + _accelerate <= _max_velocity ? _velocity + _accelerate : _max_velocity;

    if (!_forward_able && _velocity > 0)
        _velocity = 0;

    _cur_x_center += _velocity * _direction;
    this->move((_cur_x_center < OperationBar_Right ? _cur_x_center : OperationBar_Right) - this->width() / 2, this->y());

    time_exist ++;
}

bool Block::in_area(int x) const
{
    return this->pos().x() - Deviation_Tolerance <= x && x <= this->pos().x() + this->width() + Deviation_Tolerance;
}

//WhiteNormalBlock1::WhiteNormalBlock1(QWidget *parent, int x_center, int y_center, int length, int height,
//                       double velocity, int direction, int hit_count, int hit_count_bound)
//    : Block(parent, x_center, y_center, length, height, velocity, direction, hit_count, hit_count_bound, Block_Path[WHITENormalBlock1])
//{
//
//}
//WhiteNormalBlock2::WhiteNormalBlock2(QWidget* parent, int x_center, int y_center, int length, int height,
//    double velocity, int direction, int hit_count, int hit_count_bound)
//    : Block(parent, x_center, y_center, length, height, velocity, direction, hit_count, hit_count_bound, Block_Path[WHITENormalBlock2])
//{
//
//}
//
//WhiteCriticBlock::WhiteCriticBlock(QWidget *parent, int x_center, int y_center, int length, int height,
//                                   double velocity, int direction, int hit_count, int hit_count_bound)
//    : Block(parent, x_center, y_center, length, height, velocity, direction, hit_count, hit_count_bound, Block_Path[WHITECriticBlock])
//{
//
//}
//
//RedNormalBlock1::RedNormalBlock1(QWidget *parent, int x_center, int y_center, int length, int height,
//               double velocity, int direction, int hit_count, int hit_count_bound)
//    : Block(parent, x_center, y_center, length, height, velocity, direction, hit_count, hit_count_bound, Block_Path[REDNormalBlock1])
//{
//
//}
//
//RedNormalBlock2::RedNormalBlock2(QWidget* parent, int x_center, int y_center, int length, int height,
//    double velocity, int direction, int hit_count, int hit_count_bound)
//    : Block(parent, x_center, y_center, length, height, velocity, direction, hit_count, hit_count_bound, Block_Path[REDNormalBlock2])
//{
//
//}
//
//RedFastBlock1::RedFastBlock1(QWidget* parent, int x_center, int y_center, int length, int height,
//    double velocity, int direction, int hit_count, int hit_count_bound)
//    : Block(parent, x_center, y_center, length, height, velocity, direction, hit_count, hit_count_bound, Block_Path[REDFastBlock1])
//{
//
//}
//
//RedFastBlock2::RedFastBlock2(QWidget* parent, int x_center, int y_center, int length, int height,
//    double velocity, int direction, int hit_count, int hit_count_bound)
//    : Block(parent, x_center, y_center, length, height, velocity, direction, hit_count, hit_count_bound, Block_Path[REDFastBlock2])
//{
//
//}
