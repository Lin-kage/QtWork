
#include "blockloader.h"
#include "config.h"
#include <random>
#include <QQueue>


BlockLoader::BlockLoader(QWidget *parent, const std::vector<int> & block_codes, int left_center, int right_center, int y_center,
                         int cold_time, int cold_time_bias, double load_probability)
    : QLabel(parent), _parent(parent), _block_codes(block_codes), _standard_cold_time(cold_time), _load_probability(load_probability),
    _left_center(left_center), _right_center(right_center), _y_center(y_center), _cold_time_bias(cold_time_bias)
{
    for (auto i = _block_codes.begin(); i != _block_codes.end(); i++)
    {
        _block_intervals[*i] = Block_Intervals[*i];
        _block_frequancies[*i] = Block_Frequancy[*i];
        _block_width[*i] = Block_Width[*i];
        _block_height[*i] = Block_Height[*i];
    }

    _cold_time = _standard_cold_time + rand() % 100;
}

double BlockLoader::load_prob_func() const
{
    if (_load_interval <= _cold_time || _block_list.size() >= 4)
        return 0;
    else
    {
        return 1 / (1 + exp(-_load_interval / Standard_Probability_defactor * _load_probability - 3));
    }
}

int BlockLoader::load_block_which()
{
    double sum = 0;
    QQueue<int> q_id;
    QQueue<double> q_prob;
    for (auto i = _block_codes.begin(); i != _block_codes.end(); i++)
    {
        if (_current_block_intervals[*i])
        {
            _current_block_intervals[*i]--;
        }
        else
        {
            sum += _block_frequancies[*i];
            q_id.push_back(*i);
            q_prob.push_back(_block_frequancies[*i]);
        }
    }
    if (sum > 0)
    {
        double select = rand() / double(RAND_MAX) * sum;
        while (q_id.size() >= 1)
        {
            if (select > q_prob.front())
            {
                select -= q_prob.front();
                q_id.pop_front();
                q_prob.pop_front();
            }
            else
            {
                return q_id.front();
            }
        }
        return q_id.front();
    }
    else
    {
        qDebug() << "Error: No Block to Load!\n";
        return load_block_which();
    }
}

int BlockLoader::get_valid_block_center(int length)
{
    while (1)
    {
        int t = rand() % (_right_center - _left_center - 2) + _left_center + 1 - length / 2;
        bool valid = 1;

        if (t < OperationBar_Board_X_Center - OperationBar_Board_Width / 2
            || t + length > OperationBar_Board_X_Center + OperationBar_Board_Width / 2)
            valid = 0;
        if (valid)
        {
            for (auto i = _block_list.begin(); i != _block_list.end(); i++)
            {
                if (std::max(t, (*i)->x()) <= std::min(t + length, (*i)->x() + (*i)->width()) && !(*i)->is_deleteable())
                {
                    valid = 0;
                    break;
                }
            }
        }
        if (valid)
            return t + length / 2;
    }
}

void BlockLoader::try_generate_block(Block* upper)
{
    _load_interval++;
    double eps = rand() / double(RAND_MAX);
    double prob = load_prob_func();

    if (eps < prob)
    {
        generate_block(upper);
    }

    generate_block_saved(upper);
}

