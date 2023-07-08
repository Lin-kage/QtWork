
#include "operationbar.h"

OperationBar::OperationBar(QWidget *parent,
                           const int x_center, const int y_center,
                           const int length, const int height)
    : QLabel(parent), _parent(parent)
{
    this->setGeometry(x_center - length / 2, y_center - height / 2, length, height);

    this->setVisible(true);

    _left_center = OperationBar_Left;
    _right_center = OperationBar_Right;
    _y_center = y_center;

    qDebug() << "Bar:" << this->geometry() << _left_center << _right_center << '\n';

    _valid_length = _right_center - _left_center;
}

