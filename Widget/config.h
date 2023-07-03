
#ifndef CONGIF_H
#define CONGIF_H

#include <vector>
#include <QFont>
#include <QFontDatabase>
#include <QStringList>
#include <QCoreApplication>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <qslider.h>
#include <QTimer>
#include <QPoint>
#include <QKeyEvent>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QtMultimedia/QMediaPlayer>
#include <qaudiooutput.h>
#include <qsettings.h>
#include "parameters.h"
#include "hoverbutton.h"

const int
    Main_Window_Width = 1000,
    Main_Window_Height = 600,
    Main_Window_X_Center = Main_Window_Width / 2,
    Main_Window_Y_Center = Main_Window_Height / 2,

    OperationBar_Width = 730,
    OperationBar_Height = 30,
    OperationBar_X_Center = Main_Window_X_Center,
    OperationBar_Y_Center = 450,

    OperationBar_Y_Center_Two[2] = {425, 475},
    OperationBar_Y_Center_Three[3] = {400, 450, 500},

    MovingSign_Width = 27,
    MovingSign_Height = 124,

    OperationBar_Left = OperationBar_X_Center - OperationBar_Width / 2 + MovingSign_Width / 2,
    OperationBar_Right = OperationBar_X_Center + OperationBar_Width / 2 - MovingSign_Width / 2,

    OperationBar_Frame_Width = 826,
    OperationBar_Frame_Height = 198,
    OperationBar_Frame_X_Center = Main_Window_X_Center,
    OperationBar_Frame_Y_Center = 450,

    OperationBar_Board_Width = 770,
    OperationBar_Board_Height = 148,
    OperationBar_Board_X_Center = Main_Window_X_Center,
    OperationBar_Board_Y_Center = 450,

    Left_Health_Container_X_Center = 250,
    Left_Health_Container_Y_Center = 100,
    Left_Health_Container_Width = 360,
    Left_Health_Container_Height = 70,

    Left_Health_Bar_X_Center = 280,
    Left_Health_Bar_Y_Center = 100,
    Left_Health_Bar_Width = 278,
    Left_Health_Bar_Height = 30,

    Left_Sword_Icon_X_Center = 150,
    Left_Sword_Tcon_Y_Center = 163,
    Left_Sword_Icon_Width = 50,
    Left_Sword_Icon_Height = 50,

    Left_Attack_Info_X_Center = 300,
    Left_Attack_Info_Y_Center = 163,
    Left_Attack_Info_Width = 240,
    Left_Attack_Info_Height = 40,

    Right_Health_Container_X_Center = 750,
    Right_Health_Container_Y_Center = 100,
    Right_Health_Container_Width = 360,
    Right_Health_Container_Height = 70,

    Right_Health_Bar_X_Center = 721,
    Right_Health_Bar_Y_Center = 100,
    Right_Health_Bar_Width = 278,
    Right_Health_Bar_Height = 30,

    Right_Sword_Icon_X_Center = 580,
    Right_Sword_Tcon_Y_Center = 163,
    Right_Sword_Icon_Width = 50,
    Right_Sword_Icon_Height = 50,

    Right_Attack_Info_X_Center = 730,
    Right_Attack_Info_Y_Center = 163,
    Right_Attack_Info_Width = 240,
    Right_Attack_Info_Height = 40,

    Hero_X_Center = Main_Window_X_Center - 200,
    Hero_Y_Bottom = 330,
    Hero_Width = 110,
    Hero_Height = 110,

    Hero_Attack_Movement[20] {0, 10, 20, 30, 40, 40, 40, 37, 33, 28, 22, 14, 9, 5, 0},

    Left_JumpNumber_X = Hero_X_Center,
    Left_JumpNumber_Y = Hero_Y_Bottom - Hero_Height + 20,

    Enemy_X_Center = Main_Window_X_Center + 200,
    Enemy_Y_Bottom = 330,
    Enemy_Width = 400,
    Enemy_Height = 200,

    Right_JumpNumber_X = Enemy_X_Center,
    Right_JumpNumber_Y = Enemy_Y_Bottom - Enemy_Height + 20,

    Enemy_Attack_Movement[20] {0, -10, -20, -30, -40, -40, -37, -33, -28, -14, -9, -5, 0},

    Upgrade_Menu_X_Center = Main_Window_X_Center,
    Upgrade_Menu_Y_Center = Main_Window_Y_Center,
    Upgrade_Menu_Width = 600,
    Upgrade_Menu_Height = 400,

    Upgrade_Button_Interval = 25,

    Upgrade_Button_Width = 450,
    Upgrade_Button_Height = 100,
    Upgrade_Button_X[3] {Upgrade_Menu_X_Center - Upgrade_Button_Width / 2, Upgrade_Menu_X_Center - Upgrade_Button_Width / 2, Upgrade_Menu_X_Center - Upgrade_Button_Width / 2},
    Upgrade_Button_Y[3] {Upgrade_Menu_Y_Center - Upgrade_Menu_Height / 2 + Upgrade_Button_Interval,
                                Upgrade_Menu_Y_Center - Upgrade_Menu_Height / 2 + 2 * Upgrade_Button_Interval + Upgrade_Button_Height,
                                Upgrade_Menu_Y_Center - Upgrade_Menu_Height / 2 + 3 * Upgrade_Button_Interval + 2 * Upgrade_Button_Height},

    Stage_Sign_X_Center = Main_Window_X_Center,
    Stage_Sign_Y_Center = 100,
    Stage_Sign_Width = 200,
    Stage_Sign_Height = 50,

    Gameover_Sign_X_Center = Main_Window_X_Center,
    Gameover_Sign_Y_Center = Main_Window_Y_Center,
    Gameover_Sign_Width = 600,
    Gameover_Sign_Height = 400,

    Gameover_Button_X_Center = Main_Window_X_Center,
    Gameover_Button_Y_Center = Gameover_Sign_Y_Center + Gameover_Sign_Height / 2,
    Gameover_Button_Width = 120,
    Gameover_Button_Height = 70,

    Deviation_Tolerance = 5,
    
    Stage_Num_Each = 10;
    
