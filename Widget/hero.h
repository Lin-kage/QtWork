
#ifndef HERO_H
#define HERO_H

#include <cstdlib>
#include "config.h"
#include "blockloader.h"
#include <QLabel>
#include "jumpnumber.h"

class Hero : public QLabel
{
private:
    QWidget *_parent;

    int _max_health, _health;

    int _attack_low, _attack_high;

    int _triggered_hit_count = 0;
    int _hit_count = 0;

    int _magic_attack;

    QLabel *_max_health_bar, *_health_bar, *_health_text;

    QPixmap *_image;

    // BlockLoader使用参数
    std::vector<int> _blocks = White_Blocks;
    int _cold_time = Standard_Cold_Time, _cold_time_bias = Standard_Cold_Time_Bias,
        _block_frequancy = Standard_Block_Frequancy;

    QLabel *_sword_icon;
    QLabel *_attack_info;
    QLabel *_trick_bar_container, *_trick_bar, *_hit_count_icon, *_hit_count_info, *_magic_attack_info;

    int _movement = 20, _x_standard = Hero_X_Center - Hero_Width / 2;

    bool _jumpnumber_on;

    bool _shield_on = 0;

public:
    Hero(QWidget *parent, int max_health = 100, int min_attack = 10, int max_attack = 15, int magic_attack = 12);

    virtual ~Hero() {
        if (_max_health_bar)
            _max_health_bar->deleteLater();
        if (_health_bar)
            _health_bar->deleteLater();
        if (_sword_icon)
            _sword_icon->deleteLater();
        if (_attack_info)
            _attack_info->deleteLater();
        if (_health_text)
            _health_text->deleteLater();
        delete _image;
        if (_trick_bar)
            _trick_bar->deleteLater();
        if (_trick_bar_container)
            _trick_bar_container->deleteLater();
        if (_hit_count_icon)
            _hit_count_icon->deleteLater();
        if (_hit_count_info)
            _hit_count_info->deleteLater();

        qDebug() << "hero deleted\n";
    }

    void set_jumpnumber(bool b) { _jumpnumber_on = b; }

    void get_shield() { _shield_on = 1; }

    void hurt(int damage) {
        if (_shield_on)
        {
            if (_jumpnumber_on)
                new JumpNumber(_parent, "Defended", Left_JumpNumber_X, Left_JumpNumber_Y, -1);
            _shield_on = 0;
        }
        else
        {
            _health -= damage;
            if (_jumpnumber_on)
                new JumpNumber(_parent, damage, Left_JumpNumber_X, Left_JumpNumber_Y, -1);
        }
    }
    void hurt(double p) {
        if (_shield_on)
        {
            if (_jumpnumber_on)
                new JumpNumber(_parent, "Defended", Left_JumpNumber_X, Left_JumpNumber_Y, -1);
            _shield_on = 0;
        }
        else
        {
            _health -= _max_health * p;
            if (_jumpnumber_on)
                new JumpNumber(_parent, _max_health * p, Left_JumpNumber_X, Left_JumpNumber_Y, -1);
        }
    }

    int health() const { return _health; }
    int max_health() const { return _max_health; }
    int min_attack() const { return _attack_low; }
    int max_attack() const { return _attack_high; }
    int magic_attack() const { return _magic_attack; }

    void set_health(int health) {
        _health = health;
        update();
    }

    int get_hit_count() { return _hit_count; }

    void set_hit_count(int count) { _triggered_hit_count = _hit_count; _hit_count = count; }

    void set_hit_count_zero() { _triggered_hit_count = _hit_count; _hit_count = 0; }

    void heal(int healing) { _health = _health + healing < _max_health ? _health + healing : _max_health; }
    void heal(double p) { _health = _health + _max_health * p < _max_health ? _health + _max_health * p : _max_health; }
    void perfect_heal() { _health = _max_health; }

    int attackage_rand() { return rand() % (_attack_high - _attack_low) + _attack_low; }

    int attackage_max() { return _attack_high; }

    int attackage_magic() { return _magic_attack * (1.0 + Trick_Hit_Count_Index * log(_triggered_hit_count - Trick_Bound + 1)); }
    int attackage_magic_dynamic(int magic_attack, int hit_count) { return magic_attack * (1.0 + Trick_Hit_Count_Index * log(hit_count - Trick_Bound + 1)); }

    void upgrade_attack_magic(int n) { _magic_attack += n; }
    void upgrade_attack_magic(double p) { _magic_attack = _magic_attack + _magic_attack * p; }

    void upgrade_attack_high (int n) { _attack_high += n; }
    void upgrade_attack_high (double p) { _attack_high = _attack_high + _attack_high * p; }

    void upgrade_attack_low (int n) { _attack_low += n; }
    void upgrade_attack_low (double p) { _attack_low = _attack_low + _attack_low * p; }

    void upgrade_max_health (int n) {
        double p = 1.0 * _health / _max_health;
        _max_health += n;
        _health = _max_health * p;
    }
    void upgrade_max_health (double p) {
        double per = 1.0 * _health / _max_health;
        _max_health = _max_health + p * _max_health;
        _health = _max_health * per;
    }

    void hit_count()
    {
        _hit_count++;
    }

    bool arrive()
    {
        if (this->x() > Hero_X_Center - Hero_Width / 2)
        {
            this->move(Hero_X_Center - Hero_Width / 2, this->y());
            return 1;
        }
        return 0;
    }

    bool alive() const { return _health > 0; }

    bool dead() const { return _health <= 0; }

    bool trick_avalible() const { return _hit_count >= Trick_Bound; }

    void start_attack_move() { _movement = 0; }

    void stop_attack_move() { _movement = 20; }

    void attack_move() {
        if (_movement < 20)
        {
            this->move(_x_standard + Hero_Attack_Movement[_movement], this->y());
            _movement++;
        }
    }

    // 更新hero的状态，尤其是血条
    void update();

    BlockLoader* block_loader() {
        return new BlockLoader(_parent, _blocks, OperationBar_Left, OperationBar_Right, OperationBar_Y_Center, _cold_time, _cold_time_bias, _block_frequancy);
    }
};

#endif // HERO_H
