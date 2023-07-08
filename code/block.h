
#ifndef BLOCK_H
#define BLOCK_H

#include <QLabel>
#include <qtimer.h>
#include "config.h"

// 预加载各Block的参数
//void preload();

class Block : public QLabel
{
    Q_OBJECT

    friend class BlockLoader;
protected:

    bool _deleteable = 0;

    int _width;

    double _max_velocity;

    double _velocity;

    bool _forward_able = 1;

    double _accelerate = Base_Red_Block_Accelerate;

    int _direction;

    int _hit_count;

    int _hit_count_bound;

    double _cur_x_center;

    int time_exist = 0;

    int _vanish_movement = 0;

    QTimer *_vanish = nullptr;

    QString _path;

signals:
    void triggered(int);
    void left_accessed();
    void right_accessed();
    void being_hit();

    void bow_shoot_arrow(int);
    void dust_revive(int);

public:
    Block(QWidget *parent, int x_center, int y_center, int length, int height,
          double velocity = 0, int direction = -1, int hit_count = 0, int hit_count_bound = 1,
          const QString & path = "");
    virtual ~Block()
    {
        if (_vanish)
            _vanish->deleteLater();
        qDebug() << "Block deleted\n";
    }

    virtual void move_on_bar();

    bool in_area(int x) const;

    bool is_deleteable() const { return _deleteable; }

    void change_direction() { _direction *= -1; }

    bool is_forward_able() const { return _forward_able; }

    void set_forward_able(bool b) { _forward_able = b; }

    virtual void hit()
    {
        _hit_count++;
        emit being_hit();
    }

    virtual void retreat(double velocity)
    {
        _velocity = velocity;
    }

    void set_velocity(double velocity)
    {
        _velocity = velocity;
    }

    virtual void trigger_access_right()
    {
        emit right_accessed();
        _deleteable = 1;
    }
    

    virtual void trigger_access_left()
    {
        emit left_accessed();
        _deleteable = 1;
    }

    virtual void trigger_hit_bound()
    {
        emit triggered(this->x() + this->width() / 2);
        _deleteable = 1;
    }

    virtual void vanish()
    {
        _vanish = new QTimer;

        this->setScaledContents(true);

        connect(_vanish, &QTimer::timeout, [this]()->void {
            if (_vanish_movement < Vanish_Movements)
            {
                this->setGeometry(_cur_x_center - _width * Vanish_Param[_vanish_movement] / 2, this->y(),
                    _width * Vanish_Param[_vanish_movement], this->height());
                //this->setPixmap(QPixmap(_path).scaled(this->size()));
                _vanish_movement++;
            }
            else
            {
                _vanish->stop();
                this->deleteLater();
            }
            });
        _cur_x_center = this->x() + _width / 2;
        _vanish->start(Time_Per_Frame);
    }

    virtual bool access_left() { return _cur_x_center < OperationBar_Left; }

    virtual bool access_right() { return false; }

};

class WhiteNormalBlock1 : public Block
{
    friend class BlockLoader;
public:
    WhiteNormalBlock1(QWidget *parent, int x_center, int y_center, 
        int length = Block_Width[WHITENormalBlock1], int height = Block_Height[WHITENormalBlock1],
        double velocity = Block_Velocity[WHITENormalBlock1], 
        int direction = -1, int hit_count = 0, int hit_count_bound = 1)
        : Block(parent, x_center, y_center, length, height, velocity, direction, hit_count, hit_count_bound, Block_Path[WHITENormalBlock1])
    {

    }
};

class WhiteNormalBlock2 : public Block
{
    friend class BlockLoader;
public:
    WhiteNormalBlock2(QWidget* parent, int x_center, int y_center,
        int length = Block_Width[WHITENormalBlock2], int height = Block_Height[WHITENormalBlock2],
        double velocity = Block_Velocity[WHITENormalBlock2],
        int direction = -1, int hit_count = 0, int hit_count_bound = 1)
        : Block(parent, x_center, y_center, length, height, velocity, direction, hit_count, hit_count_bound, Block_Path[WHITENormalBlock2])
    {

    }
};