void BlockLoader::generate_block(Block* upper)
{
    int code = load_block_which();
    _current_block_intervals[code] = _block_intervals[code];
    _cold_time = _standard_cold_time + rand() % (_cold_time_bias * 2) - _cold_time_bias;
    _load_interval = 0;
    Block *block = nullptr;
    switch (code) {
    case WHITENormalBlock1:
        block = new WhiteNormalBlock1(_parent, get_valid_block_center(_block_width[WHITENormalBlock1]), _y_center);
        connect(block, &Block::triggered, this, &BlockLoader::hero_normal_attack);
        break;
    case WHITENormalBlock2:
        block = new WhiteNormalBlock2(_parent, get_valid_block_center(_block_width[WHITENormalBlock2]), _y_center);
        connect(block, &Block::triggered, this, &BlockLoader::hero_normal_attack);
        break;
    case WHITECriticBlock:
        block = new WhiteCriticBlock(_parent, get_valid_block_center(_block_width[WHITECriticBlock]), _y_center);
        connect(block, &Block::triggered, this, &BlockLoader::hero_critic_attack);
        break;
    case WHITESolidBlock1:
        block = new WhiteSolidBlock1(_parent, get_valid_block_center(_block_width[WHITESolidBlock1]), _y_center);
        connect(block, &Block::triggered, this, &BlockLoader::hero_normal_attack);
        break;
    case WHITESolidBlock2:
        block = new WhiteSolidBlock2(_parent, get_valid_block_center(_block_width[WHITESolidBlock2]), _y_center);
        connect(block, &Block::triggered, this, &BlockLoader::hero_normal_attack);
        break;
    case WHITEHealingBlock:
        block = new HealingBlock(_parent, get_valid_block_center(_block_width[WHITEHealingBlock]), _y_center);
        connect(block, &Block::triggered, this, &BlockLoader::hero_healing);
        break;
    case WHITEShieldBlock:
        block = new WhiteShieldBlock(_parent, get_valid_block_center(_block_width[WHITEShieldBlock]), _y_center);
        connect(block, &Block::triggered, this, &BlockLoader::hero_get_sheild);
        break;
    case WHITELavaBlock:
        block = new LavaBlock(_parent, get_valid_block_center(_block_width[WHITELavaBlock]), _y_center);
        connect(block, &Block::triggered, this, &BlockLoader::hero_lava_hurt);
        break;

    case REDNormalBlock1:
        block = new RedNormalBlock1(_parent, _right_center, _y_center);
        connect(block, &Block::left_accessed, this, &BlockLoader::enemy_normal_attack);
        break;
    case REDNormalBlock2:
        block = new RedNormalBlock2(_parent, _right_center, _y_center);
        connect(block, &Block::left_accessed, this, &BlockLoader::enemy_normal_attack);
        break;
    case REDFastBlock1:
        block = new RedFastBlock1(_parent, _right_center, _y_center);
        connect(block, &Block::left_accessed, this, &BlockLoader::enemy_normal_attack);
        break;
    case REDFastBlock2:
        block = new RedFastBlock2(_parent, _right_center, _y_center);
        connect(block, &Block::left_accessed, this, &BlockLoader::enemy_normal_attack);
        break;
    case REDBombBlock:
        block = new RedBombBlock(_parent, _right_center, _y_center);
        connect(block, &Block::left_accessed, this, &BlockLoader::enemy_normal_attack);
        connect(block, &Block::triggered, this, &BlockLoader::bomb_clash);
        break;
    case REDSolidBlock1:
        block = new RedSolidBlock1(_parent, _right_center, _y_center);
        connect(block, &Block::left_accessed, this, &BlockLoader::enemy_normal_attack);
        break;
    case REDSolidBlock2:
        block = new RedSolidBlock2(_parent, _right_center, _y_center);
        connect(block, &Block::left_accessed, this, &BlockLoader::enemy_normal_attack);
        break;
    case REDCriticalBlock:
        block = new RedCriticalBlock(_parent, _right_center, _y_center);
        connect(block, &Block::left_accessed, this, &BlockLoader::enemy_critic_attack);
        break;
    case REDSlimeBlock:
        block = new RedSlimeBlock(_parent, _right_center, _y_center);
        connect(block, &Block::left_accessed, this, &BlockLoader::enemy_critic_attack);
        connect(block, &Block::triggered, this, &BlockLoader::slime_split);
        break;
    case REDGooBlock:
        block = new RedGooBlock(_parent, _right_center, _y_center);
        connect(block, &Block::left_accessed, this, &BlockLoader::enemy_normal_attack);
        break;
    case REDShieldBlock:
        block = new RedShieldBlock(_parent, _right_center, _y_center);
        connect(block, &Block::left_accessed, this, &BlockLoader::enemy_normal_attack);
        break;
    case REDFireballBlock:
        block = new RedFireballBlock(_parent, _right_center, _y_center);
        connect(block, &Block::left_accessed, this, &BlockLoader::enemy_normal_attack);
        connect(block, &Block::right_accessed, this, &BlockLoader::enemy_fireball_hurt);
        break;
    case REDIceballBlock:
        block = new RedIceballBlock(_parent, _right_center, _y_center);
        connect(block, &Block::left_accessed, this, &BlockLoader::enemy_critic_attack);
        break;
    case REDArmorBlock:
        block = new RedArmorBlock(_parent, _right_center, _y_center);
        connect(block, &Block::left_accessed, this, &BlockLoader::enemy_normal_attack);
        break;
    case REDBowBlock:
        block = new RedBowBlock(_parent, _right_center, _y_center);
        connect(block, &Block::left_accessed, this, &BlockLoader::enemy_normal_attack);
        connect(block, &Block::bow_shoot_arrow, this, &BlockLoader::bow_shoot_arrow);
        break;
    case REDArrowBlock:
        block = new RedArrowBlock(_parent, _right_center, _y_center);
        connect(block, &Block::left_accessed, this, &BlockLoader::enemy_normal_attack);
        break;
    case REDSoulingBlock1:
        block = new RedSoulingBlock1(_parent, _right_center, _y_center);
        connect(block, &Block::left_accessed, this, &BlockLoader::enemy_steal_health);
        break;
    case REDSoulingBlock2:
        block = new RedSoulingBlock2(_parent, _right_center, _y_center);
        connect(block, &Block::left_accessed, this, &BlockLoader::enemy_steal_health);
        break;
    case REDBoneBlock:
        block = new RedBoneBlock(_parent, _right_center, _y_center);
        connect(block, &Block::left_accessed, this, &BlockLoader::enemy_normal_attack);
        connect(block, &Block::triggered, [block, this]()->void { emit this->generate_dust(block->x() + block->width() / 2); });
        break;
    case REDDustBlock:
        block = new RedDustBlock(_parent, _right_center, _y_center);
        connect(block, &Block::dust_revive, [block, this]()->void { emit this->generate_bone(block->x() + block->width() / 2); });
        break;
    case REDDeadBlock:
        block = new RedDeadBlock(_parent, _right_center, _y_center);
        connect(block, &Block::left_accessed, this, &BlockLoader::enemy_deadly_attack);
        connect(block, &Block::being_hit, [block]()->void { block->set_velocity(-Retreat_Velocity); });
        break;
    case WHITESwordBlock:
        block = new WhiteSwordBlock(_parent, Main_Window_X_Center, _y_center);
        connect(block, &Block::being_hit, this, &BlockLoader::hero_normal_attack);
        break;

    default:
        break;
    }


    if (block != nullptr)
    {
        block->setVisible(true);
        if  (upper != nullptr)
            block->stackUnder(upper);

        qDebug() << "Generate: " << block->geometry() << " Code: " << code << '\n';

        _block_list.push_back(block);
    }
}

