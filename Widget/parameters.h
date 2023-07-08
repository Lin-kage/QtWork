#ifndef PARAMETER_H
#define PARAMETER_H


// Block Settings

// Block的种类
const int Block_Kinds = 31;

enum {
    NoneBlock, // 占位
    WHITENormalBlock1, WHITENormalBlock2, WHITECriticBlock, WHITESolidBlock1,
    WHITESolidBlock2, WHITEHealingBlock, WHITEShieldBlock, WHITELavaBlock,

    REDNormalBlock1, REDNormalBlock2, REDFastBlock1, REDFastBlock2,
    REDBombBlock, REDSolidBlock1, REDSolidBlock2, REDCriticalBlock,
    REDSlimeBlock, REDGooBlock, REDShieldBlock, REDFireballBlock,
    REDIceballBlock, REDArmorBlock, REDBowBlock, REDArrowBlock,
    REDSoulingBlock1, REDSoulingBlock2, REDBoneBlock, REDDustBlock, 
    
    REDDeadBlock, WHITESwordBlock
};

// Block分类，在此对于各block的interval值进行统一定义，与上面保持顺序
/* 对每个Block需定义以下的值：
    length：默认长度
    width：默认宽度
    interval：不允许同种Block在interval个Block内出现两次及以上
    frequancy：出现该Block的概率权值，WHITENormalBlock为10
    velocity：速度，WhiteBlock一律为0
    path：图片路径
*/
const double Block_Velocity[Block_Kinds]{ 0,
    0, 0, 0, 0,
    0, 0, 0, 0,

    1.7, 1.5, 2.5, 3.2,
    1.7, 1.3, 1.5, 1.7,
    1.2, 1.2, 0.8, 2.5,
    2.0, 1.5, 1.5, 2,
    1.7, 1.7, 2.5, 0,

    1.2, 0
};
const int Block_Width[Block_Kinds]{ 0,
    80, 120, 60, 90,
    120, 80, 70, 100,

    80, 120, 70, 80,
    80, 90, 130, 80,
    160, 80, 140, 80,
    80, 120, 80, 100,
    80, 100, 80, 80,

    100, 80
};
const int Block_Height[Block_Kinds]{ 0,
    95, 95, 95, 95,
    95, 95, 95, 95,

    95, 95, 95, 95,
    95, 95, 95, 95,
    95, 95, 95, 95,
    95, 95, 95, 95,
    95, 95, 95, 95,
    
    95, 95
};
const double Block_Frequancy[Block_Kinds]{ 0,
    10, 10, 5, 8,
    8, 1, 5, 3, 
    
    10, 10, 6, 4,
    8, 8, 8, 5,
    8, 10, 5, 5,
    5, 5, 5, 10,
    8, 8, 10, 0,

    10000, 10000
};
const int Block_Intervals[Block_Kinds]{ 0,
    0, 0, 3, 1,
    1, 0, 3, 5,

    0, 0, 3, 5,
    3, 1, 1, 2,
    3, 1, 5, 5,
    7, 3, 3, 2,
    1, 1, 2, 0,

    1 << 31, 1 << 31
};
const QString Block_Path[Block_Kinds]{
    "None",

    "picture/block/WHITENormalBlock1.png",
    "picture/block/WHITENormalBlock2.png",
    "picture/block/WHITECriticalBlock.png",
    "picture/block/WHITESolidBlock1.png",

    "picture/block/WHITESolidBlock2.png",
    "picture/block/HealingBlock.png",
    "picture/block/WHITEShieldBlock.png",
    "picture/block/LavaBlock.png",

    "picture/block/REDNormalBlock1.png",
    "picture/block/REDNormalBlock2.png",
    "picture/block/REDFastBlock1.png",
    "picture/block/REDFastBlock2.png",

    "picture/block/REDBombBlock.png",
    "picture/block/REDSolidBlock1.png",
    "picture/block/REDSolidBlock2.png",
    "picture/block/REDCriticalBlock.png",

    "picture/block/REDSlimeBlock.png",
    "picture/block/REDGooBlock.png",
    "picture/block/REDShieldBlock.png",
    "picture/block/REDFireballBlock.png",

    "picture/block/REDIceballBlock.png",
    "picture/block/REDArmorBlock.png",
    "picture/block/REDBowBlock.png",
    "picture/block/REDArrowBlock.png",

    "picture/block/REDSoulingBlock1.png",
    "picture/block/REDSoulingBlock2.png",
    "picture/block/REDBoneBlock.png",
    "picture/block/REDDustBlock.png",

    "picture/block/REDDeadBlock.png",
    "picture/block/WHITESwordBlock.png",
};