class WhiteCriticBlock : public Block
{
    friend class BlockLoader;
public:
    WhiteCriticBlock(QWidget *parent, int x_center, int y_center, 
        int length = Block_Width[WHITECriticBlock], int height = Block_Height[WHITECriticBlock],
        double velocity = Block_Velocity[WHITECriticBlock],
        int direction = -1, int hit_count = 0, int hit_count_bound = 1)
        : Block(parent, x_center, y_center, length, height, velocity, direction, hit_count, hit_count_bound, Block_Path[WHITECriticBlock])
    {

    }
};

class WhiteSolidBlock1 : public Block
{
    friend class BlockLoader;
public:
    WhiteSolidBlock1(QWidget* parent, int x_center, int y_center,
        int length = Block_Width[WHITESolidBlock1], int height = Block_Height[WHITESolidBlock1],
        double velocity = Block_Velocity[WHITESolidBlock1],
        int direction = -1, int hit_count = 0, int hit_count_bound = 2)
        : Block(parent, x_center, y_center, length, height, velocity, direction, hit_count, hit_count_bound, Block_Path[WHITESolidBlock1])
    {

    }

    void hit() override
    {
        Block::hit();
        if (_hit_count < _hit_count_bound)
            this->setPixmap(QPixmap(_path = Block_Path[WHITESolidBlock1].chopped(4) + "_" + QString::number(_hit_count) + "hit.png"));
    }
};

class WhiteSolidBlock2 : public Block
{
    friend class BlockLoader;
public:
    WhiteSolidBlock2(QWidget* parent, int x_center, int y_center,
        int length = Block_Width[WHITESolidBlock2], int height = Block_Height[WHITESolidBlock2],
        double velocity = Block_Velocity[WHITESolidBlock2],
        int direction = -1, int hit_count = 0, int hit_count_bound = 2)
        : Block(parent, x_center, y_center, length, height, velocity, direction, hit_count, hit_count_bound, Block_Path[WHITESolidBlock2])
    {

    }

    void hit() override
    {
        Block::hit();
        if (_hit_count < _hit_count_bound)
            this->setPixmap(QPixmap(_path = Block_Path[WHITESolidBlock2].chopped(4) + "_" + QString::number(_hit_count) + "hit.png"));
    }
};

class HealingBlock: public Block
{
    friend class BlockLoader;
public:
    HealingBlock(QWidget* parent, int x_center, int y_center,
        int length = Block_Width[WHITEHealingBlock], int height = Block_Height[WHITEHealingBlock],
        double velocity = Block_Velocity[WHITEHealingBlock],
        int direction = -1, int hit_count = 0, int hit_count_bound = 1)
        : Block(parent, x_center, y_center, length, height, velocity, direction, hit_count, hit_count_bound, Block_Path[WHITEHealingBlock])
    {

    }
};

class WhiteShieldBlock : public Block
{
    friend class BlockLoader;
public:
    WhiteShieldBlock(QWidget* parent, int x_center, int y_center,
        int length = Block_Width[WHITEShieldBlock], int height = Block_Height[WHITEShieldBlock],
        double velocity = Block_Velocity[WHITEShieldBlock],
        int direction = -1, int hit_count = 0, int hit_count_bound = 1)
        : Block(parent, x_center, y_center, length, height, velocity, direction, hit_count, hit_count_bound, Block_Path[WHITEShieldBlock])
    {

    }
};

class LavaBlock: public Block
{
    friend class BlockLoader;

    int _lava_vanish = Lave_Vanish_Interval * (1000 / Time_Per_Frame), _count = 0;
public:
    LavaBlock(QWidget* parent, int x_center, int y_center,
        int length = Block_Width[WHITELavaBlock], int height = Block_Height[WHITELavaBlock],
        double velocity = Block_Velocity[WHITELavaBlock],
        int direction = -1, int hit_count = 0, int hit_count_bound = 1)
        : Block(parent, x_center, y_center, length, height, velocity, direction, hit_count, hit_count_bound, Block_Path[WHITELavaBlock])
    {

    }

    void move_on_bar() override{
        _count++;
        if (_count >= _lava_vanish)
            _deleteable = 1;
        Block::move_on_bar();
    }
};

class RedNormalBlock1 : public Block
{
    friend class BlockLoader;
public:
    RedNormalBlock1(QWidget *parent, int x_center, int y_center,
                    int length = Block_Width[REDNormalBlock1], int height = Block_Height[REDNormalBlock1],
                    double velocity = Block_Velocity[REDNormalBlock1], int direction = -1, int hit_count = 0, int hit_count_bound = 1)
        : Block(parent, x_center, y_center, length, height, velocity, direction, hit_count, hit_count_bound, Block_Path[REDNormalBlock1])
    {

    }
};

