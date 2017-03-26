#include "stdafx.h"



void CGame_start::stop_audio()
{
	CAudio_management::Get_instance()->back_Audio_stop();
}

void CGame_start::update()
{
	press_time--;
	if (!CPlatForm::Getinstance()->get_pause() && press_time <=0)
	{
		press_time = 5;
		pause->update();
		if (pause->get_state())
		{
			pause->set_show(false);
			go->set_show(true);
			CPlatForm::Getinstance()->set_pause(true);
		}
		
	}
	else
	{
		if (press_time <= 0)
		{
			press_time = 5;
			go->update();
			if (go->get_state())
			{
				go->set_show(false);
				pause->set_show(true);
				CPlatForm::Getinstance()->set_pause(false);
			}
		}
		
	}
	
	

	if (gogo_time > 0)
	{
		gogo_time--;
		gogo->update();
		gogo->draw();
	}

	int player_x = CPlayer::Get_Instance()->get_x();
	int npc_size = CNpc_Management::Get_instance()->get_list_size();
	switch (_state)
	{
	case CGame_start::a_0:
		_state = a_1;
		set_go(200);
		break;
	case CGame_start::a_1:
		
		Cmap::Getinstance()->set_lock_scene(1);
		if (player_x >= 1000 && !is_instate)
		{
			is_instate = true;
			
		}
		else if (is_instate && !is_stateover)
		{
			if (state_a[0] == NULL || state_a[1] == NULL)
			{
				state_a[0] = new CNpc3;
				state_a[0]->set_pos(1400, 365);

				state_a[1] = new CNpc3;
				state_a[1]->set_pos(600, 365);
				is_stateover = true;
			}
		}
		else if (npc_size == 0 && is_stateover)
		{
			_state = a_2;
			is_stateover = false;
			is_instate = false;
		}
		break;
	case CGame_start::a_2:
		if (state_a[2] == NULL || state_a[3] == NULL)
		{
			state_a[2] = new CNpc3;
			state_a[2]->set_pos(1400, 365);

			state_a[3] = new CNpc3;
			state_a[3]->set_pos(600, 365);
			is_stateover = true;
		}
		else if (npc_size == 0 && is_stateover)
		{
			_state = b_0;
			is_stateover = false;
		}
		break;
	case CGame_start::b_0:
		_state = b_1;
		set_go(200);
		break;
	case CGame_start::b_1:
		Cmap::Getinstance()->set_lock_scene(2);
		if (player_x >= 2000 && !is_instate)
		{
			is_instate = true;
			
		}
		else if (is_instate && !is_stateover)
		{
			if (state_b[0] == NULL&&state_b[1] == NULL&&state_b[2] == NULL&&state_b[3] == NULL)
			{
				state_b[0] = new CNpc2;
				state_b[0]->set_pos(2400, 365);
				state_b[1] = new CNpc2;
				state_b[1]->set_pos(2200, 365);
				state_b[2] = new CNpc2;
				state_b[2]->set_pos(1600, 365);
				state_b[3] = new CNpc2;
				state_b[3]->set_pos(1800, 365);
				is_stateover = true;
			}
		}
		else if (npc_size == 0 && is_stateover)
		{
			_state = b_2;
			is_stateover = false;
			is_instate = false;
		}
		break;
	case CGame_start::b_2:
		if (state_b[4] == NULL&&state_b[5] == NULL&&state_b[6] == NULL&&state_b[7] == NULL)
		{
			state_b[4] = new CNpc2;
			state_b[4]->set_pos(2400, 365);
			state_b[5] = new CNpc2;
			state_b[5]->set_pos(2200, 365);
			state_b[6] = new CNpc2;
			state_b[6]->set_pos(1600, 365);
			state_b[7] = new CNpc2;
			state_b[7]->set_pos(1800, 365);
			is_stateover = true;
		}
		else if (npc_size == 0 && is_stateover)
		{
			_state = c_0;
			is_stateover = false;
		}
		break;
	case CGame_start::c_0:
		_state = c_1;
		set_go(200);
		break;
	case CGame_start::c_1:
		Cmap::Getinstance()->set_lock_scene(3);
		if (player_x >= 3000 && !is_instate)
		{
			is_instate = true;
			
		}
		else if (is_instate && !is_stateover)
		{
			if (state_c[0] == NULL&&state_c[1] == NULL&&state_c[2] == NULL&&state_c[3] == NULL)
			{
				state_c[0] = new CNpc1;
				state_c[0]->set_pos(3400, 365);
				state_c[1] = new CNpc1;
				state_c[1]->set_pos(3200, 365);
				state_c[2] = new CNpc1;
				state_c[2]->set_pos(2600, 365);
				state_c[3] = new CNpc1;
				state_c[3]->set_pos(2800, 365);
				is_stateover = true;
			}
		}
		else if (npc_size == 0 && is_stateover)
		{
			_state = c_2;
			is_stateover = false;
			is_instate = false;
		}
		break;
	case CGame_start::c_2:
		if (state_c[4] == NULL&&state_c[5] == NULL&&state_c[6] == NULL&&state_c[7] == NULL)
		{
			state_c[4] = new CNpc1;
			state_c[4]->set_pos(3400, 365);
			state_c[5] = new CNpc1;
			state_c[5]->set_pos(3200, 365);
			state_c[6] = new CNpc1;
			state_c[6]->set_pos(2600, 365);
			state_c[7] = new CNpc1;
			state_c[7]->set_pos(2800, 365);
			is_stateover = true;
		}
		else if (npc_size == 0 && is_stateover)
		{
			_state = boss;
			is_stateover = false;
		}
		break;
	case CGame_start::boss:
		if (is_camera == false)
		{
			CPlayer::Get_Instance()->set_camera(2000);
			if (!CPlayer::Get_Instance()->get_is_camera())
			{
				is_camera = true;
			}
		}
		
		Cmap::Getinstance()->set_lock_scene(4);
		if (CPlayer::Get_Instance()->get_camera_stand())
		{
			boss_showtime++;
			if (boss_showtime==10)
			{
				if (boss_1[0] == NULL)
				{
					boss_1[0] = new CNpc1;
					boss_1[0]->set_pos(4700, 365);
				}
			}
			if (boss_showtime == 20)
			{
				if (boss_1[1] == NULL)
				{
					boss_1[1] = new CNpc1;
					boss_1[1]->set_pos(4800, 365);
				}
			}
			if (boss_showtime==30)
			{
				if (boss_2[0] == NULL)
				{
					boss_2[0] = new CNpc2;
					boss_2[0]->set_pos(4900, 365);
				}
			}
			if (boss_showtime == 40)
			{
				if (boss_2[1] == NULL)
				{
					boss_2[1] = new CNpc2;
					boss_2[1]->set_pos(5000, 365);
				}
			}
			if (boss_showtime == 50)
			{
				if (boss_3[0] == NULL)
				{
					boss_3[0] = new CNpc3;
					boss_3[0]->set_pos(5100, 365);
				}
			}
			if (boss_showtime == 60)
			{
				if (boss_3[1] == NULL)
				{
					boss_3[1] = new CNpc3;
					boss_3[1]->set_pos(5200, 365);
				}
			}
			if (boss_showtime == 70)
			{
				if (boss_boss == NULL)
				{
					boss_boss = new CBoss;
					boss_boss->set_pos(5400, 365);
					is_stateover = true;
				
				}
			}
			
		}
		if (npc_size == 0 && is_stateover)
		{
			//游戏胜利
			Game_state = true;
			is_stateover = false;
		}
		break;
	default:
		break;
	}
}

