
#include "hero.h"
#include <QPixmap>

Hero::Hero(QWidget *parent, int max_health, int min_attack, int max_attack, int magic_attack)
    : QLabel(parent), _max_health(max_health), _attack_low(min_attack), _attack_high(max_attack), _parent(parent), _magic_attack(magic_attack)
{
    _health = _max_health;

    _image = new QPixmap(QString("picture/hero/warrior.png"));

    _max_health_bar = new QLabel(_parent);
    _max_health_bar->setGeometry(
        Left_Health_Container_X_Center - Left_Health_Container_Width / 2,
        Left_Health_Container_Y_Center - Left_Health_Container_Height / 2,
        Left_Health_Container_Width, Left_Health_Container_Height);
    // _max_health_bar->setFrameStyle(QFrame::Box);
    _max_health_bar->setVisible(true);
    _max_health_bar->setAttribute(Qt::WA_TranslucentBackground);
    _max_health_bar->setPixmap(QPixmap(Hero_Health_Container_Address));

    _health_bar = new QLabel(_parent);
    _health_bar->setGeometry(
        Left_Health_Bar_X_Center - Left_Health_Bar_Width / 2,
        Left_Health_Bar_Y_Center - Left_Health_Bar_Height / 2,
        Left_Health_Bar_Width, Left_Health_Bar_Height);
    _health_bar->setPixmap(QPixmap(Health_Bar_Address));
    _health_bar->setVisible(true);
    _health_bar->setAttribute(Qt::WA_TranslucentBackground);

    _health_text = new QLabel(_parent);
    _health_text->setGeometry(
        Left_Health_Bar_X_Center - Left_Health_Bar_Width / 2,
        Left_Health_Bar_Y_Center - Left_Health_Bar_Height / 2,
        Left_Health_Bar_Width, Left_Health_Bar_Height);
    _health_text->setFont(QFont(QFontDatabase::applicationFontFamilies(1).at(0), 30));
    _health_text->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    _health_text->setVisible(true);
    _health_text->setAttribute(Qt::WA_TranslucentBackground);
    _health_text->setText(QString::number(_health) + " / " + QString::number(_max_health));

    _sword_icon = new QLabel(_parent);
    _sword_icon->setGeometry(Left_Sword_Icon_X_Center - Left_Sword_Icon_Width / 2, Left_Sword_Tcon_Y_Center - Left_Sword_Icon_Height / 2,
                             Left_Sword_Icon_Width, Left_Sword_Icon_Height);
    _sword_icon->setPixmap(QPixmap(Attack_Icon_Address));
    _sword_icon->setAttribute(Qt::WA_TranslucentBackground);
    _sword_icon->setVisible(true);

    _attack_info = new QLabel(_parent);
    _attack_info->setGeometry(Left_Attack_Info_X_Center - Left_Attack_Info_Width / 2, Left_Attack_Info_Y_Center - Left_Attack_Info_Height / 2,
                              Left_Attack_Info_Width, Left_Attack_Info_Height);
    _attack_info->setFont(QFont(QFontDatabase::applicationFontFamilies(1).at(0), 30));
    _attack_info->setAlignment(Qt::AlignCenter);
    _attack_info->setText(QString::number(_attack_low) + " - " + QString::number(_attack_high));
    _attack_info->setAttribute(Qt::WA_TranslucentBackground);
    _attack_info->setVisible(true);

    _hit_count_icon = new QLabel(_parent);
    _hit_count_icon->setGeometry(106, 548, 26, 30);
    _hit_count_icon->setVisible(true);
    _hit_count_icon->setPixmap(QPixmap("picture/icon/hit_count_icon.png"));

    _hit_count_info = new QLabel(_parent);
    _hit_count_info->setGeometry(125, 548, 40, 30);
    _hit_count_info->setVisible(true);
    _hit_count_info->setAlignment(Qt::AlignCenter);
    _hit_count_info->setAttribute(Qt::WA_TranslucentBackground);
    _hit_count_info->setFont(QFont(QFontDatabase::applicationFontFamilies(2).at(0), 12));
    _hit_count_info->setText(QString::number(_hit_count));

    _trick_bar_container = new QLabel(_parent);
    _trick_bar_container->setGeometry(192, 545, 249, 36);
    _trick_bar_container->setVisible(true);
    _trick_bar_container->setPixmap(QPixmap("picture/icon/special_trick_bar_container_grey.png"));

    _trick_bar = new QLabel(_parent);
    _trick_bar->setGeometry(241, 554, 190, 18);
    _trick_bar->setVisible(true);
    _trick_bar->setPixmap(QPixmap("picture/icon/special_trick_bar_grey.png"));

    _magic_attack_info = new QLabel(_parent);
    _magic_attack_info->setAttribute(Qt::WA_TranslucentBackground);
    _magic_attack_info->setGeometry(241, 545, 190, 36);
    _magic_attack_info->setFont(QFont(QFontDatabase::applicationFontFamilies(2).at(0), 12));
    _magic_attack_info->setAlignment(Qt::AlignCenter);
    _magic_attack_info->setVisible(true);

    this->setGeometry( -Hero_Width, Hero_Y_Bottom - Hero_Height,
                      Hero_Width, Hero_Height);
    this->setText("HERO");
    this->setVisible(true);
    this->setAttribute(Qt::WA_TranslucentBackground);

    this->setPixmap(*_image);

    _shield = new QLabel(_parent);
    _shield->setGeometry(Hero_X_Center - 66, Hero_Y_Bottom - Hero_Height / 2 - 66, 132, 132);
    _shield->setPixmap(QPixmap("picture/icon/bubble_shield.png"));
}

void Hero::update()
{
    _health_bar->setGeometry(Left_Health_Bar_X_Center - Left_Health_Bar_Width / 2,
                             Left_Health_Bar_Y_Center - Left_Health_Bar_Height / 2,
                             Left_Health_Bar_Width * (1.0 * _health / _max_health),
                             Left_Health_Bar_Height);

    _hit_count_info->setText(QString::number(_hit_count));

    _health_text->setText(QString::number(_health) + " / " + QString::number(_max_health));

    _attack_info->setText(QString::number(_attack_low) + " - " + QString::number(_attack_high));

    if (_hit_count < 5)
    {
        _trick_bar_container->setPixmap(QPixmap("picture/icon/special_trick_bar_container_grey.png"));
        _trick_bar->setPixmap(QPixmap("picture/icon/special_trick_bar_grey.png"));
        _trick_bar->setGeometry(_trick_bar->x(), _trick_bar->y(), 95 * 1.0 * _hit_count / 5, _trick_bar->height());
        _magic_attack_info->setText("");
    }
    else
    {
        _trick_bar_container->setPixmap(QPixmap("picture/icon/special_trick_bar_container.png"));
        _trick_bar->setPixmap(QPixmap("picture/icon/special_trick_bar.png"));
        _trick_bar->setGeometry(_trick_bar->x(), _trick_bar->y(), 95 * (1.0 + 1.0 * (attackage_magic_dynamic(_magic_attack, _hit_count) - attackage_magic_dynamic(_magic_attack, 5)) / (attackage_magic_dynamic(_magic_attack, 60))), _trick_bar->height());
        _magic_attack_info->setText(QString::number(attackage_magic_dynamic(_magic_attack, _hit_count)));
    }

    _shield->setVisible(_shield_on);
}