class RedNormalBlock2 : public Block
{
    friend class BlockLoader;
public:
    RedNormalBlock2(QWidget* parent, int x_center, int y_center,
        int length = Block_Width[REDNormalBlock2], int height = Block_Height[REDNormalBlock2],
        double velocity = Block_Velocity[REDNormalBlock2], int direction = -1, int hit_count = 0, int hit_count_bound = 1)
        : Block(parent, x_center, y_center, length, height, velocity, direction, hit_count, hit_count_bound, Block_Path[REDNormalBlock2])
    {

    }
};

class RedFastBlock1 : public Block
{
    friend class BlockLoader;
public:
    RedFastBlock1(QWidget *parent, int x_center, int y_center,
                  int length = Block_Width[REDFastBlock1], int height = Block_Height[REDFastBlock1],
                  double velocity = Block_Velocity[REDFastBlock1], int direction = -1, int hit_count = 0, int hit_count_bound = 1)
        : Block(parent, x_center, y_center, length, height, velocity, direction, hit_count, hit_count_bound, Block_Path[REDFastBlock1])
    {

    }
};

class RedFastBlock2 : public Block
{
    friend class BlockLoader;
public:
    RedFastBlock2(QWidget* parent, int x_center, int y_center,
        int length = Block_Width[REDFastBlock2], int height = Block_Height[REDFastBlock2],
        double velocity = Block_Velocity[REDFastBlock2], int direction = -1, int hit_count = 0, int hit_count_bound = 1)
        : Block(parent, x_center, y_center, length, height, velocity, direction, hit_count, hit_count_bound, Block_Path[REDFastBlock2])
    {

    }
};

class RedBombBlock : public Block
{
    friend class BlockLoader;
public:
    RedBombBlock(QWidget* parent, int x_center, int y_center,
        int length = Block_Width[REDBombBlock], int height = Block_Height[REDBombBlock],
        double velocity = Block_Velocity[REDBombBlock], int direction = -1, int hit_count = 0, int hit_count_bound = 1)
        : Block(parent, x_center, y_center, length, height, velocity, direction, hit_count, hit_count_bound, Block_Path[REDBombBlock])
    {

    }
};

class RedSolidBlock1 : public Block
{
    friend class BlockLoader;
public:
    RedSolidBlock1(QWidget* parent, int x_center, int y_center,
        int length = Block_Width[REDSolidBlock1], int height = Block_Height[REDSolidBlock1],
        double velocity = Block_Velocity[REDSolidBlock1], int direction = -1, int hit_count = 0, int hit_count_bound = 2)
        : Block(parent, x_center, y_center, length, height, velocity, direction, hit_count, hit_count_bound, Block_Path[REDSolidBlock1])
    {

    }

    void hit() override
    {
        Block::hit();
        if (_hit_count < _hit_count_bound)
            this->setPixmap(QPixmap(_path = Block_Path[REDSolidBlock1].chopped(4) + "_" + QString::number(_hit_count) + "hit.png"));
    }
};

class RedSolidBlock2 : public Block
{
    friend class BlockLoader;
public:
    RedSolidBlock2(QWidget* parent, int x_center, int y_center,
        int length = Block_Width[REDSolidBlock2], int height = Block_Height[REDSolidBlock2],
        double velocity = Block_Velocity[REDSolidBlock2], int direction = -1, int hit_count = 0, int hit_count_bound = 2)
        : Block(parent, x_center, y_center, length, height, velocity, direction, hit_count, hit_count_bound, Block_Path[REDSolidBlock2])
    {

    }

    void hit() override
    {
        Block::hit();
        if (_hit_count < _hit_count_bound)
            this->setPixmap(QPixmap(_path = Block_Path[REDSolidBlock2].chopped(4) + "_" + QString::number(_hit_count) + "hit.png"));
    }
};

class RedCriticalBlock: public Block
{
    friend class BlockLoader;
public:
    RedCriticalBlock(QWidget* parent, int x_center, int y_center,
        int length = Block_Width[REDCriticalBlock], int height = Block_Height[REDCriticalBlock],
        double velocity = Block_Velocity[REDCriticalBlock], int direction = -1, int hit_count = 0, int hit_count_bound = 1)
        : Block(parent, x_center, y_center, length, height, velocity, direction, hit_count, hit_count_bound, Block_Path[REDCriticalBlock])
    {

    }
};

