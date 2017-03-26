// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 从 Windows 头中排除极少使用的资料
#define WIN_X			960
#define WIN_Y			540
//包含lib文件
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment( lib,"winmm.lib" )
#pragma comment( lib,"bass.lib" )
#pragma comment(lib,"Vfw32.lib")

//dx头文件
#include"d3d9.h"
#include"d3dx9.h"

// Windows 头文件: 
#include <windows.h>
#include <mmsystem.h>
#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <Vfw.h>
#include"tinyxml.h"


using namespace std;
// C 运行时头文件
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO:  在此处引用程序需要的其他头文件
#include "火柴人联盟.h"
#include "PlatForm.h"
#include "Obj.h"
#include "Audio4Bass.h"
#include "DX_CircleAnim.h"
#include "Obj_management.h"
#include "Picture.h"
#include"SpriteX.h"
#include "HP_rect.h"
#include "UI_img.h"
#include "UI_button.h"
#include "UI_button_2.h"
#include "UI_number.h"
#include "Animate.h"
#include "Die_Effect.h"
//用户自己的类
#include "Audio_management.h"
#include "Money_drop.h"

#include "Hurted_num.h"
#include "Cmap.h"

#include "Npc.h"
#include "Player.h"
#include "Npc1.h"
#include "Npc2.h"
#include "Npc3.h"
#include "Boss.h"
#include "Npc_Management.h"
#include "Login.h"
#include "Loading.h"
#include "New_hand_state.h"
#include "Main_scene.h"
#include "Game_start.h"


#include "Game.h"

