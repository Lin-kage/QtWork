
#ifndef ENEMY_H
#define ENEMY_H

#include "blockloader.h"
#include <cstdlib>
#include "config.h"
#include "jumpnumber.h"

class Enemy : public QLabel
{
protected:
    QWidget *_parent;

    int _max_health, _health;

    int _attack_low, _attack_high;

    QLabel *_max_health_bar, *_health_bar, *_health_text;

    QPixmap *_image;

    // 一些用于BLockLoader的参数，代表了Enemy的攻击属性
    int _cold_time, _cold_time_bias;
    std::vector<int> _block_codes;
    double _block_frecuancy;

    QLabel *_sword_icon, *_attack_info;

    int _movement = 20, _x_standard = Enemy_X_Center - Enemy_Width / 2;

    bool _jumpnumber_on;

public:

    void in_stage(int stage)
    {
        if (stage == 1)
        {
            _attack_info->setStyleSheet("color:rgb(0,0,0)");
        }
        else if (stage == 2)
        {
            _attack_info->setStyleSheet("color:rgb(220,220,220)");
        }
        else if (stage == 3)
        {
            _attack_info->setStyleSheet("color:rgb(0,0,0)");
        }
        else if (stage == 4)
        {
            _attack_info->setStyleSheet("color:rgb(0,0,0)");
        }
    }

    void set_jumpnumber(bool b) { _jumpnumber_on = b; }

    bool arrive()
    {
        if (this->x() <= Enemy_X_Center - Enemy_Width / 2)
        {
            this->move(Enemy_X_Center - Enemy_Width / 2, Enemy_Y_Bottom - Enemy_Height);
            return 1;
        }
        return 0;
    }

    void rotate_image()
    {
        QImage temp = _image->toImage();
        temp = temp.mirrored(true, false);

        qDebug() << "Rotated\n";

        this->setPixmap(QPixmap::fromImage(temp));
    }

    bool fled()
    {
        if (this->x() > Main_Window_Width)
        {
            return 1;
        }
        return 0;
    }

    Enemy(QWidget *parent, int max_health = 40, int min_attack = 5, int max_attack = 8,
          int cold_time = Standard_Cold_Time, int cold_time_bias = Standard_Cold_Time_Bias,
          const std::vector<int> & blocks = Red_Blocks, double block_frecuancy = Standard_Block_Frequancy,
          QString img_address = "");

    virtual ~Enemy() {
        _max_health_bar->deleteLater();
        _health_bar->deleteLater();
        _sword_icon->deleteLater();
        _attack_info->deleteLater();
        _health_text->deleteLater();
        delete _image;
        qDebug() << "enemy deleted\n";
    }

    void upgrade(double p)
    {
        _health = _max_health = _max_health * p;
        _attack_low = _attack_low * p / 1.6;
        _attack_high = _attack_high * p / 1.6;
    }

    bool alive() const { return _health > 0; }
    bool dead() const { return _health <= 0; }

    virtual void physical_hurt(int damage) {
        _health -= damage;
        if (_jumpnumber_on)
            new JumpNumber(_parent, damage, Right_JumpNumber_X, Right_JumpNumber_Y, 1);
    }

    virtual void magical_hurt(int damage) {
        _health -= damage;
        if (_jumpnumber_on)
            new JumpNumber(_parent, damage, Right_JumpNumber_X, Right_JumpNumber_Y, 1);
    }
    
    void hurt(int damage) {
        _health -= damage;
        if (_jumpnumber_on)
            new JumpNumber(_parent, damage, Right_JumpNumber_X, Right_JumpNumber_Y, 1);
    }

    virtual void heal(int healing) { _health = _health + healing < _max_health ? _health + healing : _max_health; }

    virtual int attackage_rand() { return rand() % (_attack_high - _attack_low) + _attack_low; }
    virtual int attackage_max() { return _attack_high; }

    void start_attack_move() { _movement = 0; }
    void stop_attack_movement() { _movement = 20; }

    void attack_move()
    {
        if (_movement < 20)
        {
            this->move(_x_standard + Enemy_Attack_Movement[_movement], this->y());
            _movement++;
        }
    }

    BlockLoader* block_loader(){
        return new BlockLoader(_parent, _block_codes, OperationBar_Left, OperationBar_Right, OperationBar_Y_Center, _cold_time, _cold_time_bias, _block_frecuancy);
    }