class RedSlimeBlock: public Block
{
    friend class BlockLoader;
public:
    RedSlimeBlock(QWidget* parent, int x_center, int y_center,
        int length = Block_Width[REDSlimeBlock], int height = Block_Height[REDSlimeBlock],
        double velocity = Block_Velocity[REDSlimeBlock], int direction = -1, int hit_count = 0, int hit_count_bound = 1)
        : Block(parent, x_center, y_center, length, height, velocity, direction, hit_count, hit_count_bound, Block_Path[REDSlimeBlock])
    {

    }
};

class RedGooBlock : public Block
{
    friend class BlockLoader;
public:
    RedGooBlock(QWidget* parent, int x_center, int y_center,
        int length = Block_Width[REDGooBlock], int height = Block_Height[REDGooBlock],
        double velocity = Block_Velocity[REDGooBlock], int direction = -1, int hit_count = 0, int hit_count_bound = 1)
        : Block(parent, x_center, y_center, length, height, velocity, direction, hit_count, hit_count_bound, Block_Path[REDGooBlock])
    {

    }
};

class RedShieldBlock : public Block
{
    friend class BlockLoader;
public:
    RedShieldBlock(QWidget* parent, int x_center, int y_center,
        int length = Block_Width[REDShieldBlock], int height = Block_Height[REDShieldBlock],
        double velocity = Block_Velocity[REDShieldBlock], int direction = -1, int hit_count = 0, int hit_count_bound = 3)
        : Block(parent, x_center, y_center, length, height, velocity, direction, hit_count, hit_count_bound, Block_Path[REDShieldBlock])
    {

    }

    void hit() override
    {
        Block::hit();
        if (_hit_count < _hit_count_bound)
            this->setPixmap(QPixmap(_path = Block_Path[REDShieldBlock].chopped(4) + "_" + QString::number(_hit_count) + "hit.png"));
    }
};

class RedFireballBlock : public Block
{
    friend class BlockLoader;
public:
    RedFireballBlock(QWidget* parent, int x_center, int y_center,
        int length = Block_Width[REDFireballBlock], int height = Block_Height[REDFireballBlock],
        double velocity = Block_Velocity[REDFireballBlock], int direction = -1, int hit_count = 0, int hit_count_bound = 1 << 30)
        : Block(parent, x_center, y_center, length, height, velocity, direction, hit_count, hit_count_bound, Block_Path[REDFireballBlock])
    {
        //this->setStyleSheet("background-color:rgb(255,0,0);boarder-color:rgb(255,0,0)");
        //this->setFrameStyle(QFrame::Box);
        //this->setText("fireball");
        //this->setAlignment(Qt::AlignCenter);
    }
    bool access_right() override { return _cur_x_center > OperationBar_Right; }
    void hit() override {
        Block::hit();
        _direction *= -1;

        if (_direction == -1)
        {
            this->setPixmap(QPixmap(Block_Path[REDFireballBlock]));
        }
        else
        {
            this->setPixmap(QPixmap::fromImage(QPixmap(Block_Path[REDFireballBlock]).toImage().mirrored(true, false)));
        }
    }
};

class RedIceballBlock : public Block
{
    friend class BlockLoader;
public:
    RedIceballBlock(QWidget* parent, int x_center, int y_center,
        int length = Block_Width[REDIceballBlock], int height = Block_Height[REDIceballBlock],
        double velocity = Block_Velocity[REDIceballBlock], int direction = -1, int hit_count = 0, int hit_count_bound = 2)
        : Block(parent, x_center, y_center, length, height, velocity, direction, hit_count, hit_count_bound, Block_Path[REDIceballBlock])
    {
        //this->setStyleSheet("background-color:rgb(255,0,0);boarder-color:rgb(255,0,0)");
        //this->setFrameStyle(QFrame::Box);
        //this->setText("iceball\n2");
        //this->setAlignment(Qt::AlignCenter);
    }

    void hit() override
    {
        Block::hit();
        _max_velocity = 1.0;
    }
};

class RedArmorBlock : public Block
{
    friend class BlockLoader;