void BlockLoader::generate_block_forced(int x_center, int code, Block* upper)
{
    Block* block = nullptr;
    switch (code) {
    case WHITENormalBlock1:
        block = new WhiteNormalBlock1(_parent, x_center, _y_center);
        connect(block, &Block::triggered, this, &BlockLoader::hero_normal_attack);
        break;
    case WHITENormalBlock2:
        block = new WhiteNormalBlock2(_parent, x_center, _y_center);
        connect(block, &Block::triggered, this, &BlockLoader::hero_normal_attack);
        break;
    case WHITECriticBlock:
        block = new WhiteCriticBlock(_parent, x_center, _y_center);
        connect(block, &Block::triggered, this, &BlockLoader::hero_critic_attack);
        break;
    case WHITESolidBlock1:
        block = new WhiteSolidBlock1(_parent, x_center, _y_center);
        connect(block, &Block::triggered, this, &BlockLoader::hero_normal_attack);
        break;
    case WHITESolidBlock2:
        block = new WhiteSolidBlock2(_parent, x_center, _y_center);
        connect(block, &Block::triggered, this, &BlockLoader::hero_normal_attack);
        break;
    case WHITEHealingBlock:
        block = new HealingBlock(_parent, x_center, _y_center);
        connect(block, &Block::triggered, this, &BlockLoader::hero_healing);
        break;
    case WHITEShieldBlock:
        block = new WhiteShieldBlock(_parent, x_center, _y_center);
        connect(block, &Block::triggered, this, &BlockLoader::hero_get_sheild);
        break;
    case WHITELavaBlock:
        block = new LavaBlock(_parent, x_center, _y_center);
        connect(block, &Block::triggered, this, &BlockLoader::hero_lava_hurt);
        break;

    case REDNormalBlock1:
        block = new RedNormalBlock1(_parent, x_center, _y_center);
        connect(block, &Block::left_accessed, this, &BlockLoader::enemy_normal_attack);
        break;
    case REDNormalBlock2:
        block = new RedNormalBlock2(_parent, x_center, _y_center);
        connect(block, &Block::left_accessed, this, &BlockLoader::enemy_normal_attack);
        break;
    case REDFastBlock1:
        block = new RedFastBlock1(_parent, x_center, _y_center);
        connect(block, &Block::left_accessed, this, &BlockLoader::enemy_normal_attack);
        break;
    case REDFastBlock2:
        block = new RedFastBlock2(_parent, x_center, _y_center);
        connect(block, &Block::left_accessed, this, &BlockLoader::enemy_normal_attack);
        break;
    case REDBombBlock:
        block = new RedBombBlock(_parent, x_center, _y_center);
        connect(block, &Block::left_accessed, this, &BlockLoader::enemy_normal_attack);
        connect(block, &Block::triggered, this, &BlockLoader::bomb_clash);
        break;
    case REDSolidBlock1:
        block = new RedSolidBlock1(_parent, x_center, _y_center);
        connect(block, &Block::left_accessed, this, &BlockLoader::enemy_normal_attack);
        break;
    case REDSolidBlock2:
        block = new RedSolidBlock2(_parent, x_center, _y_center);
        connect(block, &Block::left_accessed, this, &BlockLoader::enemy_normal_attack);
        break;
    case REDCriticalBlock:
        block = new RedCriticalBlock(_parent, x_center, _y_center);
        connect(block, &Block::left_accessed, this, &BlockLoader::enemy_critic_attack);
        break;
    case REDSlimeBlock:
        block = new RedSlimeBlock(_parent, x_center, _y_center);
        connect(block, &Block::left_accessed, this, &BlockLoader::enemy_critic_attack);
        connect(block, &Block::triggered, this, &BlockLoader::slime_split);
        break;
    case REDGooBlock:
        block = new RedGooBlock(_parent, x_center, _y_center);
        connect(block, &Block::left_accessed, this, &BlockLoader::enemy_normal_attack);
        break;
    case REDShieldBlock:
        block = new RedShieldBlock(_parent, x_center, _y_center);
        connect(block, &Block::left_accessed, this, &BlockLoader::enemy_normal_attack);
        break;
    case REDFireballBlock:
        block = new RedFireballBlock(_parent, x_center, _y_center);
        connect(block, &Block::left_accessed, this, &BlockLoader::enemy_normal_attack);
        connect(block, &Block::right_accessed, this, &BlockLoader::enemy_fireball_hurt);
        connect(block, &Block::being_hit, [block]()->void { block->change_direction(); });
        break;
    case REDIceballBlock:
        block = new RedIceballBlock(_parent, x_center, _y_center);
        connect(block, &Block::left_accessed, this, &BlockLoader::enemy_critic_attack);
        break;
    case REDArmorBlock:
        block = new RedArmorBlock(_parent, x_center, _y_center);
        connect(block, &Block::left_accessed, this, &BlockLoader::enemy_normal_attack);
        break;
    case REDBowBlock:
        block = new RedBowBlock(_parent, x_center, _y_center);
        connect(block, &Block::left_accessed, this, &BlockLoader::enemy_normal_attack);
        connect(block, &Block::bow_shoot_arrow, this, &BlockLoader::bow_shoot_arrow);
        break;
    case REDArrowBlock:
        block = new RedArrowBlock(_parent, x_center, _y_center);
        connect(block, &Block::left_accessed, this, &BlockLoader::enemy_normal_attack);
        break;
    case REDSoulingBlock1:
        block = new RedSoulingBlock1(_parent, x_center, _y_center);
        connect(block, &Block::left_accessed, this, &BlockLoader::enemy_steal_health);
        break;
    case REDSoulingBlock2:
        block = new RedSoulingBlock2(_parent, x_center, _y_center);
        connect(block, &Block::left_accessed, this, &BlockLoader::enemy_steal_health);
        break;
    case REDBoneBlock:
        block = new RedBoneBlock(_parent, x_center, _y_center);
        connect(block, &Block::left_accessed, this, &BlockLoader::enemy_normal_attack);
        connect(block, &Block::triggered, [block, this]()->void { emit this->generate_dust(block->x() + block->width() / 2); });
        break;
    case REDDustBlock:
        block = new RedDustBlock(_parent, x_center, _y_center);
        connect(block, &Block::dust_revive, [block, this]()->void { emit this->generate_bone(block->x() + block->width() / 2); });
        break;
    case REDDeadBlock:
        block = new RedDeadBlock(_parent, x_center, _y_center);
        connect(block, &Block::access_left, this, &BlockLoader::enemy_deadly_attack);
        connect(block, &Block::being_hit, [block]()->void { block->set_velocity(Retreat_Velocity); });
        break;
    case WHITESwordBlock:
        block = new WhiteSwordBlock(_parent, Main_Window_X_Center, _y_center);
        connect(block, &Block::being_hit, this, &BlockLoader::hero_normal_attack);
        break;

    default:
        break;
    }


    if (block != nullptr)
    {
        block->setVisible(true);
        if (upper != nullptr)
            block->stackUnder(upper);

        qDebug() << "Generate: " << block->geometry() << " Code: " << code << '\n';

        _generate_later.push_back(block);
    }
    else
    {

    }
}

