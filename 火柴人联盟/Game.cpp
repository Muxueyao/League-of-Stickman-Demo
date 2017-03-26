#include "stdafx.h"


CGame *CGame::instance = NULL;
CGame * CGame::Get_instance()
{
	if (!instance)
		instance = new CGame;
	return instance;
}

void CGame::update()
{
	//重新游戏
	if (restart)
	{
		restart = false;
		is_gamescene = true;
		is_win = false;
		is_lose = false;
		if (lose_scene)
		{
			lose_scene->set_del(true);
			//delete lose_scene;
			lose_scene = NULL;
		}
		if (win_scene)
		{
			win_scene->set_del(true);
			//delete win_scene;
			win_scene = NULL;
		}
		if (start)
		{
			start->Release();
			delete start;
			start = NULL;
		}
		Cmap::Getinstance()->reset();
		CNpc_Management::Get_instance()->Release();
		CObj_management::Getinstance()->clean_class(CObj::class_id::moneydrop);
		CPlayer::Get_Instance()->reset();
	}

	else if (is_login)
	{
		if (login == NULL)
			login = new CLogin;
		else
		{
			login->update();
			if (login->get_state())
			{
				login->Release();
				delete login;
				login = NULL;
				is_login = false;
				is_load = true;
			}
		}
	}
	else if (is_load)
	{
		if (loading == NULL)
			loading = new CLoading;
		else
		{
			loading->update();
			if (loading->get_state())
			{
				loading->Release();
				delete loading;
				loading = NULL;
				is_load = false;
				is_mainscene = true;
			}
		}
	}
	else if (is_mainscene)
	{
		if (main_scene == NULL)
			main_scene = new CMain_scene;
		else
		{
			main_scene->update();
			if (main_scene->get_state())
			{
				main_scene->Release();
				delete main_scene;
				main_scene = NULL;
				is_mainscene = false;
				
				is_new_state = true;
			}
		}
	}
	//新手
	else if (is_new_state)
	{
		if (new_hand_state==NULL)
		{
			new_hand_state = new CNew_hand_state;
		}
		CPlayer::Get_Instance()->update();
		CPlayer::Get_Instance()->show();
		new_hand_state->update();
		if (new_hand_state->get_state())
		{
			new_hand_state->Release();
			delete new_hand_state;
			new_hand_state = NULL;
			is_new_state = false;
			is_gamescene = true;
			CPlayer::Get_Instance()->reset();
		}

	}
	//game start
	else if (is_gamescene)
	{
		if (loading == NULL && !game_start)
			loading = new CLoading;
		else if (loading != NULL)
		{
			loading->update();
			if (loading->get_state())
			{
				game_start = true;
				loading->Release();
				delete loading;
				loading = NULL;
			}
		}
		
		if (game_start)
		{
			if (start == NULL)
				start = new CGame_start;


			Cmap::Getinstance()->set_lock_scene(1);
			start->update();
			start->set_score(CPlayer::Get_Instance()->get_money(), CPlayer::Get_Instance()->get_hp());
			CNpc_Management::Get_instance()->update();
			if (CPlatForm::Getinstance()->get_pause())
			{
				CPlayer::Get_Instance()->show();
			}
			else
			{
				CPlayer::Get_Instance()->update();
				CPlayer::Get_Instance()->show();
			}
			//lose
			if (CPlayer::Get_Instance()->get_death())
			{
				is_lose = true;
				is_gamescene = false;
				game_start = false;
				start->stop_audio();

				start->Release();
				delete start;
				start = NULL;
			}
			//win
			else if (start->get_state())
			{
				game_start = false;
				is_win = true;
				is_gamescene = false;
				start->stop_audio();
				CPlayer::Get_Instance()->set_hp_show(false);

				start->Release();
				delete start;
				start = NULL;
				
			}
		}
		
	}
	//game win
	else if(is_win)
	{
		if (win_scene == NULL)
		{
			win_scene = new CUI_img(L"img/win.png");
			win_scene->set_pos(320, 80);
			CAudio_management::Get_instance()->win_audio_play();
		}
		else if (game_restart == NULL && game_exit == NULL)
		{
			game_restart = new CUI_button(L"img/ui_queren_you.png", L"img/ui_js_you.png", 550, 220);
			game_exit = new CUI_button(L"img/ui_queren_fanhui.png", L"img/ui_js_hui.png", 400, 220);
		}
		else
		{
			CPlayer::Get_Instance()->update();
			CPlayer::Get_Instance()->show();
			game_restart->update();
			game_exit->update();
			if (game_restart->get_state()
				|| game_exit->get_state())
			{

				restart = true;
				game_restart->Release();
				delete game_restart;
				game_restart = NULL;
				game_exit->Release();
				delete game_exit;
				game_exit = NULL;
			}
		}
		
		
	}
	//game lose
	else if (is_lose)
	{
		if (lose_scene == NULL)
		{
			lose_scene = new CUI_img(L"img/lose.png");
			lose_scene->set_pos(320, 80);
			CAudio_management::Get_instance()->lose_audio_play();
		}
		else if (game_restart == NULL && game_exit == NULL)
		{
			game_restart = new CUI_button(L"img/ui_queren_you.png", L"img/ui_js_you.png", 550, 220);
			game_exit= new CUI_button(L"img/ui_queren_fanhui.png", L"img/ui_js_hui.png", 400, 220);
		}
		else
		{
			game_restart->update();
			game_exit->update();
			if (game_restart->get_state()
				||game_exit->get_state())
			{
				restart = true;
				game_restart->Release();
				delete game_restart;
				game_restart = NULL;
				game_exit->Release();
				delete game_exit;
				game_exit = NULL;
			}
		}
	}

}

CGame::CGame()
{

	is_login = true;
	login = NULL;

	is_load = false;
	loading = NULL;

	is_mainscene = false;
	main_scene = NULL;

	is_new_state = false;
	new_hand_state = NULL;

	game_start = false;
	is_gamescene = false;
	start = NULL;

	is_win = false;
	win_scene = NULL;
	
	is_lose = false;
	lose_scene = NULL;

	restart = false;
	game_restart = NULL;

	game_exit = NULL;

	

}


CGame::~CGame()
{
}