    int _velocity_change = Armor_Move_Interval * (1000 / Time_Per_Frame), _count = 0;

public:
    RedArmorBlock(QWidget* parent, int x_center, int y_center,
        int length = Block_Width[REDArmorBlock], int height = Block_Height[REDArmorBlock],
        double velocity = Block_Velocity[REDArmorBlock], int direction = -1, int hit_count = 0, int hit_count_bound = 3)
        : Block(parent, x_center, y_center, length, height, velocity, direction, hit_count, hit_count_bound, Block_Path[REDArmorBlock])
    {
        //this->setStyleSheet("background-color:rgb(255,0,0);boarder-color:rgb(255,0,0)");
        //this->setFrameStyle(QFrame::Box);
        //this->setText("armor\n3");
        //this->setAlignment(Qt::AlignCenter);
    }

    virtual void move_on_bar() override
    {
        _count++;
        if (_velocity_change == _count)
        {
            _count = 0;
            set_forward_able(!is_forward_able());
        }
        Block::move_on_bar();
    }

    void hit() override
    {
        Block::hit();
        if (_hit_count < _hit_count_bound)
            this->setPixmap(QPixmap(_path = Block_Path[REDArmorBlock].chopped(4) + "_" + QString::number(_hit_count) + "hit.png"));
    }
};

class RedBowBlock : public Block
{
    friend class BlockLoader;

    int _velocity_change = Bow_Move_Interval * (1000 / Time_Per_Frame), _v_count = 0;
    int _shoot_bound = Bow_Shoot_Interval * (1000 / Time_Per_Frame), _s_count = 0;
public:
    RedBowBlock(QWidget* parent, int x_center, int y_center,
        int length = Block_Width[REDBowBlock], int height = Block_Height[REDBowBlock],
        double velocity = Block_Velocity[REDBowBlock], int direction = -1, int hit_count = 0, int hit_count_bound = 1)
        : Block(parent, x_center, y_center, length, height, velocity, direction, hit_count, hit_count_bound, Block_Path[REDBowBlock])
    {
        //this->setStyleSheet("background-color:rgb(255,0,0);boarder-color:rgb(255,0,0)");
        //this->setFrameStyle(QFrame::Box);
        //this->setText("bow");
        //this->setAlignment(Qt::AlignCenter);
    }

    virtual void move_on_bar() override
    {
        _v_count++;
        if (_velocity_change == _v_count)
        {
            _v_count = 0;
            set_forward_able(!is_forward_able());
        }
        _s_count++;
        if (_shoot_bound <= _s_count && _cur_x_center > Main_Window_Width / 2 - 100)
        {
            _s_count = 0;
            emit bow_shoot_arrow(this->x() + this->width() / 2);
        }
        Block::move_on_bar();
    }
};

class RedArrowBlock : public Block
{
    friend class BlockLoader;
public:
    RedArrowBlock(QWidget* parent, int x_center, int y_center,
        int length = Block_Width[REDArrowBlock], int height = Block_Height[REDArrowBlock],
        double velocity = Block_Velocity[REDArrowBlock], int direction = -1, int hit_count = 0, int hit_count_bound = 1)
        : Block(parent, x_center, y_center, length, height, velocity, direction, hit_count, hit_count_bound, Block_Path[REDArrowBlock])
    {
        //this->setStyleSheet("background-color:rgb(255,0,0);boarder-color:rgb(255,0,0)");
        //this->setFrameStyle(QFrame::Box);
        //this->setText("arrow");
        //this->setAlignment(Qt::AlignCenter);
    }
};

class RedSoulingBlock1 : public Block
{
    friend class BlockLoader;
public:
    RedSoulingBlock1(QWidget* parent, int x_center, int y_center,
        int length = Block_Width[REDSoulingBlock1], int height = Block_Height[REDSoulingBlock1],
        double velocity = Block_Velocity[REDSoulingBlock1], int direction = -1, int hit_count = 0, int hit_count_bound = 1)
        : Block(parent, x_center, y_center, length, height, velocity, direction, hit_count, hit_count_bound, Block_Path[REDSoulingBlock1])
    {
        //this->setStyleSheet("background-color:rgb(255,0,0);boarder-color:rgb(255,0,0)");
        //this->setFrameStyle(QFrame::Box);
        //this->setText("soul");
        //this->setAlignment(Qt::AlignCenter);
    }
};

