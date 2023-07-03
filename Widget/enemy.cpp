
#include "enemy.h"
#include <QPixmap>

Enemy::Enemy(QWidget *parent, int max_health, int min_attack, int max_attack,
             int cold_time, int cold_time_bias, const std::vector<int> & blocks, double block_frecuancy,
             QString img_address)
    : QLabel(parent), _max_health(max_health), _attack_low(min_attack), _attack_high(max_attack), _cold_time(cold_time),
    _block_codes(blocks), _block_frecuancy(block_frecuancy), _parent(parent), _cold_time_bias(cold_time_bias)
{
    _health = _max_health;

    if (img_address != "")
    {
        _image = new QPixmap(img_address);
    }
    else
    {
        _image = nullptr;
    }

    _max_health_bar = new QLabel(_parent);
    _max_health_bar->setGeometry(
        Right_Health_Container_X_Center - Right_Health_Container_Width / 2,
        Right_Health_Container_Y_Center - Right_Health_Container_Height / 2,
        Right_Health_Container_Width, Right_Health_Container_Height);
    _max_health_bar->setVisible(true);
    _max_health_bar->setPixmap(QPixmap(Enemy_Health_Container_Address));
    _max_health_bar->setAttribute(Qt::WA_TranslucentBackground);

    _health_bar = new QLabel(_parent);
    _health_bar->setGeometry(
        Right_Health_Bar_X_Center - Right_Health_Bar_Width / 2,
        Right_Health_Bar_Y_Center - Right_Health_Bar_Height / 2,
        Right_Health_Bar_Width, Right_Health_Bar_Height);
    _health_bar->setPixmap(QPixmap(Health_Bar_Address));
    _health_bar->setVisible(true);
    _health_bar->setAttribute(Qt::WA_TranslucentBackground);
    _health_bar->setAlignment(Qt::AlignRight);

    _health_text = new QLabel(_parent);
    _health_text->setGeometry(
        Right_Health_Bar_X_Center - Right_Health_Bar_Width / 2,
        Right_Health_Bar_Y_Center - Right_Health_Bar_Height / 2,
        Right_Health_Bar_Width, Right_Health_Bar_Height);
    _health_text->setVisible(true);
    _health_text->setFont(QFont(QFontDatabase::applicationFontFamilies(1).at(0), 30));
    _health_text->setAttribute(Qt::WA_TranslucentBackground);
    _health_text->setAlignment(Qt::AlignCenter);
    _health_text->setText(QString::number(_health) + " / " + QString::number(_max_health)); 

    _sword_icon = new QLabel(_parent);
    _sword_icon->setGeometry(Right_Sword_Icon_X_Center - Right_Sword_Icon_Width / 2, Right_Sword_Tcon_Y_Center - Right_Sword_Icon_Height / 2,
                             Right_Sword_Icon_Width, Right_Sword_Icon_Height);
    _sword_icon->setPixmap(QPixmap(Attack_Icon_Address));
    _sword_icon->setAttribute(Qt::WA_TranslucentBackground);
    _sword_icon->setVisible(true);

    _attack_info = new QLabel(_parent);
    _attack_info->setGeometry(Right_Attack_Info_X_Center - Right_Attack_Info_Width / 2, Right_Attack_Info_Y_Center - Right_Attack_Info_Height / 2,
                              Right_Attack_Info_Width, Right_Attack_Info_Height);
    _attack_info->setFrameStyle(QFrame::Box);
    _attack_info->setFont(QFont(QFontDatabase::applicationFontFamilies(1).at(0), 30));
    _attack_info->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    _attack_info->setText(QString::number(_attack_low) + " - " + QString::number(_attack_high));
    _attack_info->setAttribute(Qt::WA_TranslucentBackground);
    _attack_info->setVisible(true);

    // 一开始敌人在窗口外
    this->setGeometry(Main_Window_Width, Enemy_Y_Bottom - Enemy_Height,
                      Enemy_Width, Enemy_Height);
    this->setText("ENEMY");
    this->setVisible(true);
    if (_image)
    {
        this->setPixmap(*_image);
    }
}

void Enemy::update()
{
    _health_bar->setGeometry(
        Right_Health_Bar_X_Center - Right_Health_Bar_Width / 2 + Right_Health_Bar_Width * (1 - 1.0 * _health / _max_health),
        Right_Health_Bar_Y_Center - Right_Health_Bar_Height / 2,
        Right_Health_Bar_Width * (1.0 * _health / _max_health), Right_Health_Bar_Height);

    _health_text->setText(QString::number(_health) + " / " + QString::number(_max_health));
    _attack_info->setText(QString::number(_attack_low) + " - " + QString::number(_attack_high));
}