    void update();
};

class Slime : public Enemy
{
public:
    Slime(QWidget *parent, int max_health = EnemyMaxHealth[SLIME], int min_attack = EnemyAttack[SLIME][0], int max_attack = EnemyAttack[SLIME][1],
          const std::vector<int> block_codes = EnemyBlocks[SLIME],
          int cold_time = EnemyColdTime[SLIME][0], int cold_time_bias = EnemyColdTime[SLIME][1], double block_frecuancy = 1.0)
        : Enemy(parent, max_health, min_attack, max_attack, cold_time, cold_time_bias, EnemyBlocks[SLIME], block_frecuancy, ImgAddress[SLIME])
    {

    }
};

class Treant : public Enemy
{
public:
    Treant(QWidget* parent, int max_health = EnemyMaxHealth[TREANT], int min_attack = EnemyAttack[TREANT][0], int max_attack = EnemyAttack[TREANT][1],
        const std::vector<int> block_codes = EnemyBlocks[TREANT],
        int cold_time = EnemyColdTime[TREANT][0], int cold_time_bias = EnemyColdTime[TREANT][1], double block_frecuancy = 1.0)
        : Enemy(parent, max_health, min_attack, max_attack, cold_time, cold_time_bias, EnemyBlocks[TREANT], block_frecuancy, ImgAddress[TREANT])
    {

    }

    void magical_hurt(int damage) override
    {
        hurt(damage * 2);
    }
};

class Leprechaun : public Enemy
{
public:
    Leprechaun(QWidget *parent, int max_health = EnemyMaxHealth[LEPRECHAUN], int min_attack = EnemyAttack[LEPRECHAUN][0], int max_attack = EnemyAttack[LEPRECHAUN][1],
           const std::vector<int> block_codes = EnemyBlocks[LEPRECHAUN],
           int cold_time = EnemyColdTime[LEPRECHAUN][0], int cold_time_bias = EnemyColdTime[LEPRECHAUN][1], double block_frecuancy = 1.0)
        : Enemy(parent, max_health, min_attack, max_attack, cold_time, cold_time_bias, EnemyBlocks[LEPRECHAUN], block_frecuancy, ImgAddress[LEPRECHAUN])
    {
        //this->setText("Leprechuan");
        //this->setAlignment(Qt::AlignCenter);
        //this->setFrameStyle(QFrame::Box);
    }
};

class Beast : public Enemy
{
public:
    Beast(QWidget *parent, int max_health = EnemyMaxHealth[BEAST], int min_attack = EnemyAttack[BEAST][0], int max_attack = EnemyAttack[BEAST][1],
           const std::vector<int> block_codes = EnemyBlocks[BEAST],
           int cold_time = EnemyColdTime[BEAST][0], int cold_time_bias = EnemyColdTime[BEAST][1], double block_frecuancy = 1.0)
        : Enemy(parent, max_health, min_attack, max_attack, cold_time, cold_time_bias, EnemyBlocks[BEAST], block_frecuancy, ImgAddress[BEAST])
    {
        //this->setText("Beast");
        //this->setAlignment(Qt::AlignCenter);
        //this->setFrameStyle(QFrame::Box);
    }
};

class Goblin : public Enemy
{
public:
    Goblin(QWidget *parent, int max_health = EnemyMaxHealth[GOBLIN], int min_attack = EnemyAttack[GOBLIN][0], int max_attack = EnemyAttack[GOBLIN][1],
             const std::vector<int> block_codes = EnemyBlocks[GOBLIN],
             int cold_time = EnemyColdTime[GOBLIN][0], int cold_time_bias = EnemyColdTime[GOBLIN][1], double block_frecuancy = 1.0)
        : Enemy(parent, max_health, min_attack, max_attack, cold_time, cold_time_bias, EnemyBlocks[GOBLIN], block_frecuancy, ImgAddress[GOBLIN])
    {
        //this->setText("Goblin");
        //this->setAlignment(Qt::AlignCenter);
        //this->setFrameStyle(QFrame::Box);
    }
};

