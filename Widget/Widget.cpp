
#include "Widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent), _game_setting(this), _main_menu(this), _game_loader(this)
    , ui(new Ui::Widget), _music_player(this), _game_background(this)
{
    ui->setupUi(this);

    _main_timer = new QTimer;

//    _bar = new OperationBar(this, nullptr, 200, 400);

    connect(_main_timer, &QTimer::timeout, this, &Widget::main_timer_event);

    _main_timer->start(Time_Per_Frame);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Escape:
        if (_condition == Gaming)
        {
            if (_game_condition == GameFighting)
            {
                _game_condition = GamePause;
                qDebug() << "Paused\n";
                Optionmenu* p = new Optionmenu(this, Gaming);
                set_option_menu(p);
            }
            else if (_game_condition == GamePause)
            {
                if (_option_menu != nullptr)
                    delete _option_menu;
                _game_condition = GameFighting;
            }
        }
        break;

    case Qt::Key_Space:
        if (_condition == Gaming && _game_condition == GameFighting)
        {
            _music_player._pat_sound->play();
            if (_game_loader._bar[0]->hit())
                _game_loader._hero->hit_count();
        }
        else if (_condition == PressSpace)
        {
            _condition = MainMenu;
        }
        break;

    case Qt::Key_S:
        if (_condition == Gaming && _game_condition == GameFighting)
        {
            if (_game_loader.trick_avalible())
            {
                _game_loader.generate_trick();
            }
        }
        break;
    default:
        break;
    }
}

void Widget::main_timer_event()
{
    switch (_condition) {
    case PressSpace:
        _music_player.bgm_play("music/main_menu.mp3");
        _game_background.load_title_screen_no_button();
        break;
    case MainMenu:
        _music_player.bgm_play("music/main_menu.mp3");
        _game_background.load_title_screen_with_button();
        _main_menu.show();
        break;
    //case Option:

        //break;
    //case Achievement:

        //break;
    //case LoadGame:

        //break;
    case Gaming:
        switch (_game_condition) {
        case GameHeroEnter:
            _game_loader._hero->in_stage(_game_loader._stage_big);
            _game_loader._hero->update();
            _music_player.stage_play();
            _game_background.load_stage(_game_loader._stage_big);
            if (_game_loader.hero_enter())
            {
                _game_loader.set_white_block(StageBlocks[_game_loader._stage_big]);
                set_game_condition(GameEnemyGenerate);
            }
            break;
        case GameEnemyEnter:
            _game_background.move();
            if (_game_loader._stage_small == Stage_Num_Each)
                _music_player.bgm_play("music/boss.mp3");
            if (_game_loader.enemy_enter())
            {
                set_game_condition(GameFighting);
            }
            break;
        case GameEnemyFlee:
            if (_game_loader.enemy_flee())
            {
                _game_loader._stage_small++;
                _game_loader._upgraded = 0;
                set_game_condition(GameUpgrade);
            }
            break;
        case GameEnemyDead:
            _game_loader.trick_clear();
            _game_loader._enemy->rotate_image();
            set_game_condition(GameEnemyFlee);
            break;
        case GameUpgrade:
            if (_game_loader.hero_upgrade())
            {
                if (_game_loader._stage_small <= Stage_Num_Each)
                {
                    set_game_condition(GameEnemyGenerate);
                    _game_setting.update();
                }
                else
                {
                    set_game_condition(GameStageClear);
                    _game_loader._stage_small = 1;
                    _game_loader._stage_big++;
                    if (_game_loader._stage_big < 5)
                        _game_setting.update();
                }
            }
            break;
        case GameEnemyGenerate:
            _game_loader._stage_sign->setText(QString::number(_game_loader._stage_big) + "-" + QString::number(_game_loader._stage_small));
            if (_game_loader.is_stage_boss())
            {
                _game_loader.generate_boss_enemy();
            }
            else
            {
                _game_loader.generate_warrior_enemy();
            }
            set_game_condition(GameEnemyEnter);
            break;
        case GamePause:

            break;
        case GameFighting:
            _game_loader.load();
            if (_game_loader._enemy->dead())
            {
                _game_loader.bar_clear();
                set_game_condition(GameEnemyDead);
                _game_loader._hero->stop_attack_move();
            }
            else if (_game_loader._hero->dead())
            {
                _game_loader.bar_clear();
                set_game_condition(GameHeroDead);
            }
            break;
        case GameHeroDead:
            _game_loader.game_over();
            break;
        case GameStageClear:
            if (_game_loader.stage_won())
            {
                set_game_condition(GameStageWon);
            }
            break;
        case GameStageWon:
            if (_game_loader._stage_big == 5)
            {
                _game_loader.game_won();
                set_game_condition(GameWon);
            }
            else
            {
                _game_loader._hero->move(-_game_loader._hero->width(), _game_loader._hero->y());
                _game_loader._hero->update();
                _game_loader._stage_sign->setText(QString::number(_game_loader._stage_big) + "-" + QString::number(_game_loader._stage_small));
                set_game_condition(GameHeroEnter);
            }
            break;
        case GameWon:
            break;
        }

        break;
    case Quit:

        break;
    default:
        break;
    }

}