void CGame_start::Release()
{
	//BackScene->set_del(true);
	m_money->set_del(true);
	m_hp->set_del(true);
	money_number->set_del(true);
	hp_number->set_del(true);
	if (pause != NULL)
	{
		pause->Release();
		delete pause;
		pause = NULL;
	}
	if (go != NULL)
	{
		go->Release();
		delete go;
		go = NULL;
	}
}

void CGame_start::set_score(int money,int hp)
{
	money_number->set_score(money);
	hp_number->set_score(hp);
}

CGame_start::CGame_start()
{
	_state = a_0;
	Game_state = false;
	for (int a = 0; a < 4; a++)
	{
		state_a[a] = NULL;
	}
	for (int b = 0; b < 8; b++)
	{
		state_b[b] = NULL;
		state_c[b] = NULL;
	}
	for (int c = 0; c < 2; c++)
	{
		boss_1[c] = NULL;
		boss_2[c] = NULL;
		boss_3[c] = NULL;
	}
	boss_showtime = 0;
	boss_boss = NULL;
	is_stateover = false;
	is_instate = false;
	show_time = 0;


	press_time = 20;
	go = new CUI_button(L"img/button_go.png", L"img/button_go1.png", 900, 40);
	pause = new CUI_button(L"img/button_pause.png", L"img/button_pause1.png", 900, 40);

	BackScene = new CUI_img(L"img/top_sky.png");
	BackScene->set_sort(2);
	BackScene->set_pos(0, -300);

	m_money = new CAnimate(L"img/sprite-219-0.png", 4, 3, 1, 10);
	m_money->set_pos(40, 500);
	m_money->set_sort(-5);
	m_money->set_dir(true);

	m_hp = new CAnimate(L"img/sprite-221-0.png", 4, 3, 1, 10);
	m_hp->set_pos(40, 450);
	m_hp->set_sort(-5);
	m_hp->set_dir(true);

	money_number = new CUI_number(L"img/num_yellow.png", 65, 493);
	hp_number = new CUI_number(L"img/num_monsterhit.png", 65, 443);

	

	gogo = new SpriteX(CPlatForm::Getinstance()->Get_pd3dDevice(), "img/gogo.sprite", "img/gogogo_role.png");
	gogo->setAction(0);
	gogo->setDelay(200);
	gogo->setLoop(true);
	gogo->setPosition(880, 200);


	int m_MusicIndex;//临时变量，配置音频

	
	CAudio_management::Get_instance()->back_Audio_play();
	

}


CGame_start::~CGame_start()
{
	
}
