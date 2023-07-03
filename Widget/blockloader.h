
#ifndef BLOCKLOADER_H
#define BLOCKLOADER_H

#include "block.h"
#include "config.h"
#include <QList>
#include <vector>

class BlockLoader : public QLabel
{
    Q_OBJECT
protected:
    int _standard_cold_time, _cold_time;
    int _cold_time_bias;
    double _load_probability;
    int _load_interval = 0;

    QWidget *_parent;

    int _left_center, _right_center, _y_center;

    // 储存可生成的Block的code
    std::vector<int> _block_codes;

    // 储存已生成的Block
    QList<Block*> _block_list;
    // 储存非正常流程生成的Block
    QList<Block*> _generate_later;

    // 储存各个Block的interval与probability
    int _block_intervals[Block_Kinds];
    int _current_block_intervals[Block_Kinds]{ };
    double _block_frequancies[Block_Kinds];
    int _block_width[Block_Kinds], _block_height[Block_Kinds];

    // 返回一个概率，若random值大于此概率则会生成Block
    double load_prob_func() const;

    // 返回一个可生成的Block的code
    int load_block_which();


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
    void bomb_clash(int);
    void slime_split(int);

    void bow_shoot_arrow(int);
    void enemy_steal_health();
    void generate_dust(int);
    void generate_bone(int);

public:
    // 清除空指针
    void clear_nulls();

    // cold_time * 0.02秒内不会生成Block, load_probability与生成Block的频率有关
    BlockLoader(QWidget *parent, const std::vector<int> & block_codes, int left_center, int right_center, int y_center,
                int cold_time = Standard_Cold_Time, int cold_time_bias = Standard_Cold_Time_Bias, double load_probability = 1.0);

    virtual ~BlockLoader() { clear(); qDebug() << "Blockloader deleted\n"; }

    Block* front_block()
    {
        if (_block_list.size() > 0)
            return _block_list.front();
        return nullptr;
    }

    // 尝试生成Block
    void try_generate_block(Block * upper = nullptr);

    // 获得一个适合生成Block的位置
    int get_valid_block_center(int length);

    // 生成一个Block，会考虑重叠，并将非正常流程生成的Block转移到block_list
    void generate_block(Block* upper = nullptr);

    // 在指定位置强制生成一个Block，会储存在generate_later中
    void generate_block_forced(int x_center, int code, Block* upper = nullptr);

    // 将generate_later的Block放入block_list中
    void generate_block_saved(Block *upper = nullptr) {
        for (auto i = _generate_later.begin(); i != _generate_later.end(); )
        {
            _block_list.push_back(*i);
            if (upper)
                (*i)->stackUnder(upper);
            else if (!_block_list.empty())
                (*i)->stackUnder(_block_list.front());
            i = _generate_later.erase(i);
        }
    }

    // Blocks进行移动
    void move_blocks();

    // 处理移动到最左边的Block
    void trigger_access_lefts();

    void trigger_access_rights();

    // 清除存在时间超过frames帧的Block
    void clear_time_outs(int frames = 100);

    // 检测此位置是否有Block，有则返回true并hit
    bool hit(int x);

    // 处理到达hit_bound的Block
    void trigger_hit_bound();

    // Block每时刻需要使其生成的Block进行移动
    void time_event();

    void set_center(int l_center, int r_center, int y_center);

    void set_y_center(int y_center)
    {
        _y_center = y_center;
    }
    
    void set_blocks(const std::vector<int> &blocks)
    {
        _block_codes = blocks;
    }

    // 将Block置顶
    void raise_blocks();

    void under_block(Block *block);

    // 使储存的所有block后退
    void retreat_blocks(double retreat_velocity);

    // 清除所有储存的Block,带动画
    void clear_blocks()
    {
        while (!_block_list.empty())
        {
            _block_list.front()->vanish();
            _block_list.pop_front();
        }
    }

    // 清除中心在[center - radius, center + radius]的Block，带动画
    void bomb_clear_blocks(int center, int radius)
    {
        for (auto i = _block_list.begin(); i != _block_list.end(); i++)
        {
            if ((*i)->_cur_x_center >= center - radius && (*i)->_cur_x_center <= center + radius)
            {
                (*i)->_deleteable = 1;
            }
        }
    }

    // 清楚所有储存的Block，无动画
    void delete_blocks()
    {
        while (!_block_list.empty())
        {
            _block_list.front()->deleteLater();
            _block_list.pop_front();
        }
    }

    void set_block_frequancy(int kind, int frequancy) { _block_frequancies[kind] = frequancy; }
    void set_block_interval(int kind, int interval) { _block_intervals[kind] = interval; }
    void set_block_width(int kind, int interval) { _block_width[kind] = interval; }
};

#endif // BLOCKLOADER_H