class SlimeQueen : public Enemy
{
public:
    SlimeQueen(QWidget *parent, int max_health = EnemyMaxHealth[SLIMEQUEEN], int min_attack = EnemyAttack[SLIMEQUEEN][0], int max_attack = EnemyAttack[SLIMEQUEEN][1],
           const std::vector<int> block_codes = EnemyBlocks[SLIMEQUEEN],
           int cold_time = EnemyColdTime[SLIMEQUEEN][0], int cold_time_bias = EnemyColdTime[SLIMEQUEEN][1], double block_frecuancy = 1.0)
        : Enemy(parent, max_health, min_attack, max_attack, cold_time, cold_time_bias, EnemyBlocks[SLIMEQUEEN], block_frecuancy, ImgAddress[SLIMEQUEEN])
    {
        //this->setText("SlimeQueen");
        //this->setAlignment(Qt::AlignCenter);
        //this->setFrameStyle(QFrame::Box);
    }
};

class Monster : public Enemy
{
public:
    Monster(QWidget *parent, int max_health = EnemyMaxHealth[MONSTER], int min_attack = EnemyAttack[MONSTER][0], int max_attack = EnemyAttack[MONSTER][1],
           const std::vector<int> block_codes = EnemyBlocks[MONSTER],
           int cold_time = EnemyColdTime[MONSTER][0], int cold_time_bias = EnemyColdTime[MONSTER][1], double block_frecuancy = 1.0)
        : Enemy(parent, max_health, min_attack, max_attack, cold_time, cold_time_bias, EnemyBlocks[MONSTER], block_frecuancy, ImgAddress[MONSTER])
    {
        //this->setText("Monster");
        //this->setAlignment(Qt::AlignCenter);
        //this->setFrameStyle(QFrame::Box);
    }
};

class Bat : public Enemy
{
public:
    Bat(QWidget *parent, int max_health = EnemyMaxHealth[BAT], int min_attack = EnemyAttack[BAT][0], int max_attack = EnemyAttack[BAT][1],
           const std::vector<int> block_codes = EnemyBlocks[BAT],
           int cold_time = EnemyColdTime[BAT][0], int cold_time_bias = EnemyColdTime[BAT][1], double block_frecuancy = 1.0)
        : Enemy(parent, max_health, min_attack, max_attack, cold_time, cold_time_bias, EnemyBlocks[BAT], block_frecuancy, ImgAddress[BAT])
    {
        //this->setText("Bat");
        //this->setAlignment(Qt::AlignCenter);
        //this->setFrameStyle(QFrame::Box);
    }

    void physical_hurt(int damage) override
    {
        hurt(damage / 2);
    }
};

class Golem : public Enemy
{
public:
    Golem(QWidget *parent, int max_health = EnemyMaxHealth[GOLEM], int min_attack = EnemyAttack[GOLEM][0], int max_attack = EnemyAttack[GOLEM][1],
            const std::vector<int> block_codes = EnemyBlocks[GOLEM],
            int cold_time = EnemyColdTime[GOLEM][0], int cold_time_bias = EnemyColdTime[GOLEM][1], double block_frecuancy = 1.0)
        : Enemy(parent, max_health, min_attack, max_attack, cold_time, cold_time_bias, EnemyBlocks[GOLEM], block_frecuancy, ImgAddress[GOLEM])
    {
        //this->setText("Golem");
        //this->setAlignment(Qt::AlignCenter);
        //this->setFrameStyle(QFrame::Box);
    }
};

class StoneSlime : public Enemy
{
public:
    StoneSlime(QWidget *parent, int max_health = EnemyMaxHealth[STONESLIME], int min_attack = EnemyAttack[STONESLIME][0], int max_attack = EnemyAttack[STONESLIME][1],
          const std::vector<int> block_codes = EnemyBlocks[STONESLIME],
          int cold_time = EnemyColdTime[STONESLIME][0], int cold_time_bias = EnemyColdTime[STONESLIME][1], double block_frecuancy = 1.0)
        : Enemy(parent, max_health, min_attack, max_attack, cold_time, cold_time_bias, EnemyBlocks[STONESLIME], block_frecuancy, ImgAddress[STONESLIME])
    {
        //this->setText("StoneSlime");
        //this->setAlignment(Qt::AlignCenter);
        //this->setFrameStyle(QFrame::Box);
    }
};