const std::vector<int> White_Blocks {WHITENormalBlock1, WHITENormalBlock2, WHITECriticBlock};

const std::vector<int> Red_Blocks {REDNormalBlock1, REDNormalBlock2, REDFastBlock1, REDFastBlock2};


// Upgrade Settings

const int Upgrade_String_num = 4;

enum { RaiseMaxHealth, RaiseBothAttack, Heal, RaiseMagicAttack };

const QString Upgrade_Strings[Upgrade_String_num]{
    "Raise max health by",
    "Raise attack by",
    "Heal to full health",
    "Raise skill attack by"
};

const double upgrade_index[]{ 0,
    1.00, 1.20, 1.42, 1.66, 1.90,
    2.30, 2.66, 2.97, 3.39, 4.00,
    4.83, 5.32, 5.91, 6.63, 7.39,
    8.00, 8.82, 9.78, 10.52, 11.50,
    12.53, 13.66, 14.80, 16.00, 17.34, 
    18.67, 20.23, 22.00, 24.30, 26.50,
    28.00, 30.34, 33.00, 36.21, 39.97, 
    43.12, 46.51, 49.21, 53.34, 59.12, 65.00
};

const int Upgrade_Range_Min = 30, Upgrade_Range_Max = 40;

// Icon Settings

const QString
    Attack_Icon_Address = "picture/icon/hero_attack_icon.png",
    Hero_Health_Container_Address = "picture/icon/hero_healthbar_container.png",
    Enemy_Health_Container_Address = "picture/icon/enemy_healthbar_container.png",
    Health_Bar_Address = "picture/icon/healthbar_bar.png",
    Operationbar_Frame_Address = "picture/icon/operationbar_frame.png",
    Operationbar_Board_Address = "picture/icon/operationbar_board.png",
    MovingSign_Address = "picture/icon/moving_sword.png",
    TitleScreenNoButton_Address = "picture/background/title_screen_no_buttons.png",
    TitleScreenWithButton_Address = "picture/background/title_screen_with_buttons.png",
    LoadGameButton_Address = "picture/background/load_game_button.png",
    LoadGameButtonHover_Address = "picture/background/load_game_button_hover.png",
    NewGameButton_Address = "picture/background/new_game_button.png",
    NewGameButtonHover_Address = "picture/background/new_game_button_hover.png",
    OptionButton_Address = "picture/background/options_button.png",
    OptionButtonHover_Address = "picture/background/options_button_hover.png",
    TutorialButton_Address = "picture/background/tutorial_button.png",
    TutorialButtonHover_Address = "picture/background/tutorial_button_hover.png",
    PressSpacePng_Address = "picture/background/press_space.png",
    Trick_Movement[4]{
        "picture/icon/sword_ball1.png",
        "picture/icon/sword_ball2.png",
        "picture/icon/sword_ball3.png",
        "picture/icon/sword_ball4.png"
    },
    Trick_Trigger_Movement[4]{
        "picture/icon/sword_ball_hit1.png",
        "picture/icon/sword_ball_hit2.png",
        "picture/icon/sword_ball_hit3.png",
        "picture/icon/sword_ball_hit4.png",
    };

// Enemy Settings

enum { None, 
    SLIME, TREANT, LEPRECHAUN, BEAST, GOBLIN, SLIMEQUEEN, MONSTER, 
    BAT, GOLEM, STONESLIME, SKELETON, GIANTGOLEM, MEDUSA,
    GUARD, ARCHER, WIZARD, SHIELD, DARKKING, MELIN,
    LAVASLIME, DEMON, UNDEADSKELETON, SUCCUBUS, THEDEATH, THECREATOR
    };