// 清除空指针
void BlockLoader::clear_nulls()
{
    for (auto i = _block_list.begin(); i != _block_list.end(); )
    {
        if ((*i)->is_deleteable())
        {
            (*i)->vanish();
            i = _block_list.erase(i);
        }
        else
            i++;
    }
}

void BlockLoader::under_block(Block* block)
{
    for (auto i = _block_list.begin(); i != _block_list.end(); i++)
    {
        if ((*i)->is_deleteable())
            continue;
        (*i)->stackUnder(block);
    }
}

void BlockLoader::raise_blocks()
{
    for (auto i = _block_list.begin(); i != _block_list.end(); i++)
    {
        if ((*i)->is_deleteable())
            continue;
        (*i)->raise();
    }
}

// 处理移动到最左边的Block
void BlockLoader::trigger_access_lefts()
{
    for (auto i = _block_list.begin(); i != _block_list.end(); i++)
    {
        if ((*i)->is_deleteable())
            continue;
        if ((*i)->access_left())
        {
            (*i)->trigger_access_left();
        }
    }
}

void BlockLoader::trigger_access_rights()
{
    for (auto i = _block_list.begin(); i != _block_list.end(); i++)
    {
        if ((*i)->is_deleteable())
            continue;
        if ((*i)->access_right())
        {
            (*i)->trigger_access_right();
        }
    }
}