class Skeleton : public Enemy
{
public:
    Skeleton(QWidget *parent, int max_health = EnemyMaxHealth[SKELETON], int min_attack = EnemyAttack[SKELETON][0], int max_attack = EnemyAttack[SKELETON][1],
            const std::vector<int> block_codes = EnemyBlocks[SKELETON],
            int cold_time = EnemyColdTime[SKELETON][0], int cold_time_bias = EnemyColdTime[SKELETON][1], double block_frecuancy = 1.0)
        : Enemy(parent, max_health, min_attack, max_attack, cold_time, cold_time_bias, EnemyBlocks[SKELETON], block_frecuancy, ImgAddress[SKELETON])
    {

    }
};

class GiantGolem : public Enemy
{
public:
    GiantGolem(QWidget* parent, int max_health = EnemyMaxHealth[GIANTGOLEM], int min_attack = EnemyAttack[GIANTGOLEM][0], int max_attack = EnemyAttack[GIANTGOLEM][1],
        const std::vector<int> block_codes = EnemyBlocks[GIANTGOLEM],
        int cold_time = EnemyColdTime[GIANTGOLEM][0], int cold_time_bias = EnemyColdTime[GIANTGOLEM][1], double block_frecuancy = 1.0)
        : Enemy(parent, max_health, min_attack, max_attack, cold_time, cold_time_bias, EnemyBlocks[GIANTGOLEM], block_frecuancy, ImgAddress[GIANTGOLEM])
    {
        //this->setText("GiantGolem");
        //this->setAlignment(Qt::AlignCenter);
        //this->setFrameStyle(QFrame::Box);
    }
};

class Medusa : public Enemy
{
public:
    Medusa(QWidget* parent, int max_health = EnemyMaxHealth[MEDUSA], int min_attack = EnemyAttack[MEDUSA][0], int max_attack = EnemyAttack[MEDUSA][1],
        const std::vector<int> block_codes = EnemyBlocks[MEDUSA],
        int cold_time = EnemyColdTime[MEDUSA][0], int cold_time_bias = EnemyColdTime[MEDUSA][1], double block_frecuancy = 1.0)
        : Enemy(parent, max_health, min_attack, max_attack, cold_time, cold_time_bias, EnemyBlocks[MEDUSA], block_frecuancy, ImgAddress[MEDUSA])
    {
        //this->setText("Medusa");
        //this->setAlignment(Qt::AlignCenter);
        //this->setFrameStyle(QFrame::Box);
    }
};

class Guard : public Enemy
{
public:
    Guard(QWidget* parent, int max_health = EnemyMaxHealth[GUARD], int min_attack = EnemyAttack[GUARD][0], int max_attack = EnemyAttack[GUARD][1],
        const std::vector<int> block_codes = EnemyBlocks[GUARD],
        int cold_time = EnemyColdTime[GUARD][0], int cold_time_bias = EnemyColdTime[GUARD][1], double block_frecuancy = 1.0)
        : Enemy(parent, max_health, min_attack, max_attack, cold_time, cold_time_bias, EnemyBlocks[GUARD], block_frecuancy, ImgAddress[GUARD])
    {
        //this->setText("Guard");
        //this->setAlignment(Qt::AlignCenter);
        //this->setFrameStyle(QFrame::Box);
    }
};

class Archer : public Enemy
{
public:
    Archer(QWidget* parent, int max_health = EnemyMaxHealth[ARCHER], int min_attack = EnemyAttack[ARCHER][0], int max_attack = EnemyAttack[ARCHER][1],
        const std::vector<int> block_codes = EnemyBlocks[ARCHER],
        int cold_time = EnemyColdTime[ARCHER][0], int cold_time_bias = EnemyColdTime[ARCHER][1], double block_frecuancy = 1.0)
        : Enemy(parent, max_health, min_attack, max_attack, cold_time, cold_time_bias, EnemyBlocks[ARCHER], block_frecuancy, ImgAddress[ARCHER])
    {
        //this->setText("Archer");
        //this->setAlignment(Qt::AlignCenter);
        //this->setFrameStyle(QFrame::Box);
    }
};

class Wizard : public Enemy
{
public:
    Wizard(QWidget* parent, int max_health = EnemyMaxHealth[WIZARD], int min_attack = EnemyAttack[WIZARD][0], int max_attack = EnemyAttack[WIZARD][1],
        const std::vector<int> block_codes = EnemyBlocks[WIZARD],
        int cold_time = EnemyColdTime[WIZARD][0], int cold_time_bias = EnemyColdTime[WIZARD][1], double block_frecuancy = 1.0)
        : Enemy(parent, max_health, min_attack, max_attack, cold_time, cold_time_bias, EnemyBlocks[WIZARD], block_frecuancy, ImgAddress[WIZARD])
    {
        //this->setText("Wizard");
        //this->setAlignment(Qt::AlignCenter);
        //this->setFrameStyle(QFrame::Box);
    }