const std::vector<int> Stage_Enemy[5]
{
    {},
    {SLIME, TREANT, LEPRECHAUN, BEAST, GOBLIN},
    {BAT, GOLEM, STONESLIME, SKELETON},
    {GUARD, ARCHER, WIZARD, SHIELD},
    {LAVASLIME, DEMON, UNDEADSKELETON, SUCCUBUS}
};

const std::vector<int> Stage_Boss[5]
{
    {},
    {SLIMEQUEEN, MONSTER},
    {GIANTGOLEM, MEDUSA},
    {DARKKING, MELIN},
    {THEDEATH}
};

// 相应定义在enemy.h
const QString ImgAddress[]{
    "",                             // default
    "picture/enemy/slime.png",
    "picture/enemy/treant.png",
    "picture/enemy/leprechaun.png",
    "picture/enemy/beast.png",
    "picture/enemy/goblin.png",
    "picture/enemy/slimequeen.png",
    "picture/enemy/monster.png",

    "picture/enemy/bat.png",
    "picture/enemy/golem.png",
    "picture/enemy/stoneslime.png",
    "picture/enemy/skeleton.png",
    "picture/enemy/giantgolem.png",
    "picture/enemy/medusa.png",

    "picture/enemy/guard.png",
    "picture/enemy/archer.png",
    "picture/enemy/wizard.png",
    "picture/enemy/shield.png",
    "picture/enemy/darkking.png",
    "picture/enemy/melin.png",

    "picture/enemy/lavaslime.png",
    "picture/enemy/demon.png",
    "picture/enemy/undeadskeleton.png",
    "picture/enemy/succubus.png",
    "picture/enemy/thedeath.png",
    "picture/enemy/thecreator.png",
};

const int EnemyMaxHealth[]{
    40,         // default

    60, 100, 60, 80, 60, 220, 200,
    80, 120, 120, 100, 280, 220,
    120, 120, 100, 160, 250, 200,
    160, 160, 40, 110, 320, 500
};

const int EnemyAttack[][2]{
    {0, 0},        // default

    {6, 10},
    {6, 10},
    {8, 12},
    {6, 10},
    {8, 12},
    {13, 18},
    {15, 20},

    {10, 14},
    {10, 14},
    {8, 12},
    {10, 14},
    {16, 22},
    {16, 22},

    {12, 16},
    {14, 18},
    {16, 20},
    {10, 14},
    {23, 30},
    {28, 35},

    {16, 20},
    {16, 20},
    {18, 22},
    {18, 22},
    {30, 36},
    {34, 45},

};

const int EnemyColdTime[][2]{
    {100, 50},        // default

    {150, 40},
    {160, 20},
    {130, 20},
    {130, 20},
    {150, 40},
    {120, 40},
    {100, 40},

    {125, 30},
    {155, 50},
    {145, 40},
    {125, 20},
    {115, 20},
    {105, 40},

    {125, 40},
    {95, 40},
    {125, 40},
    {125, 100},
    {90, 5},
    {105, 40},

    {130, 40},
    {110, 30},
    {90, 20},
    {100, 20},
    {90, 40},
    {130, 40},
};

const std::vector<int> StageBlocks[]{
    {WHITENormalBlock1},
    {1, 2, 3, 6},
    {1, 2, 3, 4, 5, 6},
    {1, 2, 3, 6, 7},
    {1, 2, 3, 6, 8, 30}
};

const std::vector<int> EnemyBlocks[]{
    {REDNormalBlock1},
    {9, 10, 18},
    {9, 10, 11},
    {9, 10, 24},
    {9, 11, 12},
    {9, 10, 11, 13},
    {9, 10, 11, 17},
    {9, 11, 12, 16},

    {9, 10, 11, 12},
    {9, 10, 14, 15},
    {9, 10, 14, 17, 18},
    {9, 10, 11, 16},
    {12, 14, 15},
    {9, 11, 12},

    {9, 10, 11, 13, 19},
    {13, 19, 24},
    {14, 20, 21, 25},
    {13, 14, 19},
    {22, 23},
    {14, 15, 20, 21, 25, 26},

    {9, 10, 16, 17},
    {16, 20, 25, 26},
    {13, 19, 25, 26, 27},
    {16, 25, 26},
    {20, 21, 25, 26, 27, 29},
    {9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,29}
};

#endif
