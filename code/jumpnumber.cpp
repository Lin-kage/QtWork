
#include "jumpnumber.h"
#include <QFontDatabase>
#include "config.h"

JumpNumber::JumpNumber(QWidget *parent, int num, int x, int y, int direction)
    : QLabel(parent)
{
    this->setFont(QFont(QFontDatabase::applicationFontFamilies(0).at(0), 20));
    this->setText(QString::number(num));
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setGeometry(x + (rand() % 5) * ((rand() % 2) ? -1 : 1), y + (rand() % 5) * ((rand() % 2) ? -1 : 1), 50, 50);
    this->setVisible(true);
    this->setStyleSheet("color:rgb(255,0,0)");

    double angel = cos(1.0 * rand() / RAND_MAX * (JumpNumber_Angel_Max - JumpNumber_Angel_Min));

    qDebug() << angel << '\n';

    _v_x = JumpNumber_Velocity * cos(angel) + 1;
    _v_y = - JumpNumber_Velocity * sin(angel);
    _v_x *= direction;
    _acc = JumpNumber_Accalarate;

    _timer = new QTimer;
    connect(_timer, &QTimer::timeout, this, &JumpNumber::move_num);
    _timer->start(10);
}

JumpNumber::JumpNumber(QWidget* parent, QString str, int x, int y, int direction)
    : QLabel(parent)
{
    this->setFont(QFont(QFontDatabase::applicationFontFamilies(0).at(0), 20));
    this->setText(str);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setGeometry(x + (rand() % 5) * ((rand() % 2) ? -1 : 1), y + (rand() % 5) * ((rand() % 2) ? -1 : 1), 50, 50);
    this->setVisible(true);
    this->setStyleSheet("color:rgb(255,0,0)");

    double angel = cos(1.0 * rand() / RAND_MAX * (JumpNumber_Angel_Max - JumpNumber_Angel_Min));

    qDebug() << angel << '\n';

    _v_x = JumpNumber_Velocity * cos(angel) + 1;
    _v_y = -JumpNumber_Velocity * sin(angel);
    _v_x *= direction;
    _acc = JumpNumber_Accalarate;

    _timer = new QTimer;
    connect(_timer, &QTimer::timeout, this, &JumpNumber::move_num);
    _timer->start(10);
}