    void magical_hurt(int damage) override
    {
        hurt(damage / 2);
    }
};

class Shield : public Enemy
{
public:
    Shield(QWidget* parent, int max_health = EnemyMaxHealth[SHIELD], int min_attack = EnemyAttack[SHIELD][0], int max_attack = EnemyAttack[SHIELD][1],
        const std::vector<int> block_codes = EnemyBlocks[SHIELD],
        int cold_time = EnemyColdTime[SHIELD][0], int cold_time_bias = EnemyColdTime[SHIELD][1], double block_frecuancy = 1.0)
        : Enemy(parent, max_health, min_attack, max_attack, cold_time, cold_time_bias, EnemyBlocks[SHIELD], block_frecuancy, ImgAddress[SHIELD])
    {   
        //this->setText("Shield");
        //this->setAlignment(Qt::AlignCenter);
        //this->setFrameStyle(QFrame::Box);
    }
};

class DarkKing : public Enemy
{
public:
    DarkKing(QWidget* parent, int max_health = EnemyMaxHealth[DARKKING], int min_attack = EnemyAttack[DARKKING][0], int max_attack = EnemyAttack[DARKKING][1],
        const std::vector<int> block_codes = EnemyBlocks[DARKKING],
        int cold_time = EnemyColdTime[DARKKING][0], int cold_time_bias = EnemyColdTime[DARKKING][1], double block_frecuancy = 1.0)
        : Enemy(parent, max_health, min_attack, max_attack, cold_time, cold_time_bias, EnemyBlocks[DARKKING], block_frecuancy, ImgAddress[DARKKING])
    {
        //this->setText("Darkking");
        //this->setAlignment(Qt::AlignCenter);
        //this->setFrameStyle(QFrame::Box);
    }
};

class Melin : public Enemy
{
public:
    Melin(QWidget* parent, int max_health = EnemyMaxHealth[MELIN], int min_attack = EnemyAttack[MELIN][0], int max_attack = EnemyAttack[MELIN][1],
        const std::vector<int> block_codes = EnemyBlocks[MELIN],
        int cold_time = EnemyColdTime[MELIN][0], int cold_time_bias = EnemyColdTime[MELIN][1], double block_frecuancy = 1.0)
        : Enemy(parent, max_health, min_attack, max_attack, cold_time, cold_time_bias, EnemyBlocks[MELIN], block_frecuancy, ImgAddress[MELIN])
    {
        //this->setText("Melin");
        //this->setAlignment(Qt::AlignCenter);
        //this->setFrameStyle(QFrame::Box);
    }

    void magical_hurt(int damage)
    {
        hurt(damage / 2);
    }

    void heal(int healing) override
    {
        Enemy::heal(healing * 3);
    }
};

class LavaSlime : public Enemy
{
public:
    LavaSlime(QWidget* parent, int max_health = EnemyMaxHealth[LAVASLIME], int min_attack = EnemyAttack[LAVASLIME][0], int max_attack = EnemyAttack[LAVASLIME][1],
        const std::vector<int> block_codes = EnemyBlocks[LAVASLIME],
        int cold_time = EnemyColdTime[LAVASLIME][0], int cold_time_bias = EnemyColdTime[LAVASLIME][1], double block_frecuancy = 1.0)
        : Enemy(parent, max_health, min_attack, max_attack, cold_time, cold_time_bias, EnemyBlocks[LAVASLIME], block_frecuancy, ImgAddress[LAVASLIME])
    {
        //this->setText("LavaSlime");
        //this->setAlignment(Qt::AlignCenter);
        //this->setFrameStyle(QFrame::Box);
    }
};

