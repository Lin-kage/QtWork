
#ifndef OPERATIONBAR_H
#define OPERATIONBAR_H

#include <QLabel>
#include "movingsign.h"
#include "blockloader.h"
#include "config.h"

class OperationBar : public QLabel
{
    Q_OBJECT

    friend class BlockLoader;
private:
    QWidget *_parent;

    int _left_center, _right_center, _y_center;
    // 浮标类
    MovingSign *_movingSign = nullptr;

    BlockLoader *_white_block_loader = nullptr, *_red_block_loader = nullptr;

    int _valid_length;

    int get_sign_value()
    {
        return _movingSign->get_pos_hit();
    }

signals:
    void hero_normal_attack();
    void hero_critic_attack();
    void hero_magic_attack();
    void enemy_normal_attack();
    void enemy_critic_attack();
    void enemy_deadly_attack();
    void enemy_fireball_hurt();

    void hero_healing();
    void hero_get_sheild();
    void hero_lava_hurt();
    void enemy_steal_health();

private slots:
    void bomb_clash(int x_center)
    {
        _white_block_loader->bomb_clear_blocks(x_center, Bomb_Radius);
        _red_block_loader->bomb_clear_blocks(x_center, Bomb_Radius);
    }
    void slime_split(int x_center)
    {
        _red_block_loader->generate_block_forced(x_center - Block_Width[REDGooBlock] / 2, REDGooBlock, _red_block_loader->front_block());
        _red_block_loader->generate_block_forced(x_center + Block_Width[REDGooBlock] / 2, REDGooBlock, _red_block_loader->front_block());
    }
    void bow_shoot_arrow(int x_center)
    {
        _red_block_loader->generate_block_forced(x_center, REDArrowBlock, _red_block_loader->front_block());
    }
    void generate_dust(int x_center)
    {
        _red_block_loader->generate_block_forced(x_center, REDDustBlock, _red_block_loader->front_block());
    }
    void generate_bone(int x_center)
    {
        _red_block_loader->generate_block_forced(x_center, REDBoneBlock, _red_block_loader->front_block());
    }

public:

    // OperationBar不会自定义block_loader，但会尝试将其析构
    OperationBar(QWidget *parent,
                 const int x = OperationBar_X_Center - OperationBar_Width / 2,
                 const int y = OperationBar_Y_Center - OperationBar_Height / 2,
                 const int length = OperationBar_Width, const int height = OperationBar_Height);

    ~OperationBar() { 
        qDebug() << "Bar deleted\n";
        delete _white_block_loader;
        delete _red_block_loader;
    }

    void set_moving_sign(MovingSign *moving_sign)
    {
        if (_movingSign)
            _movingSign->deleteLater();
        _movingSign = moving_sign;
    }

    int left_center() const { return _left_center; }

    void sign_moving()
    {
        _movingSign->move_on_bar();
    }

    void blocks_moving()
    {
        _white_block_loader->move_blocks();
        _red_block_loader->move_blocks();
    }

    void loader_load()
    {
        _white_block_loader->try_generate_block(_red_block_loader->front_block());
        _red_block_loader->try_generate_block();
    }

    void clear_nulls()
    {
        _white_block_loader->clear_nulls();
        _red_block_loader->clear_nulls();
    }

    void timeout_blocks_vanished()
    {
//        _white_block_loader->clear_time_outs();
    }

    void trigger_access_lefts()
    {
        _white_block_loader->trigger_access_lefts();
        _red_block_loader->trigger_access_lefts();
    }

    void trigger_access_rights()
    {
        _white_block_loader->trigger_access_rights();
        _red_block_loader->trigger_access_rights();
    }

    void trigger_hit_bound()
    {
        _white_block_loader->trigger_hit_bound();
        _red_block_loader->trigger_hit_bound();
    }

    bool hit()
    {
        int x = get_sign_value();
        if (_red_block_loader->hit(x))
        {
            return 1;
        }
        else if (_white_block_loader->hit(x))
        {
            return 1;
        }
        else
        {
            emit enemy_normal_attack();
            return 0;
        }
    }

    void set_white_blocks(const std::vector<int> &blocks)
    {
        if (_white_block_loader)
            _white_block_loader->deleteLater();
        _white_block_loader = new BlockLoader(_parent, blocks, OperationBar_Left, OperationBar_Right, _y_center);
        connect(_white_block_loader, &BlockLoader::hero_normal_attack, this, &OperationBar::hero_normal_attack);
        connect(_white_block_loader, &BlockLoader::hero_critic_attack, this, &OperationBar::hero_critic_attack);
        connect(_white_block_loader, &BlockLoader::hero_healing, this, &OperationBar::hero_healing);
        connect(_white_block_loader, &BlockLoader::hero_lava_hurt, this, &OperationBar::hero_lava_hurt);
        connect(_white_block_loader, &BlockLoader::hero_get_sheild, this, &OperationBar::hero_get_sheild);
    }

    void set_white_block_loader(BlockLoader *white_block_loader)
    {
        if (_white_block_loader)
            _white_block_loader->deleteLater();
        _white_block_loader = white_block_loader;
        connect(_white_block_loader, &BlockLoader::hero_normal_attack, this, &OperationBar::hero_normal_attack);
        connect(_white_block_loader, &BlockLoader::hero_critic_attack, this, &OperationBar::hero_critic_attack);
        connect(_white_block_loader, &BlockLoader::hero_healing, this, &OperationBar::hero_healing);
        connect(_white_block_loader, &BlockLoader::hero_lava_hurt, this, &OperationBar::hero_lava_hurt);
        connect(_white_block_loader, &BlockLoader::hero_get_sheild, this, &OperationBar::hero_get_sheild);
    }

    void set_red_block_loader(BlockLoader *red_block_loader)
    {
        if (_red_block_loader)
            _red_block_loader->deleteLater();
        _red_block_loader = red_block_loader;
        connect(_red_block_loader, &BlockLoader::enemy_normal_attack, this, &OperationBar::enemy_normal_attack);
        connect(_red_block_loader, &BlockLoader::enemy_critic_attack, this, &OperationBar::enemy_critic_attack);
        connect(_red_block_loader, &BlockLoader::enemy_steal_health, this, &OperationBar::enemy_steal_health);
        connect(_red_block_loader, &BlockLoader::enemy_fireball_hurt, this, &OperationBar::enemy_fireball_hurt);
        connect(_red_block_loader, &BlockLoader::enemy_deadly_attack, this, &OperationBar::enemy_deadly_attack);
        connect(_red_block_loader, &BlockLoader::bomb_clash, this, &OperationBar::bomb_clash);
        connect(_red_block_loader, &BlockLoader::slime_split, this, &OperationBar::slime_split);
        connect(_red_block_loader, &BlockLoader::bow_shoot_arrow, this, &OperationBar::bow_shoot_arrow);
        connect(_red_block_loader, &BlockLoader::generate_bone, this, &OperationBar::generate_bone);
        connect(_red_block_loader, &BlockLoader::generate_dust, this, &OperationBar::generate_dust);
    }

    void red_blocks_retreat(double retreat_velocity)
    {
        _red_block_loader->retreat_blocks(retreat_velocity);
    }

    void delete_blocks()
    {
        _white_block_loader->delete_blocks();
        _red_block_loader->delete_blocks();
    }

    void clear_blocks()
    {
        _white_block_loader->clear_blocks();
        _red_block_loader->clear_blocks();
    }

};

#endif // OPERATIONBAR_H