// 处理到达hit_bound的Block
void BlockLoader::trigger_hit_bound()
{
//    qDebug() << "Enter trigger_hit_bound, List size:" << _block_list.size();
    for (auto i = _block_list.begin(); i != _block_list.end(); i++)
    {
        if ((*i)->is_deleteable())
            continue;
        if ((*i)->_hit_count >= (*i)->_hit_count_bound)
        {
            (*i)->trigger_hit_bound();
        }
    }
}

bool BlockLoader::hit(int x)
{
    Block* choose = nullptr;
    for (auto i = _block_list.begin(); i != _block_list.end(); i++)
    {
        if ((*i)->is_deleteable())
            continue;
        if ((*i)->in_area(x))
        {
            choose = *i;
        }
    }
    if (choose)
    {
        choose->hit();
        return true;
    }
    return false;
}

// 移动Blocks
void BlockLoader::move_blocks()
{
    for (auto i = _block_list.begin(); i != _block_list.end(); i++)
    {
        if ((*i)->is_deleteable())
            continue;
        (*i)->move_on_bar();
    }
}

void BlockLoader::retreat_blocks(double retreat_velocity)
{
    for (auto i = _block_list.begin(); i != _block_list.end(); i++)
    {
        if ((*i)->is_deleteable())
            continue;
        (*i)->set_velocity(-retreat_velocity);
    }
}

void BlockLoader::clear_time_outs(int frames)
{
    for (auto i = _block_list.begin(); i != _block_list.end(); i++)
    {
        if ((*i)->is_deleteable())
            continue;
        if ((*i)->time_exist > frames)
        {
            (*i)->_deleteable = 1;
        }
    }
}

void BlockLoader::time_event()
{
    move_blocks();

    clear_time_outs();

    try_generate_block();
}

void BlockLoader::set_center(int l_center, int r_center, int y_center)
{
    _left_center = l_center;
    _right_center = r_center;
    _y_center = y_center;
}