class Demon : public Enemy
{
public:
    Demon(QWidget* parent, int max_health = EnemyMaxHealth[DEMON], int min_attack = EnemyAttack[DEMON][0], int max_attack = EnemyAttack[DEMON][1],
        const std::vector<int> block_codes = EnemyBlocks[DEMON],
        int cold_time = EnemyColdTime[DEMON][0], int cold_time_bias = EnemyColdTime[DEMON][1], double block_frecuancy = 1.0)
        : Enemy(parent, max_health, min_attack, max_attack, cold_time, cold_time_bias, EnemyBlocks[DEMON], block_frecuancy, ImgAddress[DEMON])
    {
        //this->setText("Demon");
        //this->setAlignment(Qt::AlignCenter);
        //this->setFrameStyle(QFrame::Box);
    }
};

class UndeadSkeleton : public Enemy
{
public:
    UndeadSkeleton(QWidget* parent, int max_health = EnemyMaxHealth[UNDEADSKELETON], int min_attack = EnemyAttack[UNDEADSKELETON][0], int max_attack = EnemyAttack[UNDEADSKELETON][1],
        const std::vector<int> block_codes = EnemyBlocks[UNDEADSKELETON],
        int cold_time = EnemyColdTime[UNDEADSKELETON][0], int cold_time_bias = EnemyColdTime[UNDEADSKELETON][1], double block_frecuancy = 1.0)
        : Enemy(parent, max_health, min_attack, max_attack, cold_time, cold_time_bias, EnemyBlocks[UNDEADSKELETON], block_frecuancy, ImgAddress[UNDEADSKELETON])
    {
        //this->setText("Undead\nSkeleton");
        //this->setAlignment(Qt::AlignCenter);
        //this->setFrameStyle(QFrame::Box);
    }

    int attackage_rand() override
    {
        int t = Enemy::attackage_rand();
        heal(t);
        return t;
    }
};

class Succubus : public Enemy
{
public:
    Succubus(QWidget* parent, int max_health = EnemyMaxHealth[SUCCUBUS], int min_attack = EnemyAttack[SUCCUBUS][0], int max_attack = EnemyAttack[SUCCUBUS][1],
        const std::vector<int> block_codes = EnemyBlocks[SUCCUBUS],
        int cold_time = EnemyColdTime[SUCCUBUS][0], int cold_time_bias = EnemyColdTime[SUCCUBUS][1], double block_frecuancy = 1.0)
        : Enemy(parent, max_health, min_attack, max_attack, cold_time, cold_time_bias, EnemyBlocks[SUCCUBUS], block_frecuancy, ImgAddress[SUCCUBUS])
    {
        //this->setText("Succubus");
        //this->setAlignment(Qt::AlignCenter);
        //this->setFrameStyle(QFrame::Box);
    }

    void physical_hurt(int damage)
    {
        if (_jumpnumber_on)
            new JumpNumber(_parent, "Immused", Right_JumpNumber_X, Right_JumpNumber_Y, 1);
    }
};

class TheDeath : public Enemy
{
public:
    TheDeath(QWidget* parent, int max_health = EnemyMaxHealth[THEDEATH], int min_attack = EnemyAttack[THEDEATH][0], int max_attack = EnemyAttack[THEDEATH][1],
        const std::vector<int> block_codes = EnemyBlocks[THEDEATH],
        int cold_time = EnemyColdTime[THEDEATH][0], int cold_time_bias = EnemyColdTime[THEDEATH][1], double block_frecuancy = 1.0)
        : Enemy(parent, max_health, min_attack, max_attack, cold_time, cold_time_bias, EnemyBlocks[THEDEATH], block_frecuancy, ImgAddress[THEDEATH])
    {
        //this->setText("The Death");
        //this->setAlignment(Qt::AlignCenter);
        //this->setFrameStyle(QFrame::Box);
    }
};

class TheCreator : public Enemy
{
public:
    TheCreator(QWidget* parent, int max_health = EnemyMaxHealth[THECREATOR], int min_attack = EnemyAttack[THECREATOR][0], int max_attack = EnemyAttack[THECREATOR][1],
        const std::vector<int> block_codes = EnemyBlocks[THECREATOR],
        int cold_time = EnemyColdTime[THECREATOR][0], int cold_time_bias = EnemyColdTime[THECREATOR][1], double block_frecuancy = 1.0)
        : Enemy(parent, max_health, min_attack, max_attack, cold_time, cold_time_bias, EnemyBlocks[THECREATOR], block_frecuancy, ImgAddress[THECREATOR])
    {
        //this->setText("The Creator");
        //this->setAlignment(Qt::AlignCenter);
        //this->setFrameStyle(QFrame::Box);
    }
};


#endif // ENEMY_H