class RedSoulingBlock2 : public Block
{
    friend class BlockLoader;
public:
    RedSoulingBlock2(QWidget* parent, int x_center, int y_center,
        int length = Block_Width[REDSoulingBlock2], int height = Block_Height[REDSoulingBlock2],
        double velocity = Block_Velocity[REDSoulingBlock2], int direction = -1, int hit_count = 0, int hit_count_bound = 1)
        : Block(parent, x_center, y_center, length, height, velocity, direction, hit_count, hit_count_bound, Block_Path[REDSoulingBlock2])
    {
        //this->setStyleSheet("background-color:rgb(255,0,0);boarder-color:rgb(255,0,0)");
        //this->setFrameStyle(QFrame::Box);
        //this->setText("soul");
        //this->setAlignment(Qt::AlignCenter);
    }
};

class RedBoneBlock : public Block
{
    friend class BlockLoader;
public:
    RedBoneBlock(QWidget* parent, int x_center, int y_center,
        int length = Block_Width[REDBoneBlock], int height = Block_Height[REDBoneBlock],
        double velocity = Block_Velocity[REDBoneBlock], int direction = -1, int hit_count = 0, int hit_count_bound = 1)
        : Block(parent, x_center, y_center, length, height, velocity, direction, hit_count, hit_count_bound, Block_Path[REDBoneBlock])
    {
        //this->setStyleSheet("background-color:rgb(255,0,0);boarder-color:rgb(255,0,0)");
        //this->setFrameStyle(QFrame::Box);
        //this->setText("bone");
        //this->setAlignment(Qt::AlignCenter);
    }
};

class RedDustBlock : public Block
{
    friend class BlockLoader;

    int _revive_bound = Dust_Rivive_Interval * (1000 / Time_Per_Frame), _count = 0;

public:
    RedDustBlock(QWidget* parent, int x_center, int y_center,
        int length = Block_Width[REDDustBlock], int height = Block_Height[REDDustBlock],
        double velocity = Block_Velocity[REDDustBlock], int direction = -1, int hit_count = 0, int hit_count_bound = 1)
        : Block(parent, x_center, y_center, length, height, velocity, direction, hit_count, hit_count_bound, Block_Path[REDDustBlock])
    {
        _forward_able = 0;
        //this->setStyleSheet("background-color:rgb(255,0,0);boarder-color:rgb(255,0,0)");
        //this->setFrameStyle(QFrame::Box);
        //this->setText("dust");
        //this->setAlignment(Qt::AlignCenter);
    }

    void move_on_bar() override
    {
        _count++;
        if (_count >= _revive_bound)
        {
            emit dust_revive(this->x() + this->width() / 2);
            _deleteable = 1;
        }
    }
};

class RedDeadBlock : public Block
{
    friend class BlockLoader;
public:
    RedDeadBlock(QWidget* parent, int x_center, int y_center,
        int length = Block_Width[REDDeadBlock], int height = Block_Height[REDDeadBlock],
        double velocity = Block_Velocity[REDDeadBlock], int direction = -1, int hit_count = 0, int hit_count_bound = 1 << 30)
        : Block(parent, x_center, y_center, length, height, velocity, direction, hit_count, hit_count_bound, Block_Path[REDDeadBlock])
    {
        //this->setStyleSheet("background-color:rgb(255,0,0);boarder-color:rgb(255,0,0)");
        //this->setFrameStyle(QFrame::Box);
        //this->setText("dead");
        //this->setAlignment(Qt::AlignCenter);
    }
};

class WhiteSwordBlock : public Block
{
    friend class BlockLoader;
public:
    WhiteSwordBlock(QWidget* parent, int x_center, int y_center,
        int length = Block_Width[WHITESwordBlock], int height = Block_Height[WHITESwordBlock],
        double velocity = Block_Velocity[WHITESwordBlock], int direction = -1, int hit_count = 0, int hit_count_bound = 1 << 30)
        : Block(parent, x_center, y_center, length, height, velocity, direction, hit_count, hit_count_bound, Block_Path[WHITESwordBlock])
    {
        //this->setStyleSheet("background-color:rgb(255,255,255)");
        //this->setFrameStyle(QFrame::Box);
        //this->setText("sword");
        //this->setAlignment(Qt::AlignCenter);
    }
};


#endif // BLOCK_H