const int
    Option_Menu_X_Center = Main_Window_X_Center,
    Option_Menu_Y_Center = Main_Window_Y_Center,
    Option_Menu_Width = 600,
    Option_Menu_Height = 400,

    Optino_Bgm_Label_X_Center = 300,
    Option_Bgm_Label_Y_Center = 200,
    Option_Bgm_Label_Width = 100,
    Option_Bgm_Label_Height = 40,

    Option_Bgm_Slider_X_Center = 680,
    Option_Bgm_Slider_Y_Center = 200,
    Option_Bgm_Slider_Width = 400,
    Option_Bgm_Slider_Height = 40,

    Option_Sound_Label_X_Center = 285,
    Option_Sound_Label_Y_Center = 280,
    Option_Sound_Label_Width = 100,
    Option_Sound_Label_Height = 40,

    Option_Sound_Slider_X_Center = 680,
    Option_Sound_Slider_Y_Center = 280,
    Option_Sound_Slider_Width = 400,
    Option_Sound_Slider_Height = 40,

    Option_Jumpnumber_Label_X_Center = 400,
    Option_Jumpnumber_Label_Y_Center = 360,
    Option_Jumpnumber_Label_Width = 200,
    Option_Jumpnumber_Label_Height = 40,

    Option_Jumpnumber_Button_X_Center = 550,
    Option_Jumpnumber_Button_Y_Center = 360,
    Option_Jumpnumber_Button_Width = 60,
    Option_Jumpnumber_Button_Height = 40,

    Option_Close_Button_X_Center = Option_Menu_X_Center + Option_Menu_Width / 2 - 50,
    Option_Close_Button_Y_Center = Option_Menu_Y_Center - Option_Menu_Height / 2 + 25,
    Option_Close_Button_Width = 100,
    Option_Close_Button_Height = 50,

    Load_Label_X_Center = Main_Window_X_Center,
    Load_Label_Y_Center = Main_Window_Y_Center,
    Load_Label_Width = 600,
    Load_Label_Height = 400,

    Load_Close_Button_Width = 100,
    Load_Close_Button_Height = 50,
    Load_Close_Button_X_Center = Option_Menu_X_Center + Load_Label_Width / 2 - Load_Close_Button_Width / 2,
    Load_Close_Button_Y_Center = Option_Menu_Y_Center - Load_Label_Height / 2 + Load_Close_Button_Height / 2,

    Load_Commit_Button_Width = 100,
    Load_Commit_Button_Height = 50,
    Load_Commit_Button_X_Center = Load_Label_X_Center,
    Load_Commit_Button_Y_Center = Option_Menu_Y_Center + Load_Label_Height / 2 - Load_Commit_Button_Height / 2,

    Press_Space_Png_Width = 254,
    Press_Space_Png_Height = 28,
    Press_Sapce_Png_X_Center = 500,
    Press_Space_Png_Y_Center = 426,

    New_Game_Button_Width = 278,
    New_Game_Button_Height = 58,
    New_Game_Button_X_Center = 353,
    New_Game_Button_Y_Center = 384,

    Load_Game_Button_Width = 278,
    Load_Game_Button_Height = 58,
    Load_Game_Button_X_Center = 647,
    Load_Game_Button_Y_Center = 384,

    Tutorial_Button_Width = 278,
    Tutorial_Button_Height = 58,
    Tutorial_Button_X_Center = 353,
    Tutorial_Button_Y_Center = 458,

    Options_Button_Width = 278,
    Options_Button_Height = 58,
    Options_Button_X_Center = 647,
    Options_Button_Y_Center = 458,

    Trick_Start_X_Center = Main_Window_X_Center - 180,
    Trick_Start_Y_Center = Hero_Y_Bottom - Hero_Height / 2,
    Trick_End_X_Center = Main_Window_X_Center + 180,
    Trick_End_Y_Center = Trick_Start_Y_Center,
    Trick_Width = 38,
    Trick_Height = 33;

    const double
        Base_Sign_Velocity = 4.5,
        Base_Red_Block_Velocity = 4,
        Base_Red_Block_Accelerate = 0.02,
        Standard_Probability_defactor = 100,
        Standard_Block_Frequancy = 1.0,
        JumpNumber_Angel_Min = acos(-1) / 6,
        JumpNumber_Angel_Max = acos(-1) / 3,
        JumpNumber_Velocity = 5.0,
        JumpNumber_Accalarate = 0.6,

        Back_Near_Velocity = 3,
        Back_Far_Velocity = 1,
        Back_Sky_Velocity = 0.3,

        Trick_Velocity = 5.2,
        Trick_Hit_Count_Index = 0.5,
        Retreat_Velocity = 1.5,
        Enemy_Upgrade_Index = 0.1,
        Bow_Shoot_Interval = 1.5,
        Bow_Move_Interval = 1.0,
        Armor_Move_Interval = 1.0,
        Bomb_Radius = 150.0,
        Dust_Rivive_Interval = 2.5,
        Fireball_Hurt = 100,
        Deadly_Hurt = 66666,
        Heal_Persentage = 0.1,
        Lava_Hurt_Persentage = 0.1,
        Lave_Vanish_Interval = 5.0;

const int
    Time_Per_Frame = 10, // 100帧（后面可能要改成100帧）
    Standard_Cold_Time = 100,
    Standard_Cold_Time_Bias = 60,
    Trick_Bound = 5;

//const int
//    Block_Stack_Size = 20; // 栈的最大容量

const double Pi = acos(-1);
const int Vanish_Movements = 10;
const double Vanish_Param[10]{ cos(0), cos(Pi / 20), cos(2 * Pi / 20), 
    cos(3 * Pi / 20), cos(4 * Pi / 20), cos(5 * Pi / 20), cos(6 * Pi / 20), cos(7 * Pi / 20), cos(8 * Pi / 20), cos(9 * Pi / 20) };


#endif // CONGIF_H
