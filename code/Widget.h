
#ifndef WIDGET_H
#define WIDGET_H

#include "enemy.h"
#include "hero.h"
#include "operationbar.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget

{
    Q_OBJECT

private:


public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void keyPressEvent(QKeyEvent *key);

    void set_condition(int condition)
    {
        _condition = condition;
    }

    void set_game_condition(int condition)
    {
        _game_condition = condition;
    }

    void close_main_menu()
    {
        _main_menu.close();
    }

    void start_game()
    {
        close_main_menu();
        _game_loader.preload();
        set_condition(Gaming);
        set_game_condition(GameHeroEnter);
    }

    void show_save()
    {
        QLabel* save_background = new QLabel(this);
        QLabel *save_info = new QLabel(save_background);
        HoverButton *close_button = new HoverButton(this);
        HoverButton*commit_button = new HoverButton(this);

        save_background->setGeometry(0, 0, Main_Window_Width, Main_Window_Height);
        save_background->setPixmap(QPixmap("picture/icon/option.png"));
        save_background->setVisible(true);
        save_info->setGeometry(Load_Label_X_Center - Load_Label_Width / 2, Load_Label_Y_Center - Load_Label_Height / 2,
            Load_Label_Width, Load_Label_Height);
        save_info->setAttribute(Qt::WA_TranslucentBackground);
        save_info->setAlignment(Qt::AlignCenter);
        save_info->setFont(QFont(QFontDatabase::applicationFontFamilies(0).at(0), 24));
        save_info->setText("Stage: " + QString::number(_game_setting._stage_big) + " - " + QString::number(_game_setting._stage_small) + "\n" +
            "Health: " + QString::number(_game_setting._health) + " / " + QString::number(_game_setting._max_health) + "\n" +
            "Attack: " + QString::number(_game_setting._min_attack) + " - " + QString::number(_game_setting._max_attack) + "\n" + 
            "Magic Attack:" + QString::number(_game_setting._magic_attack) + "\n\n" +
            "Are you sure to load?");
        save_info->setVisible(true);
        
        close_button->setGeometry(Load_Close_Button_X_Center - Load_Close_Button_Width / 2, Load_Close_Button_Y_Center - Load_Close_Button_Height / 2,
            Load_Close_Button_Width, Load_Close_Button_Height);
        close_button->setIconSize(close_button->size());
        close_button->setIcon(QPixmap("picture/icon/blank_frame.png").scaled(close_button->size()));
        close_button->setVisible(true);

        QLabel* label = new QLabel(close_button);
        label->setGeometry(0, 0, close_button->width(), close_button->height());
        label->setFont(QFont(QFontDatabase::applicationFontFamilies(3).at(0), 24));
        label->setText("X");
        label->setAlignment(Qt::AlignCenter);
        label->setVisible(true);
        connect(close_button, &QPushButton::clicked, [=]()->void {
            _music_player._choose_sound->play();
            save_background->deleteLater();
            close_button->deleteLater();
            commit_button->deleteLater();
            });
        connect(close_button, &HoverButton::enter, [=]()->void {
            close_button->setIcon(QPixmap("picture/icon/blank_frame_hover.png").scaled(close_button->size()));
            });
        connect(close_button, &HoverButton::leave, [=]()->void {
            close_button->setIcon(QPixmap("picture/icon/blank_frame.png").scaled(close_button->size()));
            });

        if (_game_setting._save_exist == 0)
        {
            save_info->setText("No save!");
            return;
        }
        commit_button->setGeometry(Load_Commit_Button_X_Center - Load_Commit_Button_Width / 2, Load_Commit_Button_Y_Center - Load_Commit_Button_Height / 2,
            Load_Commit_Button_Width, Load_Commit_Button_Height);
        commit_button->setIconSize(commit_button->size());
        commit_button->setIcon(QPixmap("picture/icon/blank_frame.png").scaled(commit_button->size()));
        commit_button->setVisible(true);

        label = new QLabel(commit_button);
        label->setGeometry(0, 0, commit_button->width(), commit_button->height());
        label->setFont(QFont(QFontDatabase::applicationFontFamilies(0).at(0), 24));
        label->setText("OK");
        label->setAlignment(Qt::AlignCenter);
        label->setVisible(true);

        connect(commit_button, &HoverButton::enter, [=]()->void {
            commit_button->setIcon(QPixmap("picture/icon/blank_frame_hover.png").scaled(commit_button->size()));
            });
        connect(commit_button, &HoverButton::leave, [=]()->void {
            commit_button->setIcon(QPixmap("picture/icon/blank_frame.png").scaled(commit_button->size()));
            });
        connect(commit_button, &QPushButton::clicked, [=]()->void {
            _music_player._choose_sound->play();
            close_main_menu();
            _game_loader.preload(_game_setting);

            save_background->deleteLater();
            commit_button->deleteLater();
            close_button->deleteLater();

            set_condition(Gaming);
            set_game_condition(GameHeroEnter);
            });
    }

    bool jumpnumber_on() const { return _game_setting.jumpnumber_on(); }

private slots:

    // 逻辑帧主函数，未暂停时，每一帧都会执行一次
    void main_timer_event();

    void hero_normal_attack() {
        _game_loader.hero_normal_attack();
        _music_player._punch_sound->stop();
        _music_player._punch_sound->play();
    }

    void hero_critic_attack() {
        _game_loader.hero_critic_attack();
        _music_player._sword_sound->stop();
        _music_player._sword_sound->play();
    }

    void enemy_normal_attack() {
        _game_loader.enemy_normal_attack();
        _music_player._clap_sound->stop();
        _music_player._clap_sound->play();
    }

    void enemy_critic_attack() {
        _game_loader.enemy_critic_attack();
        _music_player._clap_sound->stop();
        _music_player._clap_sound->play();
    }

    void enemy_steal_health() {
        _game_loader.enemy_steal_health();
        _music_player._clap_sound->stop();
        _music_player._clap_sound->play();
    }

    void enemy_fireball_hurt() {
         _game_loader._enemy->magical_hurt(Fireball_Hurt);
        _game_loader.red_block_retreat(Retreat_Velocity);
    }

    void enemy_deadly_attack() {
        _game_loader._hero->hurt(Deadly_Hurt);
        _game_loader._hero->hurt(Deadly_Hurt);
        _game_loader._hero->hurt(Deadly_Hurt);
    }

    void hero_healing() {
        _music_player._heal_sound->play();
        _game_loader._hero->heal(Heal_Persentage);
    }

    void hero_lava_hurt() {
        _game_loader._hero->hurt(Lava_Hurt_Persentage);
    }

    void hero_get_shield() {
        _game_loader._hero->get_shield();
    }
    
    void change_bgm_volume(int volume)
    {
        _music_player._bgm_output->setVolume(volume / 100.0);
        _game_setting._bgm_volume = volume;
    }

    void change_sound_volume(int volume)
    {
        for (int i = 0; i < 4; i++)
        {
            _music_player._sound_output[i]->setVolume(volume / 100.0);
        }
        _game_setting._sound_volume = volume;
    }

private:

    // 几种不同的状态
    enum{PressSpace, MainMenu, Option, Achievement, LoadGame, Gaming, Quit};
    // 状态标志
    int _condition = PressSpace;

    // 游戏中几种不同的状态
    enum{GameEnemyEnter, GameEnemyFlee, GameFighting, GamePause, GameUpgrade,
         GameEnemyDead, GameHeroDead, GameEnemyGenerate, GameHeroEnter, GameStageBoss, GameStageClear, GameStageWon, GameWon};
    // 游戏中的状态标志
    int _game_condition = GameFighting;

private:

    // 游戏背景图
    class GameBackGround {
    private:
        Widget *_parent;

        QLabel* _near_left = nullptr, * _near_right = nullptr,
            * _far_left = nullptr, * _far_right = nullptr,
            * _sky_left = nullptr, * _sky_right = nullptr, * _title_screen = nullptr;


        int _current_stage = 0, _current_main_menu = -1;

        double _near_velocity = 3, _far_velocity = 1, _sky_velocity = 0.3;

        int _direction = -1;

        double _near_left_x = -100, _far_left_x = -100, _sky_left_x = -100, 
            _near_right_x = 1200, _far_right_y = 1200, _sky_right_y = 1200;

        bool _moving = 1;

    public:
        GameBackGround(Widget* parent) : _parent(parent)
        {
            _sky_left = new QLabel(_parent);
            _sky_right = new QLabel(_parent);
            _far_left = new QLabel(_parent);
            _far_right = new QLabel(_parent);
            _near_left = new QLabel(_parent);
            _near_right = new QLabel(_parent);

            _near_left->setVisible(true);
            _near_right->setVisible(true);
            _far_left->setVisible(true);
            _far_right->setVisible(true);
            _sky_left->setVisible(true);
            _sky_right->setVisible(true);

            _near_left->setGeometry(0, 0, 1350, 600);
            _near_right->setGeometry(0, 0, 1350, 600);
            _far_left->setGeometry(0, 0, 1350, 600);
            _far_right->setGeometry(0, 0, 1350, 600);
            _sky_left->setGeometry(0, 0, 1350, 600);
            _sky_right->setGeometry(0, 0, 1350, 600);
        }

        void load_title_screen_no_button()
        {
            if (_current_main_menu != 0)
            {
                delete _title_screen;
                _title_screen = nullptr;
                _title_screen = new QLabel(_parent);
                _title_screen->setVisible(true);
                _title_screen->setGeometry(Main_Window_X_Center - Main_Window_Width / 2, Main_Window_Y_Center - Main_Window_Height / 2,
                    Main_Window_Width, Main_Window_Height);
                _title_screen->setPixmap(QPixmap(TitleScreenNoButton_Address));

                QLabel* press_space = new QLabel(_title_screen);
                press_space->setGeometry(Press_Sapce_Png_X_Center - Press_Space_Png_Width / 2, Press_Space_Png_Y_Center - Press_Space_Png_Height / 2,
                    Press_Space_Png_Width, Press_Space_Png_Height);
                press_space->setPixmap(QPixmap(PressSpacePng_Address));
                QTimer* press_space_blink = new QTimer(press_space);
                connect(press_space_blink, &QTimer::timeout, [press_space]()->void {
                    if (press_space->isVisible())
                        press_space->setVisible(false);
                    else
                        press_space->setVisible(true);
                });
                press_space_blink->start(800);

                _current_main_menu = 0;
            }
        }

        void load_title_screen_with_button()
        {
            if (_current_main_menu != 1)
            {
                delete _title_screen;
                _title_screen = nullptr;
                _title_screen = new QLabel(_parent);
                _title_screen->setVisible(true);
                _title_screen->setGeometry(0, 0, 1000, 600);
                _title_screen->setPixmap(QPixmap(TitleScreenWithButton_Address));
                _current_main_menu = 1;
            }
        }

        void load_stage(int stage)
        {
            if (_current_main_menu != -1)
            {
                delete _title_screen;
                _title_screen = nullptr;
                _current_main_menu = -1;
            }

            if (_current_stage != stage)
            {
                QString dir_path = "picture/background/stage" + QString::number(stage) + "/";

                _near_left->setPixmap(dir_path + "near.png");
                _near_right->setPixmap(dir_path + "near.png");
                _far_left->setPixmap(dir_path + "far.png");
                _far_right->setPixmap(dir_path + "far.png");
                _sky_left->setPixmap(dir_path + "sky.png");
                _sky_right->setPixmap(dir_path + "sky.png");

                //_near_left->setScaledContents(true);
                //_near_right->setScaledContents(true);
                //_far_left->setScaledContents(true);
                //_far_right->setScaledContents(true);
                //_sky_left->setScaledContents(true);
                //_sky_right->setScaledContents(true);

                _near_left_x = -150, _far_left_x = -150, _sky_left_x = -150,
                _near_right_x = 1150, _far_right_y = 1150, _sky_right_y = 1150;

                _near_left->move(_near_left_x, 0);
                _near_right->move(_near_right_x, 0);
                _far_left->move(_far_left_x, 0);
                _far_right->move(_far_right_y, 0);
                _sky_left->move(_sky_left_x, 0);
                _sky_right->move(_sky_right_y, 0);

                _current_stage = stage;
            }
        }

        void move()
        {
            if (!_moving)
                return;

            _near_left_x += _direction * _near_velocity;
            _near_right_x += _direction * _near_velocity;
            _far_left_x += _direction * _far_velocity;
            _far_right_y += _direction * _far_velocity;
            _sky_left_x += _direction * _sky_velocity;
            _sky_right_y += _direction * _sky_velocity;

            if (_near_left_x > -100)
            {
                _near_right_x = _near_left_x;
                _near_left_x -= 1300;
            }
            else if (_near_right_x < -100)
            {
                _near_left_x = _near_right_x;
                _near_right_x += 1300;
            }

            if (_far_left_x > -100)
            {
                _far_right_y = _far_left_x;
                _far_left_x -= 1300;
            }
            else if (_far_right_y < -100)
            {
                _far_left_x = _far_right_y;
                _far_right_y += 1300;
            }

            if (_sky_left_x > -100)
            {
                _sky_right_y = _sky_left_x;
                _sky_left_x -= 1300;
            }
            else if (_sky_right_y < -100)
            {
                _sky_left_x = _sky_right_y;
                _sky_right_y += 1300;
            }

            _near_left->move(_near_left_x, 0);
            _near_right->move(_near_right_x, 0);
            _far_left->move(_far_left_x, 0);
            _far_right->move(_far_right_y, 0);
            _sky_left->move(_sky_left_x, 0);
            _sky_right->move(_sky_right_y, 0);
        }

        void set_dir(int direction) { _direction = direction; }

        void set_moving(bool moving) { _moving = moving; }
    };

    // 储存游戏配置参数
    class GameSetting
    {
    public:
        Widget* _parent;

        // 音乐配置参数
        int _bgm_volume, _sound_volume;

        bool _jumpnumber_on;

        // 存档参数
        bool _save_exist;

        int _stage_big, _stage_small;

        int _health, _max_health, _hit_count;

        int _min_attack, _max_attack, _magic_attack;

        int _shield_on;

        // 首次启动参数

        // 最高分参数

    public:
        GameSetting(Widget *parent) : _parent(parent) { 
            QSettings* setting = new QSettings("config/settings.ini", QSettings::IniFormat);
            
            setting->beginGroup("Music");
            
            _bgm_volume = setting->value("BGM_volume", 50).toInt();
            _sound_volume = setting->value("sound_volume", 50).toInt();
            _jumpnumber_on = setting->value("jumpnumber_on", 1).toBool();

            setting->endGroup();

            setting->beginGroup("Save");
            
            _save_exist = setting->value("save_exist", 0).toBool();
            _stage_big = setting->value("stage_big", 0).toInt();
            _stage_small = setting->value("stage_small", 0).toInt();
            _health = setting->value("health", 0).toInt();
            _max_health = setting->value("max_health", 0).toInt();
            _min_attack = setting->value("min_attack", 0).toInt();
            _max_attack = setting->value("max_attack", 0).toInt();
            _hit_count = setting->value("hit_count", 0).toInt();
            _magic_attack = setting->value("magic_attack", 0).toInt();
            _shield_on = setting->value("shield_on", 0).toInt();

            setting->endGroup();

            delete setting;
        }

        void update()
        {
            _save_exist = true;
            _stage_big = _parent->_game_loader._stage_big;
            _stage_small = _parent->_game_loader._stage_small;
            _health = _parent->_game_loader._hero->health();
            _max_health = _parent->_game_loader._hero->max_health();
            _min_attack = _parent->_game_loader._hero->min_attack();
            _max_attack = _parent->_game_loader._hero->max_attack();
            _hit_count = _parent->_game_loader._hero->get_hit_count();
            _magic_attack = _parent->_game_loader._hero->magic_attack();
            _shield_on = _parent->_game_loader._hero->shield_on();
        }

        ~GameSetting()
        {
            QSettings* setting = new QSettings("config/settings.ini", QSettings::IniFormat);

            setting->beginGroup("Music");

            setting->setValue("BGM_volume", _bgm_volume);
            setting->setValue("sound_volume", _sound_volume);
            setting->setValue("jumpnumber_on", _jumpnumber_on);

            setting->endGroup();

            setting->beginGroup("Save");

            setting->setValue("save_exist", _save_exist);
            setting->setValue("stage_big", _stage_big);
            setting->setValue("stage_small", _stage_small);
            setting->setValue("health", _health);
            setting->setValue("max_health", _max_health);
            setting->setValue("min_attack", _min_attack);
            setting->setValue("max_attack", _max_attack);
            setting->setValue("hit_count", _hit_count);
            setting->setValue("magic_attack", _magic_attack);
            setting->setValue("shield_on", _shield_on);

            setting->endGroup();

            qDebug() << "Saved\n";

            delete setting;
        }

        void set_save()
        {
            QSettings* setting = new QSettings("config/settings.ini", QSettings::IniFormat);

            setting->beginGroup("Music");

            setting->setValue("BGM_volume", _bgm_volume);
            setting->setValue("sound_volume", _sound_volume);
            setting->setValue("jumpnumber_on", _jumpnumber_on);

            setting->endGroup();

            setting->beginGroup("Save");

            setting->setValue("save_exist", _save_exist);
            setting->setValue("stage_big", _stage_big);
            setting->setValue("stage_small", _stage_small);
            setting->setValue("health", _health);
            setting->setValue("max_health", _max_health);
            setting->setValue("min_attack", _min_attack);
            setting->setValue("max_attack", _max_attack);
            setting->setValue("magic_attack", _magic_attack);
            setting->setValue("shield_on", _shield_on);

            setting->endGroup();

            qDebug() << "Saved\n";

            delete setting;
        }

        bool jumpnumber_on() const { return _jumpnumber_on; }

        void change_jumpnumber() { _jumpnumber_on = !_jumpnumber_on; }

        void set_bgm_volume(int volume) { _bgm_volume = volume; }

        void set_sound_volume(int volume) { _sound_volume = volume;  }

    };

    // 处理BGM，音效等信息
    class MusicPlayer
    {
        Widget* _parent;

    public:
        QMediaPlayer *_bgm, * _clap_sound, * _sword_sound, * _punch_sound, * _choose_sound, *_trick_sound,
            * _bomb_sound, * _shield_defend, * _heal_sound, * _air_sound, * _fast_sword_sound, * _fast_stab_sound, * _pat_sound;
        QAudioOutput* _bgm_output, * _sound_output[12];
        MusicPlayer(Widget *parent)
            : _parent(parent)
        {
            // BGM 与 音效 集合
            _bgm = new QMediaPlayer(_parent);
            _clap_sound = new QMediaPlayer(_parent);
            _sword_sound = new QMediaPlayer(_parent);
            _punch_sound = new QMediaPlayer(_parent);
            _choose_sound = new QMediaPlayer(_parent);
            _bomb_sound = new QMediaPlayer(_parent);
            _shield_defend = new QMediaPlayer(_parent);
            _heal_sound = new QMediaPlayer(_parent);
            _air_sound = new QMediaPlayer(_parent);
            _fast_sword_sound = new QMediaPlayer(_parent);
            _fast_stab_sound = new QMediaPlayer(_parent);
            _pat_sound = new QMediaPlayer(_parent);
            _trick_sound = new QMediaPlayer(_parent);

            _bgm_output = new QAudioOutput(_parent);
            _bgm_output->setVolume(_parent->_game_setting._bgm_volume / 100.0);
            for (int i = 0; i < 12; i++)
            {
                _sound_output[i] = new QAudioOutput(_parent);
                _sound_output[i]->setVolume(_parent->_game_setting._sound_volume / 100.0);
            }

            _clap_sound->setSource(QUrl::fromLocalFile("music/clap_sound.mp3"));
            _sword_sound->setSource(QUrl::fromLocalFile("music/sword_sound.mp3"));
            _punch_sound->setSource(QUrl::fromLocalFile("music/punch_sound.mp3"));
            _choose_sound->setSource(QUrl::fromLocalFile("music/choose_sound.mp3"));
            _bomb_sound->setSource(QUrl::fromLocalFile("music/bomb_sound.wav"));
            _shield_defend->setSource(QUrl::fromLocalFile("music/shield_defend.wav"));
            _heal_sound->setSource(QUrl::fromLocalFile("music/heal_sound.wav"));
            _air_sound->setSource(QUrl::fromLocalFile("music/air_sound.wav"));
            _fast_sword_sound->setSource(QUrl::fromLocalFile("music/fast_sword_sound.wav"));
            _fast_stab_sound->setSource(QUrl::fromLocalFile("music/fast_stab_sound.mp3"));
            _pat_sound->setSource(QUrl::fromLocalFile("music/pat_sound.wav"));
            _trick_sound->setSource(QUrl::fromLocalFile("music/trick_sound.wav"));

            _clap_sound->setAudioOutput(_sound_output[0]);
            _sword_sound->setAudioOutput(_sound_output[1]);
            _punch_sound->setAudioOutput(_sound_output[2]);
            _choose_sound->setAudioOutput(_sound_output[3]);
            _bomb_sound->setAudioOutput(_sound_output[4]);
            _shield_defend->setAudioOutput(_sound_output[5]);
            _heal_sound->setAudioOutput(_sound_output[6]);
            _air_sound->setAudioOutput(_sound_output[7]);
            _fast_sword_sound->setAudioOutput(_sound_output[8]);
            _fast_stab_sound->setAudioOutput(_sound_output[9]);
            _pat_sound->setAudioOutput(_sound_output[10]);
            _trick_sound->setAudioOutput(_sound_output[11]);

            _bgm->setAudioOutput(_bgm_output);
        }

        void bgm_play(const QString& address)
        {
            if (QUrl::fromLocalFile(address) == _bgm->source())
                return;
            _bgm->stop();
            _bgm->setSource(QUrl::fromLocalFile(address));
            _bgm->setLoops(QMediaPlayer::Infinite);
            _bgm->play();
        }

        void stage_play()
        {
            bgm_play("music/stage_" + QString::number(_parent->_game_loader._stage_big) + ".mp3");
        }

    };

    // 设置菜单
    class Optionmenu : public QLabel
    {
    private:
        Widget* _parent;

        int _last_condition;

        QLabel *_bgm_label, *_sound_label;
        QSlider *_bgm_slider, *_sound_slider;
        QLabel *_jumpnum_label, *_jumpnumber_button_label, *_label;
        HoverButton *_jumpnumber_button;
        HoverButton* _close_button;
        HoverButton* _main_menu_button;
        HoverButton* _just_close_button;
    public:
        Optionmenu(Widget* parent, int last_condition)
            : QLabel(parent), _parent(parent), _last_condition(last_condition)
        {
            this->setGeometry(0, 0, 1000, 600);
            this->setVisible(true);
            this->setPixmap(QPixmap("picture/icon/option.png"));

            _bgm_label = new QLabel(_parent);
            _bgm_label->setGeometry(Optino_Bgm_Label_X_Center - Option_Bgm_Label_Width / 2, Option_Bgm_Label_Y_Center - Option_Bgm_Label_Height / 2,
                Option_Bgm_Label_Width, Option_Bgm_Label_Height);
            _bgm_label->setVisible(true);
            _bgm_label->setFont(QFont(QFontDatabase::applicationFontFamilies(0).at(0), 20));
            _bgm_label->setText("BGM:");
            _bgm_label->setAlignment(Qt::AlignCenter);
            _bgm_label->setAttribute(Qt::WA_TranslucentBackground);

            _bgm_slider = new QSlider(Qt::Horizontal, _parent);
            _bgm_slider->setGeometry(Option_Bgm_Slider_X_Center - Option_Bgm_Slider_X_Center / 2, Option_Bgm_Slider_Y_Center - Option_Bgm_Slider_Height / 2,
                Option_Bgm_Slider_Width, Option_Bgm_Slider_Height);
            _bgm_slider->setVisible(true);
            _bgm_slider->setMaximum(100);
            _bgm_slider->setMinimum(0);
            _bgm_slider->setValue(_parent->_music_player._bgm_output->volume() * 100);
            connect(_bgm_slider, &QSlider::valueChanged, _parent, &Widget::change_bgm_volume);

            _sound_label = new QLabel(_parent);
            _sound_label->setGeometry(Option_Sound_Label_X_Center - Option_Sound_Label_Width / 2, Option_Sound_Label_Y_Center - Option_Sound_Label_Height / 2,
                Option_Sound_Label_Width, Option_Sound_Label_Height);
            _sound_label->setVisible(true);
            _sound_label->setFont(QFont(QFontDatabase::applicationFontFamilies(0).at(0), 20));
            _sound_label->setText("Sound:");
            _sound_label->setAlignment(Qt::AlignCenter);
            _sound_label->setAttribute(Qt::WA_TranslucentBackground);

            _sound_slider = new QSlider(Qt::Horizontal, _parent);
            _sound_slider->setGeometry(Option_Sound_Slider_X_Center - Option_Sound_Slider_X_Center / 2, Option_Sound_Slider_Y_Center - Option_Sound_Slider_Height / 2,
                Option_Sound_Slider_Width, Option_Sound_Slider_Height);
            _sound_slider->setVisible(true);
            _sound_slider->setMaximum(100);
            _sound_slider->setMinimum(0);
            _sound_slider->setValue(_parent->_music_player._sound_output[0]->volume() * 100);
            connect(_sound_slider, &QSlider::valueChanged, _parent, &Widget::change_sound_volume);

            _jumpnum_label = new QLabel(_parent);
            _jumpnum_label->setGeometry(Option_Jumpnumber_Label_X_Center - Option_Jumpnumber_Label_Width / 2, Option_Jumpnumber_Label_Y_Center - Option_Jumpnumber_Label_Height / 2,
                Option_Jumpnumber_Label_Width, Option_Jumpnumber_Label_Height);
            _jumpnum_label->setVisible(true);
            _jumpnum_label->setFont(QFont(QFontDatabase::applicationFontFamilies(0).at(0), 20));
            _jumpnum_label->setText("JumpNumber:");
            _jumpnum_label->setAlignment(Qt::AlignCenter);
            _jumpnum_label->setAttribute(Qt::WA_TranslucentBackground);

            _jumpnumber_button = new HoverButton(_parent);
            _jumpnumber_button->setGeometry(Option_Jumpnumber_Button_X_Center - Option_Jumpnumber_Button_Width / 2, Option_Jumpnumber_Button_Y_Center - Option_Jumpnumber_Button_Height / 2,
                Option_Jumpnumber_Button_Width, Option_Jumpnumber_Button_Height);
            _jumpnumber_button->setIconSize(_jumpnumber_button->size());
            _jumpnumber_button->setIcon(QPixmap("picture/icon/blank_frame.png").scaled(_jumpnumber_button->size()));
            _jumpnumber_button->setVisible(true);
            _jumpnumber_button_label = new QLabel(_jumpnumber_button);
            _jumpnumber_button_label->setGeometry(0, 0, _jumpnumber_button->width(), _jumpnumber_button->height());
            _jumpnumber_button_label->setAttribute(Qt::WA_TranslucentBackground);
            _jumpnumber_button_label->setFont(QFont(QFontDatabase::applicationFontFamilies(0).at(0), 20));
            _jumpnumber_button_label->setAlignment(Qt::AlignCenter);

            if (_parent->_game_setting.jumpnumber_on())
            {
                _jumpnumber_button_label->setText("ON");
            }
            else
            {
                _jumpnumber_button_label->setText("OFF");
            }
            _jumpnumber_button_label->setVisible(true);

            connect(_jumpnumber_button, &QPushButton::clicked, [this]()->void {
                _parent->_game_setting.change_jumpnumber();
                if (_parent->_game_setting.jumpnumber_on())
                    _jumpnumber_button_label->setText("ON");
                else 
                    _jumpnumber_button_label->setText("OFF");

                if (this->_parent->_game_condition == GamePause)
                {
                    _parent->_game_loader._hero->set_jumpnumber(_parent->_game_setting.jumpnumber_on());
                    _parent->_game_loader._enemy->set_jumpnumber(_parent->_game_setting.jumpnumber_on());
                }

                this->_parent->_music_player._choose_sound->play();
            });

            connect(_jumpnumber_button, &HoverButton::enter, [=]()->void {
                _jumpnumber_button->setIcon(QPixmap("picture/icon/blank_frame_hover.png").scaled(_jumpnumber_button->size()));
                });
            connect(_jumpnumber_button, &HoverButton::leave, [=]()->void {
                _jumpnumber_button->setIcon(QPixmap("picture/icon/blank_frame.png").scaled(_jumpnumber_button->size()));
                });

            _close_button = new HoverButton(_parent);
            _close_button->setGeometry(Option_Close_Button_X_Center - Option_Close_Button_Width / 2, Option_Close_Button_Y_Center - Option_Close_Button_Height / 2,
                Option_Close_Button_Width, Option_Close_Button_Height); _jumpnumber_button->setIcon(QPixmap("picture/icon/blank_frame.png").scaled(_jumpnumber_button->size()));
            _close_button->setVisible(true);
            _close_button->setIconSize(_close_button->size());
            _close_button->setIcon(QPixmap("picture/icon/blank_frame.png").scaled(_close_button->size()));
            
            _label = new QLabel(_close_button);
            _label->setGeometry(0, 0, _close_button->width(), _close_button->height());
            _label->setAttribute(Qt::WA_TranslucentBackground);
            _label->setFont(QFont(QFontDatabase::applicationFontFamilies(3).at(0), 40));
            _label->setAlignment(Qt::AlignCenter);
            _label->setText("X");
            _label->setVisible(true);

            connect(_close_button, &QPushButton::clicked, [this]()->void {
                _parent->set_condition(_last_condition);

                if (_parent->game_condition() == GamePause)
                {
                    _parent->set_game_condition(GameFighting);
                }
                this->_parent->_music_player._choose_sound->play();

                _parent->set_option_menu(nullptr);
                this->deleteLater();
                });
            connect(_close_button, &HoverButton::enter, [=]()->void {
                _close_button->setIcon(QPixmap("picture/icon/blank_frame_hover.png").scaled(_close_button->size()));
                });
            connect(_close_button, &HoverButton::leave, [=]()->void {
                _close_button->setIcon(QPixmap("picture/icon/blank_frame.png").scaled(_close_button->size()));
                });

            _main_menu_button = new HoverButton(_parent);
            _main_menu_button->setGeometry(Option_Menu_X_Center - 100 - 80, Option_Menu_Y_Center + Option_Menu_Height / 2 - 30,
                160, 50);
            _main_menu_button->setIconSize(_main_menu_button->size());
            _main_menu_button->setIcon(QPixmap("picture/icon/blank_frame.png").scaled(_main_menu_button->size()));

            _label = new QLabel(_main_menu_button);
            _label->setGeometry(0, 0, _main_menu_button->width(), _main_menu_button->height());
            _label->setAttribute(Qt::WA_TranslucentBackground);
            _label->setFont(QFont(QFontDatabase::applicationFontFamilies(0).at(0), 16));
            _label->setAlignment(Qt::AlignCenter);
            _label->setText("Main Menu");
            if (_parent->game_condition() == GamePause)
            {
                _main_menu_button->setVisible(true);
                _label->setVisible(true);
            }

            connect(_main_menu_button, &QPushButton::clicked, [this]()->void {

                _parent->_game_loader.game_quit();
                _parent->set_condition(MainMenu);
                _parent->set_game_condition(GameFighting);

                this->_parent->_music_player._choose_sound->play();
                
                this->deleteLater();
                _parent->set_option_menu(nullptr);
                });
            connect(_main_menu_button, &HoverButton::enter, [=]()->void {
                _main_menu_button->setIcon(QPixmap("picture/icon/blank_frame_hover.png").scaled(_main_menu_button->size()));
                });
            connect(_main_menu_button, &HoverButton::leave, [=]()->void {
                _main_menu_button->setIcon(QPixmap("picture/icon/blank_frame.png").scaled(_main_menu_button->size()));
                });

            _just_close_button = new HoverButton(_parent);
            _just_close_button->setGeometry(Option_Menu_X_Center + 100 - 80, Option_Menu_Y_Center + Option_Menu_Height / 2 - 30,
                160, 50);
            _just_close_button->setIconSize(_just_close_button->size());
            _just_close_button->setIcon(QPixmap("picture/icon/blank_frame.png").scaled(_just_close_button->size()));

            _label = new QLabel(_just_close_button);
            _label->setGeometry(0, 0, _just_close_button->width(), _just_close_button->height());
            _label->setAttribute(Qt::WA_TranslucentBackground);
            _label->setFont(QFont(QFontDatabase::applicationFontFamilies(0).at(0), 16));
            _label->setAlignment(Qt::AlignCenter);
            _label->setText("Game View");

            connect(_just_close_button, &QPushButton::clicked, [this]()->void {
                this->_parent->_music_player._choose_sound->play();
                this->deleteLater();
                _parent->set_option_menu(nullptr);
                });
            connect(_just_close_button, &HoverButton::enter, [=]()->void {
                _just_close_button->setIcon(QPixmap("picture/icon/blank_frame_hover.png").scaled(_just_close_button->size()));
                });
            connect(_just_close_button, &HoverButton::leave, [=]()->void {
                _just_close_button->setIcon(QPixmap("picture/icon/blank_frame.png").scaled(_just_close_button->size()));
                });

            if (_parent->game_condition() == GamePause)
            {
                _label->setVisible(true);
                _just_close_button->setVisible(true);
            }
        }

        ~Optionmenu() {
            _bgm_label->deleteLater();  _sound_label->deleteLater();
            _bgm_slider->deleteLater();  _sound_slider->deleteLater();
            _jumpnum_label->deleteLater();
            _jumpnumber_button->deleteLater();
            _close_button->deleteLater();
            _main_menu_button->deleteLater();
            _just_close_button->deleteLater();
        }
    };

    // 主菜单
    class Mainmenu
    {
    private:
        const QString _string_start_game = "Start Game";
        const QString _string_load_game = "Load Game";
        const QString _string_option = "Option";
        const QString _string_tutorial = "Tutorial";

        HoverButton
            *_button_start = nullptr,
            *_button_load = nullptr,
            *_button_option = nullptr,
            *_button_tutorial = nullptr;

        QLabel *_headline = nullptr;

//        QHBoxLayout *_achievement_option;
//        QVBoxLayout *_buttons;

        bool _visable = 0;

        Widget *_parent;

        // 可用临时变量
        QLabel* sign = nullptr;
        QPushButton* button = nullptr;

    public:

        Mainmenu(Widget *parent) : _parent(parent) { }

        void show()
        {
            if (!_visable)
            {
                _headline = new QLabel(_parent);

                _button_start = new HoverButton(_parent);
                _button_load = new HoverButton(_parent);
                _button_tutorial = new HoverButton(_parent);
                _button_option = new HoverButton(_parent);

                qDebug() << "Button set\n";

                _button_start->setGeometry(New_Game_Button_X_Center - New_Game_Button_Width / 2, New_Game_Button_Y_Center - New_Game_Button_Height / 2,
                    New_Game_Button_Width, New_Game_Button_Height);
                _button_load->setGeometry(Load_Game_Button_X_Center - Load_Game_Button_Width / 2, Load_Game_Button_Y_Center - Load_Game_Button_Height / 2,
                    Load_Game_Button_Width, Load_Game_Button_Height);
                _button_option->setGeometry(Options_Button_X_Center - Options_Button_Width / 2, Options_Button_Y_Center - Options_Button_Height / 2,
                    Options_Button_Width, Options_Button_Height);
                _button_tutorial->setGeometry(Tutorial_Button_X_Center - Tutorial_Button_Width / 2, Tutorial_Button_Y_Center - Tutorial_Button_Height / 2,
                    Tutorial_Button_Width, Tutorial_Button_Height);

                _button_start->setIconSize(_button_start->size());
                _button_option->setIconSize(_button_option->size());
                _button_load->setIconSize(_button_load->size());
                _button_tutorial->setIconSize(_button_tutorial->size());

                _button_start->setIcon(QPixmap(NewGameButton_Address));
                _button_option->setIcon(QPixmap(OptionButton_Address));
                _button_load->setIcon(QPixmap(LoadGameButton_Address));
                _button_tutorial->setIcon(QPixmap(TutorialButton_Address));

                _button_start->setFlat(true);
                _button_option->setFlat(true);
                _button_load->setFlat(true);
                _button_tutorial->setFlat(true);

                _button_start->setStyleSheet("background:transparent");
                _button_option->setStyleSheet("background:transparent");
                _button_load->setStyleSheet("background:transparent");
                _button_tutorial->setStyleSheet("background:transparent");

                _button_start->setVisible(true);
                _button_load->setVisible(true);
                _button_option->setVisible(true);
                _button_tutorial->setVisible(true);

                connect(_button_start, &QPushButton::clicked, [this]()->void{
                    this->_parent->start_game();
                    this->_parent->_music_player._choose_sound->play();
                });
                connect(_button_start, &HoverButton::enter, [this]()->void {
                    this->_button_start->setIcon(QPixmap(NewGameButtonHover_Address));
                    });
                connect(_button_start, &HoverButton::leave, [this]()->void {
                    this->_button_start->setIcon(QPixmap(NewGameButton_Address));
                    });

                connect(_button_load, &QPushButton::clicked, [this]()->void {
                    _parent->show_save();
                    this->_parent->_music_player._choose_sound->play();
                });
                connect(_button_load, &HoverButton::enter, [this]()->void {
                    this->_button_load->setIcon(QPixmap(LoadGameButtonHover_Address));
                    });
                connect(_button_load, &HoverButton::leave, [this]()->void {
                    this->_button_load->setIcon(QPixmap(LoadGameButton_Address));
                    });

                connect(_button_option, &QPushButton::clicked, [this]()->void {
                    if (!_parent->option_on())
                        _parent->set_option_menu(new Optionmenu(this->_parent, MainMenu));

                    this->_parent->_music_player._choose_sound->play();
                    });
                connect(_button_option, &HoverButton::enter, [this]()->void {
                    this->_button_option->setIcon(QPixmap(OptionButtonHover_Address));
                    });
                connect(_button_option, &HoverButton::leave, [this]()->void {
                    this->_button_option->setIcon(QPixmap(OptionButton_Address));
                    });

                connect(_button_tutorial, &QPushButton::clicked, [this]()->void {
                    this->_parent->_music_player._choose_sound->play();
                    sign = new QLabel(_parent);
                    sign->setGeometry(200, 25, 600, 550);
                    sign->setStyleSheet("background-color:rgb(255,255,255)");
                    sign->setVisible(true);
                    sign->setFrameStyle(QFrame::Box);

                    QLabel* temp = new QLabel(sign);
                    temp->setGeometry(100, 10, 400, 240);
                    temp->setPixmap(QPixmap("picture/icon/tutorial.png").scaled(temp->size()));
                    temp->setVisible(true);

                    temp = new QLabel(sign);
                    temp->setGeometry(20, 240, 560, 280);
                    temp->setText("Press \"space\" when sword is above a block\n"
                        "Just Remember these things:\n"\
                        "1, Don't make red/purple/black blocks access left\n"
                        "2, Using 's' to trigger special skill to knock back blocks\n"
                        "3, Using \"esc\" to pause\n"
                        "4, Different blocks have different functions\n"
                        "please find block functions by yourself\n"
                        "Have fun :)");
                    temp->setVisible(true);
                    temp->setFont(QFont("", 16));
                    temp->setAlignment(Qt::AlignCenter);

                    button = new QPushButton(_parent);
                    button->setGeometry(420, 520, 160, 50);
                    button->setText("Main Menu");
                    button->setVisible(true);

                    connect(button, &QPushButton::clicked, [this]()->void {
                        _parent->_music_player._choose_sound->play();
                        sign->deleteLater();
                        button->deleteLater();
                        });
                    });

                connect(_button_tutorial, &HoverButton::enter, [this]()->void {
                    this->_button_tutorial->setIcon(QPixmap(TutorialButtonHover_Address));
                    });
                connect(_button_tutorial, &HoverButton::leave, [this]()->void {
                    this->_button_tutorial->setIcon(QPixmap(TutorialButton_Address));
                    });

                _visable = 1;
            }
        }

        void close()
        {
            if (_visable)
            {
                delete _button_start;
                delete _button_load;
                delete _button_tutorial;
                delete _button_option;

                _visable = 0;
            }
        }

    };

    // 游戏处理
    class GameLoader
    {

    public:
        Widget *_parent;

        Enemy *_enemy;

        Hero *_hero;

        // 浮标
        MovingSign* _moving_sign;
        OperationBar *_bar[3];
        QLabel* _operationbar_frame;
        QLabel* _operationbar_board;

        //BlockLoader* _white_block_loader, * _red_block_loader;

        int _bar_count = 1;

        bool _upgraded = 0;
        QLabel *_upgrade_menu = nullptr;
        HoverButton *_upgrade_buttons[3] {};

        QLabel *_stage_sign = nullptr;
        int _stage_small = 1;
        int _stage_big = 1;

        QLabel *_over_sign = nullptr;
        QPushButton *_over_button = nullptr;
        bool _over = 0;

        // 可用临时变量
        QLabel* _loader_sign = nullptr;
        HoverButton* _loader_button = nullptr;

        QLabel* _trick = nullptr;
        int _trick_movement = 0, _trick_movement_change_count = 0;
        int _trick_count = 5;

        QLabel* _trick_bomb = nullptr;
        int _trick_bomb_movement = 0, trick_bomb_change_count = 0;

        QLabel* _instruction = nullptr;

    public:
        GameLoader(Widget *parent) : _parent(parent) {

        }

        double calc_stage_index() const 
        {
            int tot = (_stage_big - 1) * 10 + _stage_small;
            return upgrade_index[tot];
        }

        bool trick_avalible() const { return _hero->trick_avalible(); }

        void clear_trick()
        {
            delete _trick;
            _trick = nullptr;
        }

        void generate_trick()
        {
            _parent->_music_player._trick_sound->play();
            delete _trick;
            _trick = new QLabel(_parent);
            _trick->setGeometry(Trick_Start_X_Center - Trick_Width / 2, Trick_Start_Y_Center - Trick_Height / 2,
                Trick_Width, Trick_Height);
            _trick->setVisible(true);
            _hero->set_hit_count_zero();
        }

        void trick_move()
        {
            if (_trick)
            {
                _trick->move(_trick->x() + Trick_Velocity, _trick->y());
                if (_trick_movement_change_count++ == 0)
                {
                    _trick->setPixmap(Trick_Movement[_trick_movement++]);
                    if (_trick_movement == 4)
                        _trick_movement = 0;
                }
                else
                {
                    _trick_movement_change_count++;
                    if (_trick_movement_change_count == 15)
                        _trick_movement_change_count = 0;
                }

                if (_trick->x() + Trick_Width / 2 >= Trick_End_X_Center)
                {
                    trigger_trick();
                    delete _trick;
                    _trick = nullptr;
                }
            }
            if (_trick_bomb)
            {
                if (trick_bomb_change_count == 0)
                {
                    if (_trick_bomb_movement == 4)
                    {
                        _trick_bomb->deleteLater();
                        _trick_bomb = nullptr;
                        trick_bomb_change_count = 0;
                        _trick_bomb_movement = 0;
                    }
                    else
                    {
                        _trick_bomb->setPixmap(Trick_Trigger_Movement[_trick_bomb_movement++]);
                        trick_bomb_change_count++;
                    }
                }
                else
                {
                    trick_bomb_change_count++;
                    if (trick_bomb_change_count == 8)
                        trick_bomb_change_count = 0;
                }
            }
        }

        void trigger_trick()
        {
            _parent->_music_player._bomb_sound->play();
            _enemy->magical_hurt(_hero->attackage_magic());
             red_block_retreat(Retreat_Velocity);
             _trick_bomb = new QLabel(_parent);
             _trick_bomb->setGeometry(_trick->x() + Trick_Width / 2 - 32, _trick->y() + Trick_Height / 2 - 32, 64, 64);
             _trick_bomb->setVisible(true);
             _trick_bomb->setAttribute(Qt::WA_TranslucentBackground);
        }

        void trick_clear()
        {
            delete _trick;
            _trick = nullptr;
            delete _trick_bomb;
            _trick_bomb = nullptr;
        }

        void red_block_retreat(double retreat_velocity)
        {
            for (int i = 0; i < _bar_count; i++)
            {
                _bar[i]->red_blocks_retreat(retreat_velocity);
            }
        }

        void bar_clear()
        {
            for (int i = 0; i < _bar_count; i++)
                _bar[i]->clear_blocks();
        }

        void trigger_hit_bound() {
            for (int i = 0; i < _bar_count; i++)
                _bar[i]->trigger_hit_bound();
        }

        void trigger_access_left() {
            for (int i = 0; i < _bar_count; i++)
                _bar[i]->trigger_access_lefts();
        }

        void trigger_access_right() {
            for (int i = 0; i < _bar_count; i++)
                _bar[i]->trigger_access_rights();
        }

        void clear_nulls() {
            for (int i = 0; i < _bar_count; i++)
                _bar[i]->clear_nulls();
        }

        void blocks_moving() {
            for (int i = 0; i < _bar_count; i++)
                _bar[i]->blocks_moving();
        }

        void sign_moving() {
            _moving_sign->move_on_bar();
        }

        void load_blocks() {
            for (int i = 0; i < _bar_count; i++)
            {
                _bar[i]->loader_load();
            }

        }

        void hero_normal_attack() {
            _hero->start_attack_move();
            int attackage = _hero->attackage_rand();
            _enemy->physical_hurt(attackage);
        }

        void hero_critic_attack() {
            _hero->start_attack_move();
            int attackage = _hero->attackage_max();
            _enemy->physical_hurt(attackage);
        }

        void enemy_normal_attack() {
            _enemy->start_attack_move();
            int attackage = _enemy->attackage_rand();
            _hero->hurt(attackage);
        }

        void enemy_critic_attack() {
            _enemy->start_attack_move();
            int attackage = _enemy->attackage_max();
            _hero->hurt(attackage);
        }

        void enemy_steal_health() {
            _enemy->start_attack_move();
            int attackage = _enemy->attackage_rand();
            _hero->hurt(attackage);
            _enemy->heal(attackage);
        }

        BlockLoader* stage_block_loader(int y_center)
        {
            return new BlockLoader(_parent, StageBlocks[_stage_big], OperationBar_Left, OperationBar_Right, y_center);
        }

        // 从配置文件加载游戏
        void preload(GameSetting& game_setting)
        {
            _hero = new Hero(_parent, game_setting._max_health, game_setting._min_attack, game_setting._max_attack, game_setting._magic_attack);
            _hero->set_health(game_setting._health);
            _hero->set_jumpnumber(game_setting._jumpnumber_on);
            _hero->set_hit_count(game_setting._hit_count);
            if (game_setting._shield_on)
                _hero->get_shield();

            _enemy = nullptr;

            _bar_count = 1;
            _stage_small = game_setting._stage_small;
            _stage_big = game_setting._stage_big;

            preload_background();
        }
        // 加载人物及场景
        void preload()
        {
            _hero = new Hero(_parent);
            _hero->set_jumpnumber(_parent->jumpnumber_on());
            _enemy = nullptr;
            _bar_count = 1;
            _stage_small = _stage_big = 1;

            preload_background();
        }

        // 加载游戏用控件
        void preload_background()
        {
            if (!_hero)
            {
                qDebug() << "Error, hero must be loaded!\n";
            }

            _over = 0;
            _stage_sign = new QLabel(_parent);
            _stage_sign->setGeometry(Stage_Sign_X_Center - Stage_Sign_Width / 2, Stage_Sign_Y_Center - Stage_Sign_Height / 2,
                Stage_Sign_Width, Stage_Sign_Height);
            _stage_sign->setAttribute(Qt::WA_TranslucentBackground);
            _stage_sign->setVisible(true);
            _stage_sign->setFont(QFont(QFontDatabase::applicationFontFamilies(2).at(0), 26));
            _stage_sign->setAlignment(Qt::AlignHCenter);
            _stage_sign->setText(QString::number(_stage_big) + "-" + QString::number(_stage_small));

            _operationbar_board = new QLabel(_parent);
            _operationbar_board->setGeometry(OperationBar_Board_X_Center - OperationBar_Board_Width / 2, OperationBar_Board_Y_Center - OperationBar_Board_Height / 2,
                OperationBar_Board_Width, OperationBar_Board_Height);
            _operationbar_board->setPixmap(QPixmap(Operationbar_Board_Address).scaled(_operationbar_board->size()));
            _operationbar_board->setVisible(true);
            _operationbar_board->setAttribute(Qt::WA_TranslucentBackground);

            _operationbar_frame = new QLabel(_parent);
            _operationbar_frame->setGeometry(OperationBar_Frame_X_Center - OperationBar_Frame_Width / 2, OperationBar_Frame_Y_Center - OperationBar_Frame_Height / 2,
                OperationBar_Frame_Width, OperationBar_Frame_Height);
            _operationbar_frame->setPixmap(QPixmap(Operationbar_Frame_Address).scaled(_operationbar_frame->size()));
            _operationbar_frame->setVisible(true);
            _operationbar_frame->setAttribute(Qt::WA_TranslucentBackground);

            _moving_sign = new MovingSign(_parent);

            _instruction = new QLabel(_parent);
            _instruction->setPixmap(QPixmap("picture/icon/instruction.png"));
            _instruction->setGeometry(496, 552, 424, 23);
            _instruction->setVisible(true);

            BlockLoader* block_loader;

            for (int i = 0; i < _bar_count; i++)
            {
                _bar[i] = new OperationBar(_parent, OperationBar_Board_X_Center, OperationBar_Board_Y_Center);
                block_loader = stage_block_loader(OperationBar_Board_Y_Center);
                block_loader->set_y_center(block_loader_y(i));
                _bar[i]->set_white_block_loader(block_loader);
                _bar[i]->set_moving_sign(_moving_sign);
                connect(_bar[i], &OperationBar::hero_normal_attack, _parent, &Widget::hero_normal_attack);
                connect(_bar[i], &OperationBar::hero_critic_attack, _parent, &Widget::hero_critic_attack);
                connect(_bar[i], &OperationBar::enemy_normal_attack, _parent, &Widget::enemy_normal_attack);
                connect(_bar[i], &OperationBar::enemy_critic_attack, _parent, &Widget::enemy_critic_attack);
                connect(_bar[i], &OperationBar::enemy_steal_health, _parent, &Widget::enemy_steal_health);
                connect(_bar[i], &OperationBar::enemy_fireball_hurt, _parent, &Widget::enemy_fireball_hurt);
                connect(_bar[i], &OperationBar::enemy_deadly_attack, _parent, &Widget::enemy_deadly_attack);
                connect(_bar[i], &OperationBar::hero_healing, _parent, &Widget::hero_healing);
                connect(_bar[i], &OperationBar::hero_lava_hurt, _parent, &Widget::hero_lava_hurt);
                connect(_bar[i], &OperationBar::hero_get_sheild, _parent, &Widget::hero_get_shield);
            }
        }

        // hero死亡，游戏结束
        void game_over()
        {
            if (!_over)
            {
                _over = 1;
                _over_sign = new QLabel(_parent);
                _over_sign->setGeometry(Gameover_Sign_X_Center - Gameover_Sign_Width / 2, Gameover_Sign_Y_Center - Gameover_Sign_Height / 2,
                                        Gameover_Sign_Width, Gameover_Sign_Height);
                _over_sign->setFrameStyle(QFrame::Box);
                _over_sign->setFont(QFont(QFontDatabase::applicationFontFamilies(0).at(0), 20));
                _over_sign->setStyleSheet("background-color:rgb(255,255,255)");
                _over_sign->setAlignment(Qt::AlignHCenter);
                _over_sign->setText("\n\n\n\n\nOh no!\n"
                                    "You are dead.\n"
                                    "Hopefully, you can win next time\n");
                _over_sign->setVisible(true);

                _over_button = new QPushButton(_parent);
                _over_button->setText("Main Menu");
                _over_button->setGeometry(Gameover_Button_X_Center - Gameover_Button_Width / 2, Gameover_Button_Y_Center - Gameover_Button_Height / 2,
                                          Gameover_Button_Width, Gameover_Button_Height);
                _over_button->setVisible(true);
                connect(_over_button, &QPushButton::clicked, [this]()->void{
                    this->_parent->_music_player._choose_sound->play();
                    this->_over_sign->deleteLater();
                    this->_over_button->deleteLater();
                    this->_parent->set_condition(MainMenu);
                    this->game_quit();
                });
            }
        }

        // 关闭游戏场景
        void game_quit()
        {
            if (_hero)
                _hero->deleteLater();
            if (_enemy)
                _enemy->deleteLater();
            for (int i = 0; i < _bar_count; i++)
            {
                _bar[i]->delete_blocks();
                _bar[i]->deleteLater();
            }
            if (_stage_sign)
                _stage_sign->deleteLater();
            if (_moving_sign)
                _moving_sign->deleteLater();
            if (_operationbar_frame)
                _operationbar_frame->deleteLater();
            if (_operationbar_board)
                _operationbar_board->deleteLater();
            if (_trick)
            {
                _trick->deleteLater();
                _trick = nullptr;
            }
            if (_instruction)
                _instruction->deleteLater();
        }

        bool hero_enter()
        {
            _hero->move(_hero->x() + 3, _hero->y());
            if (_hero->arrive())
            {
                return 1;
            }
            return 0;
        }

        void set_white_block(const std::vector<int> &blocks)
        {
            for (int i = 0; i < _bar_count; i++)
            {
                _bar[i]->set_white_blocks(blocks);
            }
        }

        bool hero_march()
        {
            _hero->move(_hero->x() + 3, _hero->y());
            if (_hero->x() > Main_Window_Width)
            {
                return 1;
            }
            return 0;
        }

        bool enemy_enter()
        {
            _enemy->move(_enemy->x() - 3, _enemy->y());
            if (_enemy->arrive())
            {
                return 1;
            }
            return 0;
        }

        bool is_stage_boss()
        {
            return _stage_small == Stage_Num_Each;
        }

        bool is_stage_clear()
        {
            return _stage_small == Stage_Num_Each + 1;
        }

        bool enemy_flee()
        {
            _enemy->move(_enemy->x() + 6, _enemy->y());
            if (_enemy->fled())
            {
                _enemy->deleteLater();
                _enemy = nullptr;
                return 1;
            }
            return 0;
        }

        void set_upgrade_string(QPushButton * button, int string_kind)
        {
            int rand_int = rand() % (Upgrade_Range_Max - Upgrade_Range_Min) + Upgrade_Range_Min;
            if (string_kind == RaiseBothAttack)
            {
                rand_int -= log(_parent->_game_loader._hero->min_attack()) * log(_parent->_game_loader._hero->max_attack()) - 5;
                if (rand_int < 10)
                    rand_int = 10;
            }
            else if (string_kind == RaiseMaxHealth)
            {
                rand_int += 20 - log(_parent->_game_loader._hero->max_health()) * log(_parent->_game_loader._hero->max_health());
                if (rand_int < 12)
                    rand_int = 12;
            }
            else if (string_kind == RaiseMagicAttack)
            {
                rand_int -= log(_parent->_game_loader._hero->magic_attack()) * log(_parent->_game_loader._hero->magic_attack());
                if (rand_int < 8)
                    rand_int < 8;
            }

            QLabel* label = new QLabel(button);
            label->setGeometry(0, 0, button->width() - 63, button->height());
            label->setAttribute(Qt::WA_TranslucentBackground);
            label->setAlignment(Qt::AlignCenter);
            label->setFont(QFont(QFontDatabase::applicationFontFamilies(0).at(0), 16));
            label->setVisible(true);

            if (string_kind != Heal)
            {
                label->setText(Upgrade_Strings[string_kind] + " " + QString::number(rand_int) + "%");
            }
            else if (string_kind == Heal)
            {
                label->setText(Upgrade_Strings[string_kind]);
            }
            switch (string_kind) {
            case RaiseMaxHealth:
                connect(button, &QPushButton::clicked, _hero, [=]()->void {
                    _hero->upgrade_max_health(rand_int / 100.0);
                    this->_upgraded = 1;
                });
                break;
            case RaiseBothAttack:
                connect(button, &QPushButton::clicked, _hero, [=]()->void {
                    _hero->upgrade_attack_low(rand_int / 100.0);
                    _hero->upgrade_attack_high(rand_int / 100.0);
                    this->_upgraded = 1;
                });
                break;
            //case RaiseMaxAttack:
            //    connect(button, &QPushButton::clicked, _hero, [=]()->void {
            //        _hero->upgrade_attack_high(rand_int / 100.0);
            //        this->_upgraded = 1;
            //    });
            //    break;
            case Heal:
                connect(button, &QPushButton::clicked, _hero, [=]()->void {
                    _hero->perfect_heal();
                    this->_upgraded = 1;
                });
                break;
            case RaiseMagicAttack:
                connect(button, &QPushButton::clicked, _hero, [=]()->void {
                    _hero->upgrade_attack_magic(rand_int / 100.0);
                    this->_upgraded = 1;
                    });
            }

            connect(button, &QPushButton::clicked, [this]()->void {
                this->_parent->_music_player._choose_sound->play();
                });
        }

        bool hero_upgrade()
        {
            if (!_upgrade_menu)
            {
                _upgrade_menu = new QLabel(_parent);

                _upgrade_menu->setGeometry(Upgrade_Menu_X_Center - Upgrade_Menu_Width / 2, Upgrade_Menu_Y_Center - Upgrade_Menu_Height / 2,
                                           Upgrade_Menu_Width, Upgrade_Menu_Height);
                _upgrade_menu->setVisible(true);
                _upgrade_menu->setPixmap(QPixmap("picture/icon/upgrade.png"));


                bool vis[Upgrade_String_num] { };
                int choose;
                for (int i = 0; i < 3; i++)
                {
                    while (vis[choose = rand() % Upgrade_String_num]);
                    vis[choose] = 1;
                    _upgrade_buttons[i] = new HoverButton(_parent);
                    _upgrade_buttons[i]->setGeometry(Upgrade_Button_X[i], Upgrade_Button_Y[i], Upgrade_Button_Width, Upgrade_Button_Height);
                    _upgrade_buttons[i]->setVisible(true);
                    set_upgrade_string(_upgrade_buttons[i], choose);
                    _upgrade_buttons[i]->setIconSize(_upgrade_buttons[i]->size());
                    _upgrade_buttons[i]->setIcon(QPixmap("picture/icon/blank_button.png"));
                    _upgrade_buttons[i]->setFlat(true);
                    _upgrade_buttons[i]->setStyleSheet("background:transparent");

                    connect(_upgrade_buttons[i], &HoverButton::enter, [=]()-> void {
                        _upgrade_buttons[i]->setIcon(QPixmap("picture/icon/blank_button_hover.png"));
                        });
                    connect(_upgrade_buttons[i], &HoverButton::leave, [=]()-> void {
                        _upgrade_buttons[i]->setIcon(QPixmap("picture/icon/blank_button.png"));
                        });
                }

                _upgraded = 0;
            }
            if (_upgraded)
            {
                _hero->update();
                _upgrade_menu->deleteLater();
                _upgrade_menu = nullptr;
                for (int i = 0; i < 3; i++)
                {
                    _upgrade_buttons[i]->deleteLater();
                }

                return 1;
            }
            return 0;
        }

        int block_loader_y(int i)
        {
            if (_bar_count == 1)
            {
                return OperationBar_Y_Center;
            }
            else if (_bar_count == 2)
            {
                return OperationBar_Y_Center_Two[i];
            }
            else if (_bar_count == 3)
            {
                return OperationBar_Y_Center_Three[i];
            }
            qDebug() << "Error, No such block_loader_y!\n";
            return OperationBar_Y_Center;
        }

        bool generate_warrior_enemy()
        {
            int code = rand() % Stage_Enemy[_stage_big].size();
            _enemy = load_enemy(Stage_Enemy[_stage_big][code]);
            _enemy->set_jumpnumber(_parent->jumpnumber_on());
            _enemy->in_stage(_stage_big);
            BlockLoader *block_loader;
            for (int i = 0; i < _bar_count; i++)
            {
                block_loader = _enemy->block_loader();
                block_loader->set_y_center(block_loader_y(i));
                _bar[i]->set_red_block_loader(block_loader);
            }
            return 1;
        }

        bool generate_boss_enemy()
        {
            int code = rand() % Stage_Boss[_stage_big].size();
            _enemy = load_enemy(Stage_Boss[_stage_big][code]);
            _enemy->set_jumpnumber(_parent->jumpnumber_on());
            BlockLoader* block_loader;
            for (int i = 0; i < _bar_count; i++)
            {
                block_loader = _enemy->block_loader();
                block_loader->set_y_center(block_loader_y(i));
                _bar[i]->set_red_block_loader(block_loader);
            }
            return 1;
        }

        bool stage_won()
        {
            return hero_march();
        }

        void game_won()
        {
            _loader_sign = new QLabel(_parent);
            _loader_sign->setGeometry(0, 0, Main_Window_Width, Main_Window_Height);
            _loader_sign->setPixmap(QPixmap("picture/icon/option.png"));
            _loader_sign->setVisible(true);

            QLabel* label = new QLabel(_loader_sign);
            label->setGeometry(200, 100, 600, 400);
            label->setText("You have won the game!\n"
                    "thank you for playing!");
            label->setAlignment(Qt::AlignCenter);
            label->setFont(QFont(QFontDatabase::applicationFontFamilies(0).at(0), 30));
            label->setVisible(true);
            
            _loader_button = new HoverButton(_parent);
            _loader_button->setGeometry(420, 470, 160, 50);
            _loader_button->setIconSize(_loader_button->size());
            _loader_button->setIcon(QPixmap("picture/icon/blank_frame.png").scaled(_loader_button->size()));
            _loader_button->setVisible(true);

            connect(_loader_button, &HoverButton::enter, [=]()->void {
                _loader_button->setIcon(QPixmap("picture/icon/blank_frame_hover.png").scaled(_loader_button->size()));
                });
            connect(_loader_button, &HoverButton::leave, [=]()->void {
                _loader_button->setIcon(QPixmap("picture/icon/blank_frame.png").scaled(_loader_button->size()));
                });

            label = new QLabel(_loader_button); 
            label->setGeometry(0, 0, _loader_button->width(), _loader_button->height());
            label->setAlignment(Qt::AlignCenter);
            label->setText("Main Menu");
            label->setVisible(true);

            connect(_loader_button, &QPushButton::clicked, [this]()->void {
                delete _loader_sign;
                _loader_sign = nullptr;
                game_quit();

                _parent->set_game_condition(GameFighting);
                _parent->set_condition(MainMenu);
                _loader_button->deleteLater();
                _loader_button = nullptr;
                });
        }

        // GameFight的主体函数，游戏开始时每帧执行一次
        void load()
        {
            trick_move();

            _hero->attack_move();

            _enemy->attack_move();

            trigger_hit_bound();

            trigger_access_left();

            trigger_access_right();

            clear_nulls();

            blocks_moving();

            sign_moving();

            load_blocks();

            _hero->update();

            _enemy->update();

            _moving_sign->raise();
        }

        // 根据kind从enemy库中选取enemy
        Enemy* load_enemy(int kind = 0)
        {
            Enemy* ret = nullptr;
            switch (kind) {
            case None:
                ret = new Enemy(_parent);
                break;
            case SLIME:
                ret = new Slime(_parent);
                break;
            case TREANT:
                ret = new Treant(_parent);
                break;
            case LEPRECHAUN:
                ret = new Leprechaun(_parent);
                break;
            case BEAST:
                ret = new Beast(_parent);
                break;
            case GOBLIN:
                ret = new Goblin(_parent);
                break;
            case SLIMEQUEEN:
                ret = new SlimeQueen(_parent);
                break;
            case MONSTER:
                ret = new Monster(_parent);
                break;
            case BAT:
                ret = new Bat(_parent);
                break;
            case GOLEM:
                ret = new Golem(_parent);
                break;
            case STONESLIME:
                ret = new StoneSlime(_parent);
                break;
            case SKELETON:
                ret = new Skeleton(_parent);
                break;
            case GIANTGOLEM:
                ret = new GiantGolem(_parent);
                break;
            case MEDUSA:
                ret = new Medusa(_parent);
                break;
            case GUARD:
                ret = new Guard(_parent);
                break;
            case ARCHER:
                ret = new Archer(_parent);
                break;
            case WIZARD:
                ret = new Wizard(_parent);
                break;
            case SHIELD:
                ret = new Shield(_parent);
                break;
            case DARKKING:
                ret = new DarkKing(_parent);
                break;
            case MELIN:
                ret = new Melin(_parent);
                break;
            case LAVASLIME:
                ret = new LavaSlime(_parent);
                break;
            case DEMON:
                ret = new Demon(_parent);
                break;
            case UNDEADSKELETON:
                ret = new UndeadSkeleton(_parent);
                break;
            case SUCCUBUS:
                ret = new Succubus(_parent);
                break;
            case THEDEATH:
                ret = new TheDeath(_parent);
                break;
            case THECREATOR:
                ret = new TheCreator(_parent);
                break;
            default:
                ret = new Enemy(_parent);
            }
            ret->upgrade(calc_stage_index());
            ret->update();

            return ret;
        }
    };

    GameSetting _game_setting;

    GameBackGround _game_background;

    MusicPlayer _music_player;

    GameLoader _game_loader;

    Optionmenu* _option_menu = nullptr;

    Mainmenu _main_menu;

    Ui::Widget *ui;

    // 计时器
    QTimer *_main_timer;

public:

    void set_option_menu(Optionmenu* option_menu)
    {
        _option_menu = option_menu;
    }
    bool option_on() const { return _option_menu; }
    int game_condition() const { return _game_condition; }
};

#endif // WIDGET_H
